const fs = require('fs');
const path = require('path');

var opencvBuild = null;
try {
  opencvBuild = require('opencv-build');
} catch (e) {
  if (e.code !== 'MODULE_NOT_FOUND') {
    throw e;
  }

  function isWin() {
      return process.platform == 'win32';
  }
  function isOSX() {
      return process.platform == 'darwin';
  }
  var opencvModules = [
      'core',
      'highgui',
      'imgcodecs',
      'imgproc',
      'features2d',
      'calib3d',
      'photo',
      'objdetect',
      'ml',
      'video',
      'videoio',
      'videostab',
      'dnn',
      'face',
      'text',
      'tracking',
      'xfeatures2d',
      'ximgproc'
  ];

  opencvBuild = {
    getLibs: require('./getLibsFactory').getLibsFactory({ isWin, isOSX, opencvModules, path, fs }),
    isAutoBuildDisabled: () => true,
  }
}

function resolvePath(filePath, file) {
  if (!filePath) {
    return undefined;
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/');
}

const defaultDir = '/usr/local';
const defaultIncludeDir = `${defaultDir}/include`;
const defaultIncludeDirOpenCV4 = `${defaultIncludeDir}/opencv4`;

function getLibDir() {
  const libPath = resolvePath(process.env.OPENCV_LIB_DIR)
  if (process.platform === 'win32' && !libPath) {
    throw new Error('OPENCV_LIB_DIR is not defined')
  }
  return libPath || `${defaultDir}/lib`;
}

module.exports = {
  opencvBuild,
  resolvePath,
  defaultDir,
  defaultIncludeDir,
  defaultIncludeDirOpenCV4,
  getLibDir
};
