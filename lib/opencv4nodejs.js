const binary = require('node-pre-gyp');
const path = require('path');
const bindingPath = binary.find(path.resolve(path.join(__dirname, '../package.json')), { debug: !!process.env.DEBUG });
const binding = require(bindingPath);
const { resolvePath } = require('./utils');

// resolve haarcascade files
const { haarCascades } = binding.cvTypes;
Object.keys(haarCascades).forEach(
  key => haarCascades[key] = resolvePath(path.join(__dirname, './haarcascades'), haarCascades[key]));

module.exports = binding;