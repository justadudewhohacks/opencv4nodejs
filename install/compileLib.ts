import { OpencvModule, OpenCVBuilder, OpenCVBuildEnv, isWin } from '@u4/opencv-build'
import child_process from 'child_process'
import fs from 'fs'
import log from 'npmlog'
import { resolvePath } from '../lib/commons'
import pc from 'picocolors'
import mri from 'mri';
import { OpenCVParamBuildOptions } from '@u4/opencv-build/build/BuildEnv'
import path from 'path'

const defaultDir = '/usr/local'
const defaultLibDir = `${defaultDir}/lib`
const defaultIncludeDir = `${defaultDir}/include`
const defaultIncludeDirOpenCV4 = `${defaultIncludeDir}/opencv4`

/**
 * @returns global system include paths
 */
function getDefaultIncludeDirs() {
    log.info('install', 'OPENCV_INCLUDE_DIR is not set, looking for default include dir')
    if (isWin()) {
        throw new Error('OPENCV_INCLUDE_DIR has to be defined on windows when auto build is disabled')
    }
    return [defaultIncludeDir, defaultIncludeDirOpenCV4]
}

/**
 * @returns return a path like /usr/local/lib
 */
function getDefaultLibDir() {
    log.info('install', 'OPENCV_LIB_DIR is not set, looking for default lib dir')
    if (isWin()) {
        throw new Error('OPENCV_LIB_DIR has to be defined on windows when auto build is disabled')
    }
    return defaultLibDir
}

/**
 * @returns a built lib directory
 */
function getLibDir(env: OpenCVBuildEnv): string {
    if (env.isAutoBuildDisabled) {
        return resolvePath(process.env.OPENCV_LIB_DIR) || getDefaultLibDir();
    } else {
        const dir = resolvePath(env.opencvLibDir);
        if (!dir) {
            throw Error('failed to resolve opencvLibDir path');
        }
        return dir;
    }
}

function getOPENCV4NODEJS_LIBRARIES(libDir: string, libsFoundInDir: OpencvModule[]): string[] {
    const libs = isWin()
        ? libsFoundInDir.map(lib => resolvePath(lib.libPath))
        // dynamically link libs if not on windows
        : ['-L' + libDir]
            .concat(libsFoundInDir.map(lib => '-lopencv_' + lib.opencvModule))
            .concat('-Wl,-rpath,' + libDir)
    console.log()
    log.info('install', 'setting the following libs:')
    libs.forEach(lib => log.info('libs', '' + lib))
    return libs;
}

function getOPENCV4NODEJS_DEFINES(libsFoundInDir: OpencvModule[]): string[] {
    const defines = libsFoundInDir
        .map(lib => `OPENCV4NODEJS_FOUND_LIBRARY_${lib.opencvModule.toUpperCase()}`)
    console.log()
    log.info('install', 'setting the following defines:')
    defines.forEach(def => log.info('defines', def))
    return defines;
}

function getOPENCV4NODEJS_INCLUDES(env: OpenCVBuildEnv, libsFoundInDir: OpencvModule[]): string[] {
    const { OPENCV_INCLUDE_DIR } = process.env;
    let explicitIncludeDir = '';
    if (OPENCV_INCLUDE_DIR) {
        explicitIncludeDir = resolvePath(OPENCV_INCLUDE_DIR)
    }
    const includes = env.isAutoBuildDisabled
        ? (explicitIncludeDir ? [explicitIncludeDir] : getDefaultIncludeDirs())
        : [resolvePath(env.opencvInclude), resolvePath(env.opencv4Include)]
    console.log()
    log.info('install', 'setting the following includes:')
    includes.forEach(inc => log.info('includes', '' + inc))
    return includes;
}

export async function compileLib(args: string[]) {
    let dryRun = false;
    const parsed = mri(args);

    if (parsed.help || parsed.h || !args.includes('build')) {
        console.log('Usage: install [--version=<version>] [--dry-run] [--flags=<flags>] [--cuda] [--nocontrib] [--nobuild] build');
        return;
    }

    const options: OpenCVParamBuildOptions = {
        autoBuildOpencvVersion: parsed.version,
        autoBuildFlags: parsed.flags
    }
    if (parsed.cuda) options.autoBuildBuildCuda = true;
    if (parsed.nocontrib) options.autoBuildWithoutContrib = true;
    if (parsed.nobuild) options.disableAutoBuild = true;

    dryRun = parsed.dryrun || parsed['dry-run'];

    // Version = '3.4.16'; // failed
    // cc\xfeatures2d\siftdetector.h(9): error C2039: 'SIFT': is not a member of 'cv::xfeatures2d' [opencv4nodejs\build\opencv4nodejs.vcxproj]
    // cc\xfeatures2d\siftdetector.h(9): error C3203: 'Ptr': unspecialized class template can't be used as a template argument for template parameter 'T', expected a real type [\opencv4nodejs\build\opencv4nodejs.vcxproj]
    for (const K in ['autoBuildFlags']) {
        if (options[K]) console.log(`using ${K}:`, options[K]);
    }
    const builder = new OpenCVBuilder(options);
    console.log(`Using openCV ${pc.green(builder.env.opencvVersion)}`);
    /**
     * prepare environment variable
     */
    // builder.env.applyEnvsFromPackageJson()
    const libDir: string = getLibDir(builder.env);
    log.info('install', 'using lib dir: ' + libDir)
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
    log.info('install', 'found the following libs:')
    libsFoundInDir.forEach(lib => log.info('install', `${lib.opencvModule}: ${lib.libPath}`))
    const OPENCV4NODEJS_DEFINES = getOPENCV4NODEJS_DEFINES(libsFoundInDir).join(';');
    const OPENCV4NODEJS_INCLUDES = getOPENCV4NODEJS_INCLUDES(builder.env, libsFoundInDir).join(';');
    const OPENCV4NODEJS_LIBRARIES = getOPENCV4NODEJS_LIBRARIES(libDir, libsFoundInDir).join(';');
    process.env['OPENCV4NODEJS_DEFINES'] = OPENCV4NODEJS_DEFINES;
    process.env['OPENCV4NODEJS_INCLUDES'] = OPENCV4NODEJS_INCLUDES;
    process.env['OPENCV4NODEJS_LIBRARIES'] = OPENCV4NODEJS_LIBRARIES;
    const flags = process.env.BINDINGS_DEBUG ? '--jobs max --debug' : '--jobs max'
    // const arch = 'x86_64'
    // const arch = 'x64'

    const cwd = path.join(__dirname, '..');
    {
        const hidenGyp = path.join(cwd, '_binding.gyp');
        const realGyp = path.join(cwd, 'binding.gyp');
        if (fs.existsSync(hidenGyp)) {
            fs.renameSync(hidenGyp, realGyp);
        }
    }


    // const nodegypCmd = `node-gyp rebuild --arch=${arch} --target_arch=${arch} ` + flags
    log.info('install', `${__dirname}`)
    // const nodegypCmd = `node-gyp --help`;
    const nodegypCmd = `node-gyp rebuild ` + flags
    log.info('install', `spawning node gyp process: ${nodegypCmd}`)

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
            if (error) {
                console.log(`error: `, error);
                log.error('install', `install.ts Done and return ${error.name} ${error.message} Return code: ${error.code}`);
            } else {
                log.info('install', 'install.ts Done With no Error');
            }
        })
        if (child.stdout) child.stdout.pipe(process.stdout)
        if (child.stderr) child.stderr.pipe(process.stderr)
    }
}

