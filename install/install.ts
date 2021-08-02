import * as opencvBuild from 'opencv-build'
import child_process from 'child_process'
import fs from 'fs'
import log from 'npmlog'
import { resolvePath } from '../lib/commons'

let dryRun = false;

if (process.argv) {
  if (process.argv.includes('--dryrun'))
    dryRun = true;
  if (process.argv.includes('--dry-run'))
    dryRun = true;
}

const defaultDir = '/usr/local'
const defaultLibDir = `${defaultDir}/lib`
const defaultIncludeDir = `${defaultDir}/include`
const defaultIncludeDirOpenCV4 = `${defaultIncludeDir}/opencv4`

/**
 * @returns global system include paths
 */
function getDefaultIncludeDirs() {
  log.info('install', 'OPENCV_INCLUDE_DIR is not set, looking for default include dir')
  if (opencvBuild.isWin()) {
    throw new Error('OPENCV_INCLUDE_DIR has to be defined on windows when auto build is disabled')
  }
  return [defaultIncludeDir, defaultIncludeDirOpenCV4]
}

/**
 * @returns return a path like /usr/local/lib
 */
function getDefaultLibDir() {
  log.info('install', 'OPENCV_LIB_DIR is not set, looking for default lib dir')
  if (opencvBuild.isWin()) {
    throw new Error('OPENCV_LIB_DIR has to be defined on windows when auto build is disabled')
  }
  return defaultLibDir
}

/**
 * @returns a built lib directory
 */
function getLibDir(): string {
  if (opencvBuild.isAutoBuildDisabled()) {
    return resolvePath(process.env.OPENCV_LIB_DIR) || getDefaultLibDir();
  } else {
    const dir = resolvePath(opencvBuild.opencvLibDir);
    if (!dir) {
      throw Error('failed to resolve opencvLibDir path');
    }
    return dir;
  }
}

function getOPENCV4NODEJS_LIBRARIES(libsFoundInDir: opencvBuild.OpencvModule[]): string[] {
  const libs = opencvBuild.isWin()
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

function getOPENCV4NODEJS_DEFINES(libsFoundInDir: opencvBuild.OpencvModule[]): string[] {
  const defines = libsFoundInDir
    .map(lib => `OPENCV4NODEJS_FOUND_LIBRARY_${lib.opencvModule.toUpperCase()}`)
  console.log()
  log.info('install', 'setting the following defines:')
  defines.forEach(def => log.info('defines', def))
  return defines;
}

function getOPENCV4NODEJS_INCLUDES(libsFoundInDir: opencvBuild.OpencvModule[]): string[] {
  const { OPENCV_INCLUDE_DIR } = process.env;
  let explicitIncludeDir = '';
  if (OPENCV_INCLUDE_DIR) {
    explicitIncludeDir = resolvePath(OPENCV_INCLUDE_DIR)
  }
  const includes = opencvBuild.isAutoBuildDisabled()
    ? (explicitIncludeDir ? [explicitIncludeDir] : getDefaultIncludeDirs())
    : [resolvePath(opencvBuild.opencvInclude), resolvePath(opencvBuild.opencv4Include)]
  console.log()
  log.info('install', 'setting the following includes:')
  includes.forEach(inc => log.info('includes', '' + inc))
  return includes;
}

/**
 * prepare environment variable
 */
opencvBuild.applyEnvsFromPackageJson()

const libDir: string = getLibDir();
log.info('install', 'using lib dir: ' + libDir)

if (!fs.existsSync(libDir as string)) {
  throw new Error('library dir does not exist: ' + libDir)
}

const libsInDir: opencvBuild.OpencvModule[] = opencvBuild.getLibs(libDir);
const libsFoundInDir: opencvBuild.OpencvModule[] = libsInDir.filter(lib => lib.libPath)
if (!libsFoundInDir.length) {
  throw new Error('no OpenCV libraries found in lib dir: ' + libDir)
}

log.info('install', 'found the following libs:')
libsFoundInDir.forEach(lib => log.info('install', `${lib.opencvModule}: ${lib.libPath}`))

const OPENCV4NODEJS_DEFINES = getOPENCV4NODEJS_DEFINES(libsFoundInDir).join(';');
const OPENCV4NODEJS_INCLUDES = getOPENCV4NODEJS_INCLUDES(libsFoundInDir).join(';');
const OPENCV4NODEJS_LIBRARIES = getOPENCV4NODEJS_LIBRARIES(libsFoundInDir).join(';');

process.env['OPENCV4NODEJS_DEFINES'] = OPENCV4NODEJS_DEFINES;
process.env['OPENCV4NODEJS_INCLUDES'] = OPENCV4NODEJS_INCLUDES;
process.env['OPENCV4NODEJS_LIBRARIES'] = OPENCV4NODEJS_LIBRARIES;

const flags = process.env.BINDINGS_DEBUG ? '--jobs max --debug' : '--jobs max'
const nodegypCmd = 'node-gyp rebuild --arch=x86_64 --target_arch=x86_64 ' + flags
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
  const child = child_process.exec(nodegypCmd, { maxBuffer: Infinity }, function (err, stdout, stderr) {
    const _err = err || stderr
    if (_err) log.error('error', `${_err}`)
  })
  if (child.stdout) child.stdout.pipe(process.stdout)
  if (child.stderr) child.stderr.pipe(process.stderr)
}