const testUtils = require('./testUtils');
const matTestUtils = require('./matTestUtils');
const defaultTests = require('./defaultTests');

const getNodeMajorVersion = () => parseInt(process.version.split('.')[0].slice(1))

module.exports = Object.assign(
  {},
  testUtils,
  matTestUtils,
  defaultTests,
  { getNodeMajorVersion }
);
