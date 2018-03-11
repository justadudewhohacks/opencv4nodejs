const opencvBuild = require('opencv-build');
const { resolvePath, defaultDir } = require('./commons');

if (opencvBuild.isAutoBuildDisabled()) {
  console.log(resolvePath(process.env.OPENCV_INCLUDE_DIR) || `${defaultDir}/include`);
  return;
}

// set include dir from auto build
console.log(resolvePath(opencvBuild.opencvInclude));
