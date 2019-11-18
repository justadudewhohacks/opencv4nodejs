const opencvBuild = require('opencv-build')
const child_process = require('child_process')
const fs = require('fs')
const log = require('npmlog')
const { resolvePath } = require('../lib/commons')

const defaultDir = '/usr/local'
const defaultLibDir = `${defaultDir}/lib`
const defaultIncludeDir = `${defaultDir}/include`
const defaultIncludeDirOpenCV4 = `${defaultIncludeDir}/opencv4`

function getDefaultIncludeDirs() {
  log.info('install', 'OPENCV_INCLUDE_DIR is not set, looking for default include dir')
  if (opencvBuild.isWin()) {
    throw new Error('OPENCV_INCLUDE_DIR has to be defined on windows when auto build is disabled')
  }
  return [defaultIncludeDir, defaultIncludeDirOpenCV4]
}

function getDefaultLibDir() {
  log.info('install', 'OPENCV_LIB_DIR is not set, looking for default lib dir')
  if (opencvBuild.isWin()) {
    throw new Error('OPENCV_LIB_DIR has to be defined on windows when auto build is disabled')
  }
  return defaultLibDir
}

opencvBuild.applyEnvsFromPackageJson()

const libDir = opencvBuild.isAutoBuildDisabled()
  ? (resolvePath(process.env.OPENCV_LIB_DIR) || getDefaultLibDir())
  : resolvePath(opencvBuild.opencvLibDir)

log.info('install', 'using lib dir: ' + libDir)

if (!fs.existsSync(libDir)) {
  throw new Error('library dir does not exist: ' + libDir)
}

const libsFoundInDir = opencvBuild
  .getLibs(libDir)
  .filter(lib => lib.libPath)

if (!libsFoundInDir.length) {
  throw new Error('no OpenCV libraries found in lib dir: ' + libDir)
}

log.info('install', 'found the following libs:')
libsFoundInDir.forEach(lib => log.info('install', lib.opencvModule + ' : ' + lib.libPath))

const defines = libsFoundInDir
  .map(lib => `OPENCV4NODEJS_FOUND_LIBRARY_${lib.opencvModule.toUpperCase()}`)

const explicitIncludeDir = resolvePath(process.env.OPENCV_INCLUDE_DIR)
const includes = opencvBuild.isAutoBuildDisabled()
  ? (explicitIncludeDir ? [explicitIncludeDir] : getDefaultIncludeDirs())
  : [resolvePath(opencvBuild.opencvInclude), resolvePath(opencvBuild.opencv4Include)]

const libs = opencvBuild.isWin()
  ? libsFoundInDir.map(lib => resolvePath(lib.libPath))
  // dynamically link libs if not on windows
  : ['-L' + libDir]
      .concat(libsFoundInDir.map(lib => '-lopencv_' + lib.opencvModule))
      .concat('-Wl,-rpath,' + libDir)

console.log()
log.info('install', 'setting the following defines:')
defines.forEach(def => log.info('defines', def))
console.log()
log.info('install', 'setting the following includes:')
includes.forEach(inc => log.info('includes', inc))
console.log()
log.info('install', 'setting the following libs:')
libs.forEach(lib => log.info('libs', lib))

process.env['OPENCV4NODEJS_DEFINES'] = defines.join('\n')
process.env['OPENCV4NODEJS_INCLUDES'] = includes.join('\n')
process.env['OPENCV4NODEJS_LIBRARIES'] = libs.join('\n')

const flags = process.env.BINDINGS_DEBUG ? '--jobs max --debug' : '--jobs max'
const nodegypCmd = 'node-gyp rebuild ' + flags
log.info('install', `spawning node gyp process: ${nodegypCmd}`)
const child = child_process.exec(nodegypCmd, { maxBuffer: Infinity }, function(err, stdout, stderr) {
  const _err = err || stderr
  if (_err) log.error(_err)
})
child.stdout.pipe(process.stdout)
child.stderr.pipe(process.stderr)