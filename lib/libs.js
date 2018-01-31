const { getLibs, opencvBuild } = require('./utils');

if (opencvBuild.hasSelfBuild()) {
  getLibs().then(libs => libs.forEach(({ lib }) => console.log(lib)));
  return;
}

// get libs from auto build
opencvBuild.libraries();

