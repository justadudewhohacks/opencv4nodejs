const opencvBuild = require('opencv-build');
const { resolvePath, getLibDir } = require('./commons');

function linkLibs(libs) {
  libs
    .map(lib => lib.libPath)
    .filter(libPath => libPath)
    .forEach(libPath => console.log(resolvePath(libPath)));
}

if (opencvBuild.isAutoBuildDisabled()) {
  linkLibs(opencvBuild.getLibs(getLibDir()));
  return;
}

// get libs from auto build
if (process.platform === 'win32') {
  linkLibs(opencvBuild.getLibs(resolvePath(opencvBuild.opencvLibDir)));
  return;
}

// if not windows, link libs dynamically
console.log('-L' + resolvePath(opencvBuild.opencvLibDir));
opencvBuild.opencvModules.forEach(lib => console.log('-lopencv_' + lib));
console.log('-Wl,-rpath,' + resolvePath(opencvBuild.opencvLibDir));
