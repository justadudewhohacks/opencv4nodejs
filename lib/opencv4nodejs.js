const path = require('path');
const binding = require('../build/Release/opencv4nodejs');
const { resolvePath } = require('./utils');

// resolve haarcascade files
const { haarCascades } = binding.cvTypes;
Object.keys(haarCascades).forEach(
  key => haarCascades[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));

module.exports = binding;