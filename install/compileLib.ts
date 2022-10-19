import { OpencvModule, OpenCVBuilder, OpenCVBuildEnv, OpenCVBuildEnvParams, args2Option, genHelp } from '@u4/opencv-build'
import child_process from 'child_process'
import fs from 'fs'
import log from 'npmlog'
import { resolvePath } from '../lib/commons'
import pc from 'picocolors'
import path from 'path'
import { EOL } from 'os'
import blob from '@u4/tiny-glob';

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

/**
 * generate all C++ Defines and debug them nicely on screen
 * @param libsFoundInDir selected modules
 * @returns list of defines
 */
function getOPENCV4NODEJS_DEFINES(libsFoundInDir: OpencvModule[]): string[] {
    const defines = libsFoundInDir
        .map(lib => `OPENCV4NODEJS_FOUND_LIBRARY_${lib.opencvModule.toUpperCase()}`)
    log.info('defines', `${EOL}Setting the following defines:`)
    const longest = Math.max(...defines.map(a => a.length));
    let next = '';
    for (const define of defines) {
        if (next.length > 80) {
            log.info('defines', pc.yellow(next));
            next = '';
        }
        next += define.padEnd(longest + 1, ' ');
    }
    if (next)
        log.info('defines', pc.yellow(next));
    return defines;
}

/**
 * generate C++ Includes
 * @param env context
 * @returns list of directory to include for C++ compiler
 */
function getOPENCV4NODEJS_INCLUDES(env: OpenCVBuildEnv): string[] {
    const { OPENCV_INCLUDE_DIR } = process.env;
    let explicitIncludeDir = '';
    if (OPENCV_INCLUDE_DIR) {
        explicitIncludeDir = resolvePath(OPENCV_INCLUDE_DIR)
    }
    const includes = env.isAutoBuildDisabled
        ? (explicitIncludeDir ? [explicitIncludeDir] : getDefaultIncludeDirs(env))
        : [resolvePath(env.opencvInclude), resolvePath(env.opencv4Include)]
    log.info('install', `${EOL}Setting the following includes:`)
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

export async function compileLib(args: string[]) {
    let dryRun = false;
    let JOBS = 'max';
    const validAction = ['build', 'clean', 'configure', 'rebuild', 'install', 'list', 'remove', 'auto']
    let action = args[args.length - 1];
    if (args.includes('--help') || args.includes('-h') || !validAction.includes(action)) {
        console.log(`Usage: build-opencv build|rebuild|configure|install [--version=<version>] [--vscode] [--jobs=<thread>] [--electron] [--node-gyp-options=<options>] [--dry-run] [--flags=<flags>] [--cuda] [--nocontrib] [--nobuild] ${validAction.join('|')}`);
        console.log(genHelp());
        return;
    }
    const env = process.env;
    const npmEnv = OpenCVBuildEnv.readEnvsFromPackageJson() || {};
    if (action === 'auto') {
        if (env.OPENCV4NODEJS_DISABLE_AUTOBUILD) {
            action = 'rebuild'
        }
        if (env.OPENCV4NODEJS_AUTOBUILD_OPENCV_VERSION) {
            action = 'rebuild'
        }
        if (Object.keys(npmEnv).length) {
            action = 'rebuild';
        }
    }
    if (action === 'auto') {
        console.log(`Use 'npx build-opencv rebuild' script to start node-gyp, use --help to check all options.
or configure configure a opencv4nodejs section in your package.json
or use OPENCV4NODEJS_* env variable.`)
        return;
    }
    const options: OpenCVBuildEnvParams = args2Option(args)
    if (options.extra.jobs) {
        JOBS = options.extra.jobs;
    }

    if (options.disableAutoBuild || env.OPENCV4NODEJS_DISABLE_AUTOBUILD || npmEnv.disableAutoBuild) {
        const summery = OpenCVBuildEnv.autoLocatePrebuild();
        log.info('envAutodetect', `autodetect ${pc.green('%d')} changes`, summery.changes)
        for (const txt of summery.summery) {
            log.info('envAutodetect', `- ${pc.yellow('%s')}`, txt)
        }
    }

    if (options.extra['dry-run'] || options.extra['dryrun']) {
        dryRun = true;
    }

    for (const K in ['autoBuildFlags']) {
        if (options[K]) console.log(`using ${K}:`, options[K]);
    }
    const builder = new OpenCVBuilder(options);
    log.info('install', `Using openCV ${pc.green('%s')}`, builder.env.opencvVersion)
    /**
     * prepare environment variable
     */
    const libDir: string = getLibDir(builder.env);
    log.info('install', `Using lib dir: ${pc.green('%s')}`, libDir)
    //if (!fs.existsSync(libDir))
    await builder.install();

    if (!fs.existsSync(libDir)) {
        throw new Error(`library dir does not exist: ${pc.green(libDir)}'`)
    }
    const libsInDir: OpencvModule[] = builder.getLibs.getLibs();
    const libsFoundInDir: OpencvModule[] = libsInDir.filter(lib => lib.libPath)
    if (!libsFoundInDir.length) {
        throw new Error(`no OpenCV libraries found in lib dir: ${pc.green(libDir)}`)
    }
    log.info('install', `${EOL}Found the following libs:`)
    libsFoundInDir.forEach(lib => log.info('install', `${pc.yellow('%s')}: ${pc.green('%s')}`, lib.opencvModule, lib.libPath))
    const OPENCV4NODEJS_DEFINES = getOPENCV4NODEJS_DEFINES(libsFoundInDir).join(';');
    const OPENCV4NODEJS_INCLUDES = getOPENCV4NODEJS_INCLUDES(builder.env).join(';');
    const OPENCV4NODEJS_LIBRARIES = getOPENCV4NODEJS_LIBRARIES(builder.env, libDir, libsFoundInDir).join(';');

    process.env['OPENCV4NODEJS_DEFINES'] = OPENCV4NODEJS_DEFINES;
    process.env['OPENCV4NODEJS_INCLUDES'] = OPENCV4NODEJS_INCLUDES;
    process.env['OPENCV4NODEJS_LIBRARIES'] = OPENCV4NODEJS_LIBRARIES;

    // see https://github.com/nodejs/node-gyp#command-options for all flags
    let flags = '';

    // process.env.JOBS=JOBS;
    flags += ` --jobs ${JOBS}`;

    // --target not mapped
    // --silly, --loglevel=silly	Log all progress to console
    // --verbose, --loglevel=verbose	Log most progress to console
    // --silent, --loglevel=silent	Don't log anything to console

    if (process.env.BINDINGS_DEBUG || options.extra['debug'])
        flags += ' --debug';
    else
        flags += ' --release';

    // --thin=yes

    const cwd = path.join(__dirname, '..');

    // const arch = 'x86_64' / 'x64'
    // flags += --arch=${arch} --target_arch=${arch}
    const cmdOptions = options.extra['node-gyp-options'] || '';
    flags += ` ${cmdOptions}`;

    const nodegyp = options.extra.electron ? 'electron-rebuild' : 'node-gyp';
    let nodegypCmd = '';
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
    nodegypCmd += ` ${action}${flags}`;

    log.info('install', `Spawning in directory:${cwd} node-gyp process: ${nodegypCmd}`)

    if (options.extra.vscode) {
        // const nan = require('nan');
        // const nativeNodeUtils = require('native-node-utils');
        // const pblob = promisify(blob)
        const openCvModuleInclude = await blob(path.join(builder.env.opencvSrc, 'modules', '*', 'include'));
        const openCvContribModuleInclude = await blob(path.join(builder.env.opencvContribSrc, 'modules', '*', 'include'));
        const cvVersion = builder.env.opencvVersion.split('.');
        const config = {
            "name": "opencv4nodejs",
            "includePath": [
                'Missing node-gyp/Cache/16.13.1/include/node',
                ...OPENCV4NODEJS_INCLUDES,
                '${workspaceFolder}/node_modules/nan',
                '${workspaceFolder}/node_modules/native-node-utils/src',
                '${workspaceFolder}/cc',
                '${workspaceFolder}/cc/core',
                ...openCvModuleInclude,
                ...openCvContribModuleInclude,
            ],
            "defines": [
                `CV_VERSION_MAJOR=${cvVersion[0]}`,
                `CV_VERSION_MINOR=${cvVersion[1]}`,
                `CV_VERSION_REVISION=${cvVersion[2]}`,
                ...OPENCV4NODEJS_DEFINES],
            "cStandard": "c11",
            "cppStandard": "c++11",
            // "compilerArgs": [ "-std=c++11" ]
        }
        if (process.platform === 'win32') {
            config.defines.push('WIN');
            config.defines.push('_HAS_EXCEPTIONS=1');
        }
        console.log(JSON.stringify(config, null, '  '));
    } else if (dryRun) {
        let setEnv = 'export ';
        if (process.platform === 'win32') {
            setEnv = '$Env:';
        }
        console.log('');
        console.log(`${setEnv}OPENCV4NODEJS_DEFINES="${OPENCV4NODEJS_DEFINES}"`);
        console.log(`${setEnv}OPENCV4NODEJS_INCLUDES="${OPENCV4NODEJS_INCLUDES}"`);
        console.log(`${setEnv}OPENCV4NODEJS_LIBRARIES="${OPENCV4NODEJS_LIBRARIES}"`);
        console.log('');
        if (cwd.includes(' '))
            console.log(`cd "${cwd}"`);
        else
            console.log(`cd ${cwd}`);
        console.log(nodegypCmd);
        console.log('');
    } else {
        const child = child_process.exec(nodegypCmd, { maxBuffer: Infinity, cwd }, function (error/*, stdout, stderr*/) {
            // fs.unlinkSync(realGyp);
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

