const path = require('path');
const binding = require('../build/Release/opencv4nodejs');
const { resolvePath } = require('./utils');

// resolve haarcascade files
const { haarCascades } = binding;
Object.keys(haarCascades).forEach(
  key => binding[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));

module.exports = binding;