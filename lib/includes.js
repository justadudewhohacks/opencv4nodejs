const { includeDir, opencvBuild } = require('./utils');

if (opencvBuild.hasSelfBuild()) {
  console.log(includeDir);
  return;
}

// set include dir from auto build
opencvBuild.includes();
