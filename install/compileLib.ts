import { OpencvModule, OpenCVBuilder, OpenCVBuildEnv, OpenCVBuildEnvParams, args2Option, genHelp } from '@u4/opencv-build'
import child_process from 'child_process'
import fs from 'fs'
import log from 'npmlog'
import { resolvePath } from '../lib/commons'
import pc from 'picocolors'
import path from 'path'
import { EOL } from 'os'

const defaultDir = '/usr/local'
const defaultLibDir = `${defaultDir}/lib`
const defaultIncludeDir = `${defaultDir}/include`
const defaultIncludeDirOpenCV4 = `${defaultIncludeDir}/opencv4`

/**
 * @returns global system include paths
 */
function getDefaultIncludeDirs(env: OpenCVBuildEnv) {
    log.info('install', 'OPENCV_INCLUDE_DIR is not set, looking for default include dir')
    if (env.isWin) {
        throw new Error('OPENCV_INCLUDE_DIR has to be defined on windows when auto build is disabled')
    }
    return [defaultIncludeDir, defaultIncludeDirOpenCV4]
}

/**
 * @returns return a path like /usr/local/lib
 */
function getDefaultLibDir(env: OpenCVBuildEnv) {
    log.info('install', 'OPENCV_LIB_DIR is not set, looking for default lib dir')
    if (env.isWin) {
        throw new Error('OPENCV_LIB_DIR has to be defined on windows when auto build is disabled')
    }
    return defaultLibDir
}

/**
 * @returns a built lib directory
 */
function getLibDir(env: OpenCVBuildEnv): string {
    if (env.isAutoBuildDisabled) {
        return resolvePath(process.env.OPENCV_LIB_DIR) || getDefaultLibDir(env);
    } else {
        const dir = resolvePath(env.opencvLibDir);
        if (!dir) {
            throw Error('failed to resolve opencvLibDir path');
        }
        return dir;
    }
}

function getOPENCV4NODEJS_LIBRARIES(env: OpenCVBuildEnv, libDir: string, libsFoundInDir: OpencvModule[]): string[] {
    const libs = env.isWin
        ? libsFoundInDir.map(lib => resolvePath(lib.libPath))
        // dynamically link libs if not on windows
        : ['-L' + libDir]
            .concat(libsFoundInDir.map(lib => '-lopencv_' + lib.opencvModule))
            .concat('-Wl,-rpath,' + libDir)

    if (libs.length > 0) {
        const dir = path.dirname(libs[0]);
        const names = libs.map(lib => path.basename(lib))
        log.info('libs', `${EOL}Setting lib from ${pc.green(dir)} : ${names.map(pc.yellow).join(', ')}`)
    } else {
        log.info('libs', `${EOL}no Libs available`)
    }
    return libs;
}

function getOPENCV4NODEJS_DEFINES(libsFoundInDir: OpencvModule[]): string[] {
    const defines = libsFoundInDir
        .map(lib => `OPENCV4NODEJS_FOUND_LIBRARY_${lib.opencvModule.toUpperCase()}`)
    log.info('defines', `${EOL}Setting the following defines:`)
    defines.forEach(def => log.info('defines', pc.yellow(def)))
    return defines;
}

function getOPENCV4NODEJS_INCLUDES(env: OpenCVBuildEnv, libsFoundInDir: OpencvModule[]): string[] {
    const { OPENCV_INCLUDE_DIR } = process.env;
    let explicitIncludeDir = '';
    if (OPENCV_INCLUDE_DIR) {
        explicitIncludeDir = resolvePath(OPENCV_INCLUDE_DIR)
    }
    const includes = env.isAutoBuildDisabled
        ? (explicitIncludeDir ? [explicitIncludeDir] : getDefaultIncludeDirs(env))
        : [resolvePath(env.opencvInclude), resolvePath(env.opencv4Include)]
    log.info('install', `${EOL}setting the following includes:`)
    includes.forEach(inc => log.info('includes', pc.green(inc)))
    return includes;
}

function getExistingNodeModulesBin(dir: string, name: string): string {
    const binPath = path.join(dir, 'node_modules', '.bin', name);
    if (fs.existsSync(binPath)) {
        return binPath;
    }
    return '';
}

function getExistingBin(dir: string, name: string): string {
    const binPath = path.join(dir, name);
    if (fs.existsSync(binPath)) {
        return binPath;
    }
    return '';
}


function getParents(dir: string) {
    const out = [dir];
    while (true) {
        const next = path.resolve(dir, '..');
        if (next === dir)
            break;
        dir = next;
        out.push(dir);
    }
    return out;
}

export async function compileLib(args: string[]) {
    let dryRun = false;
    let JOBS = 'max';

    if (args.includes('--help') || args.includes('-h') || !args.includes('build')) {
        console.log('Usage: install [--version=<version>] [--electron] [--dry-run] [--flags=<flags>] [--cuda] [--nocontrib] [--nobuild] build');
        console.log(genHelp());
        return;
    }
    const options: OpenCVBuildEnvParams = args2Option(args)

    dryRun = (args.includes('--dry-run') || args.includes('--dryrun'));
    let njobs = args.indexOf('--jobs')
    if (njobs === -1)
        njobs = args.indexOf('-j')
    if (njobs > 0)
        JOBS = args[njobs + 1];

    for (const K in ['autoBuildFlags']) {
        if (options[K]) console.log(`using ${K}:`, options[K]);
    }
    const builder = new OpenCVBuilder(options);
    log.info('install', `Using openCV ${pc.green('%s')}`, builder.env.opencvVersion)
    /**
     * prepare environment variable
     */
    const libDir: string = getLibDir(builder.env);
    log.info('install', 'Using lib dir: ' + libDir)
    if (!fs.existsSync(libDir)) {
        await builder.install();
    }
    if (!fs.existsSync(libDir)) {
        throw new Error('library dir does not exist: ' + libDir)
    }
    const libsInDir: OpencvModule[] = builder.getLibs.getLibs();
    const libsFoundInDir: OpencvModule[] = libsInDir.filter(lib => lib.libPath)
    if (!libsFoundInDir.length) {
        throw new Error('no OpenCV libraries found in lib dir: ' + libDir)
    }
    log.info('install', `${EOL}Found the following libs:`)
    libsFoundInDir.forEach(lib => log.info('install', `${pc.yellow('%s')}: ${pc.green('%s')}`, lib.opencvModule, lib.libPath))
    const OPENCV4NODEJS_DEFINES = getOPENCV4NODEJS_DEFINES(libsFoundInDir).join(';');
    const OPENCV4NODEJS_INCLUDES = getOPENCV4NODEJS_INCLUDES(builder.env, libsFoundInDir).join(';');
    const OPENCV4NODEJS_LIBRARIES = getOPENCV4NODEJS_LIBRARIES(builder.env, libDir, libsFoundInDir).join(';');
    process.env['OPENCV4NODEJS_DEFINES'] = OPENCV4NODEJS_DEFINES;
    process.env['OPENCV4NODEJS_INCLUDES'] = OPENCV4NODEJS_INCLUDES;
    process.env['OPENCV4NODEJS_LIBRARIES'] = OPENCV4NODEJS_LIBRARIES;

    let flags = '';
    if (process.env.BINDINGS_DEBUG)
        flags += ' --debug';
    // process.env.JOBS=JOBS;
    flags += ` --jobs ${JOBS}`;

    const cwd = path.join(__dirname, '..');
    const hidenGyp = path.join(cwd, '_binding.gyp');
    const realGyp = path.join(cwd, 'binding.gyp');
    if (fs.existsSync(hidenGyp)) {
        fs.copyFileSync(hidenGyp, realGyp);
    }

    // const arch = 'x86_64' / 'x64'
    // flags += --arch=${arch} --target_arch=${arch}
    let nodegypCmd = ''

    const nodegyp = options.extra.electron ? 'electron-rebuild' : 'node-gyp';

    for (const dir of process.env.PATH.split(path.delimiter)) {
        nodegypCmd = getExistingBin(dir, nodegyp);
        if (nodegypCmd) {
            // no need to use full path
            nodegypCmd = nodegyp;
            break;
        }
    }
    if (!nodegypCmd) {
        for (const startDir in [__dirname, process.cwd()]) {
            let dir = startDir;
            while (dir) {
                nodegypCmd = getExistingNodeModulesBin(dir, nodegyp);
                if (nodegypCmd)
                    break;
                const next = path.resolve(dir, '..');
                if (next === dir) {
                    break;
                }
                dir = next;
            }
            if (nodegypCmd)
                break;
        }
    }
    if (!nodegypCmd) {
        const msg = `Please install "${nodegyp}" to build openCV bindings${EOL}npm install --save-dev ${nodegyp}`;
        throw Error(msg)
    }

    // flags starts with ' '
    nodegypCmd += ` rebuild${flags}`;

    log.info('install', `Spawning in directory:${cwd} node-gyp process: ${nodegypCmd}`)

    if (dryRun) {
        console.log('');
        console.log(`export OPENCV4NODEJS_DEFINES="${OPENCV4NODEJS_DEFINES}"`);
        console.log(`export OPENCV4NODEJS_INCLUDES="${OPENCV4NODEJS_INCLUDES}"`);
        console.log(`export OPENCV4NODEJS_LIBRARIES="${OPENCV4NODEJS_LIBRARIES}"`);
        console.log('');
        console.log(nodegypCmd);
        console.log('');
    } else {
        const child = child_process.exec(nodegypCmd, { maxBuffer: Infinity, cwd }, function (error/*, stdout, stderr*/) {
            fs.unlinkSync(realGyp);
            const bin = options.extra.electron ? 'electron-rebuild' : 'node-gyp';
            if (error) {
                console.log(`error: `, error);
                log.error('install', `${bin} failed and return ${error.name} ${error.message} return code: ${error.code}`);
            } else {
                log.info('install', `${bin} complete successfully`);
            }
        })
        if (child.stdout) child.stdout.pipe(process.stdout)
        if (child.stderr) child.stderr.pipe(process.stderr)
    }
}

