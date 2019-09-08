const path = require('path');
const opencvBuild = require('opencv-build');
const { resolvePath } = require('./commons');

const requirePath = path.join(__dirname, process.env.BINDINGS_DEBUG ? '../build/Debug/opencv4nodejs' : '../build/Release/opencv4nodejs')

function tryGetOpencvBinDir() {
  // if the auto build is disabled via environment do not even attempt
  // to read package.json
  if (opencvBuild.isAutoBuildDisabled()) {
    return opencvBuild.opencvBinDir
  }

  const envs = opencvBuild.readEnvsFromPackageJson()
  return envs.disableAutoBuild
    ? (envs.opencvBinDir || process.env.OPENCV_BIN_DIR)
    : opencvBuild.opencvBinDir
}

let cv = null
try {
  cv = require(requirePath);
} catch (err) {

  // TODO: non windows?
  const opencvBinDir = tryGetOpencvBinDir()

  // ensure binaries are added to path on windows
  if (!process.env.path.includes(opencvBinDir)) {
    process.env.path = `${process.env.path};${opencvBinDir};`
  }
  cv = require(requirePath);
}

// resolve haarcascade files
const { haarCascades, lbpCascades } = cv;
Object.keys(haarCascades).forEach(
  key => cv[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));
Object.keys(lbpCascades).forEach(
  key => cv[key] = resolvePath(path.join(__dirname, './lbpcascades'), lbpCascades[key]));

module.exports = cv;