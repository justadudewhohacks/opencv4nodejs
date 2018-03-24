// require('segfault-handler').registerHandler('crash.log');

const requireCv = require('./dut');

// requiring cv has to happen before requiring utils
global.dut = requireCv();

global.utils = require('./utils');

