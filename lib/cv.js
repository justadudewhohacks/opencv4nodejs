const path = require('path');
const opencvBuild = require('opencv-build');
const { resolvePath } = require('./commons');

const requirePath = path.join(__dirname, process.env.BINDINGS_DEBUG ? '../build/Debug/opencv4nodejs' : '../build/Release/opencv4nodejs')

const logDebug = process.env.OPENCV4NODES_DEBUG_REQUIRE ? require('npmlog').info : () => {}

function tryGetOpencvBinDir() {
  if (process.env.OPENCV_BIN_DIR) {
    logDebug('tryGetOpencvBinDir', 'OPENCV_BIN_DIR environment variable is set')
    return process.env.OPENCV_BIN_DIR
  }
  // if the auto build is not disabled via environment do not even attempt
  // to read package.json
  if (!opencvBuild.isAutoBuildDisabled()) {
    logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via environment variable, using opencv bin dir of opencv-build')
    return opencvBuild.opencvBinDir
  }

  logDebug('tryGetOpencvBinDir', 'auto build has not been explicitly disabled via environment variable, attempting to read envs from package.json...')
  const envs = opencvBuild.readEnvsFromPackageJson()

  if (!envs.disableAutoBuild) {
    logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via package.json, using opencv bin dir of opencv-build')
    return opencvBuild.opencvBinDir
  }

  if (envs.opencvBinDir) {
    logDebug('tryGetOpencvBinDir', 'found opencv binary environment variable in package.json')
    return envs.opencvBinDir
  }
  logDebug('tryGetOpencvBinDir', 'failed to find opencv binary environment variable in package.json')
  return null
}

let cv = null
try {
  logDebug('require', 'require path is ' + requirePath)
  cv = require(requirePath);
} catch (err) {
  logDebug('require', 'failed to require cv with exception: ' + err.toString())
  logDebug('require', 'attempting to add opencv binaries to path')

  if (!process.env.path) {
    logDebug('require', 'there is no path environment variable, skipping...')
    throw err
  }

  const opencvBinDir = tryGetOpencvBinDir()
  logDebug('require', 'adding opencv binary dir to path: ' + opencvBinDir)

  // ensure binaries are added to path on windows
  if (!process.env.path.includes(opencvBinDir)) {
    process.env.path = `${process.env.path};${opencvBinDir};`
  }
  logDebug('require', 'process.env.path: ' + process.env.path)
  cv = require(requirePath);
}

// resolve haarcascade files
const { haarCascades, lbpCascades } = cv;
Object.keys(haarCascades).forEach(
  key => cv[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));
Object.keys(lbpCascades).forEach(
  key => cv[key] = resolvePath(path.join(__dirname, './lbpcascades'), lbpCascades[key]));

module.exports = cv;