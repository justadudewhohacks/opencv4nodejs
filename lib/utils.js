const fs = require('fs');
const path = require('path');

const resolvePath = (filePath, file) => {
  if (!filePath) {
    return undefined;
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/');
};

const modules = [
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
  'videostab'
];

const xmodules = [
  'tracking',
  'xfeatures2d',
  'ximgproc'
];

const libPrefixOSX = 'libopencv_';
const libSuffixOSX = '.dylib';
const libSuffix = process.platform === 'win32' ? '.lib' : '.so';

const defaultDir = '/usr/local';
const opencvDir = resolvePath(process.env.OPENCV_DIR);
let includeDir = resolvePath(process.env.OPENCV_INCLUDE_DIR);
let libDir = resolvePath(process.env.OPENCV_LIB_DIR);

if (!includeDir) {
  includeDir = resolvePath(opencvDir, 'include');
  if (!fs.existsSync(includeDir)) {
    includeDir = `${defaultDir}/include`;
  }
  if (!fs.existsSync(includeDir)) {
    throw new Error(`not found: process.env.OPENCV_DIR | process.env.OPENCV_INCLUDE_DIR | ${includeDir}`);
  }
}

if (!libDir) {
  libDir = `${defaultDir}/lib`;
  if (!fs.existsSync(libDir)) {
    throw new Error(`not found: process.env.OPENCV_LIB_DIR | ${libDir}`);
  }
}

const opencv2Include = resolvePath(includeDir, 'opencv2');

const getModulesHaveHeader = () => new Promise((resolve) => {
  fs.readdir(opencv2Include, (err, files) => {
    if (err) throw(err);
    const foundHeaders = [];
    modules.forEach(m => {
      if (!files.some(file => file.includes(`${m}.h`))) {
        throw new Error(`'${m}.h' not found in ${opencv2Include}`);
      }
      foundHeaders.push(m);
    });
    xmodules.forEach(m => {
      if (files.some(file => file.includes(`${m}.h`))) {
        foundHeaders.push(m);
      }
    });
    resolve(foundHeaders);
  });
});

const getLibs = () => new Promise((resolve) => {
  fs.readdir(resolvePath(libDir), (err, files) => {
    if (err) throw(err);
    let libsInDir = files.filter(f => f.includes(libSuffix) || f.includes(libSuffixOSX));

    if (!libsInDir.length) {
      throw new Error(`no valid .so, .lib or .dylib files found in in OPENCV_LIB_DIR ('${libDir}')`);
    }

    // if modules bundled in single lib file
    const world = libsInDir.find(file => file.includes('world'));
    if (world) {
      return resolve([{
        module: 'world',
        lib: resolvePath(libDir, world)
      }]);
    }

    const libs = [];
    modules.forEach(m => {
      let lib = libsInDir.find(file => file.includes(m) || file.includes(libPrefixOSX + m));

      if (!lib) {
        throw new Error(`lib for module '${m}' not found in OPENCV_LIB_DIR ('${libDir}')`);
      }
      libs.push({
        module: m,
        lib: resolvePath(libDir, lib)
      });
    });
    xmodules.forEach(m => {
      const lib = libsInDir.find(file => file.includes(m));
      if (lib) {
        libs.push({
          module: m,
          lib: resolvePath(libDir, lib)
        });
      }
    })
    resolve(libs);
  });
});

module.exports = {
  modules,
  xmodules,
  includeDir,
  getModulesHaveHeader,
  getLibs,
  resolvePath
};
