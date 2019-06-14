const opencvBuild = require('opencv-build');
const { resolvePath, defaultIncludeDir, defaultIncludeDirOpenCV4 } = require('./commons');

if (opencvBuild.isAutoBuildDisabled()) {
  const explicitIncludeDir = resolvePath(process.env.OPENCV_INCLUDE_DIR);
  if (explicitIncludeDir) {
    console.log(explicitIncludeDir);
    return;
  }
  console.log(defaultIncludeDir);
  console.log(defaultIncludeDirOpenCV4);
  return;
}

// set include dir from auto build
console.log(resolvePath(opencvBuild.opencvInclude));
console.log(resolvePath(opencvBuild.opencv4Include));
