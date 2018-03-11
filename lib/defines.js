const opencvBuild = require('opencv-build');
const { getLibDir } = require('./commons');

if (opencvBuild.isAutoBuildDisabled()) {
  opencvBuild.getLibs(getLibDir())
    .filter(lib => lib.libPath)
    .map(lib => lib.opencvModule)
    .forEach(opencvModule => console.log(`HAVE_${opencvModule.toUpperCase()}`));

  return;
}

// set defines from auto build
opencvBuild.opencvModules.forEach(m => console.log(`HAVE_${m.toUpperCase()}`));