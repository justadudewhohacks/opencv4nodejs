const { modules, xmodules, getModulesHaveHeader, getLibs, opencvBuild } = require('./utils');

if (opencvBuild.hasSelfBuild()) {
  Promise.all([getModulesHaveHeader(), getLibs()]).then(([modulesHaveHeader, libs]) => {
    if (libs.some(({ module: _m }) =>  _m === 'world')) {
      modules.forEach(m => console.log(`HAVE_${m.toUpperCase()}`));
      return;
    }

    modules.concat(xmodules).forEach(m => {
      if (modulesHaveHeader.some(_m => _m === m) && libs.some(({ module: _m }) => _m === m)) {
        console.log(`HAVE_${m.toUpperCase()}`);
      }
    });
  });
  return;
}

// set defines from auto build
opencvBuild.opencvModules.forEach(m => console.log(`HAVE_${m.toUpperCase()}`));