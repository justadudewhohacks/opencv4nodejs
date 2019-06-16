const dnnTests = require('./dnnTests');
const NetTests = require('./NetTests');

module.exports = function (args) {
  describe('dnn', () => dnnTests(args));
  describe('Net', () => NetTests(args));
};