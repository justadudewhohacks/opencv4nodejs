const { modules, xmodules, getModulesHaveHeader, getLibs } = require('./utils');

Promise.all([getModulesHaveHeader(), getLibs()]).then(([modulesHaveHeader, libs]) => {
  modules.concat(xmodules).forEach(m => {
    if (modulesHaveHeader.some(_m => _m === m) && libs.some(({ module: _m }) => _m === m)) {
      console.log(`HAVE_${m.toUpperCase()}`);
    }
  });
});