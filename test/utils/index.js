const testUtils = require('./testUtils');
const matTestUtils = require('./matTestUtils');
const defaultTests = require('./defaultTests');

module.exports = Object.assign(
  {},
  testUtils,
  matTestUtils,
  defaultTests
);
