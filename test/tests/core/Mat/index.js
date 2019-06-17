const MatTests = require('./MatTests');
const accessorTests = require('./accessorTests');
const constructorTestsFromJsArray = require('./constructorTestsFromJsArray');
const constructorTestsFromFillVector = require('./constructorTestsFromFillVector');
const operatorTests = require('./operatorTests');

module.exports = function (args) {
  describe('Mat', () => MatTests(args));
  describe('accessors', () => accessorTests(args));
  describe('constructor', () => {
    describe('from array', () => constructorTestsFromJsArray(args));
    describe('from fill vector', () => constructorTestsFromFillVector(args));
  });
  describe('operators', () => operatorTests(args));
};