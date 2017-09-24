const path = require('path');
let binding;
if (process.env.BINDINGS_DEBUG) {
  console.log('process.env.BINDINGS_DEBUG is true')
  binding = require('../build/Debug/opencv4nodejs');
} else {
  binding = require('../build/Release/opencv4nodejs');
}

const { resolvePath } = require('./utils');

// resolve haarcascade files
const { haarCascades } = binding;
Object.keys(haarCascades).forEach(
  key => binding[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));

module.exports = binding;