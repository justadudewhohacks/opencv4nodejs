const fs = require('fs');
const path = require('path');

function resolvePath(filePath, file) {
  if (!filePath) {
    return undefined;
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/');
}

const defaultDir = '/usr/local';

function getLibDir() {
  return resolvePath(process.env.OPENCV_LIB_DIR) || `${defaultDir}/lib`;
}

module.exports = {
  resolvePath,
  defaultDir,
  getLibDir
};
