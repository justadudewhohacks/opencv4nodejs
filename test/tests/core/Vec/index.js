const VecTests = require('./VecTests');
const constructorTests = require('./constructorTests');
const operatorTests = require('./operatorTests');

module.exports = function (args) {
  describe('Vec', () => VecTests(args));
  describe('constructor', () => constructorTests(args));
  describe('operators', () => operatorTests(args));
};