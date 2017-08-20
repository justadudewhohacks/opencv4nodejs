const { getLibs } = require('./utils');

getLibs().then(libs => libs.forEach(({ lib }) => console.log(lib)));
