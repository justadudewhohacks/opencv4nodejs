const testUtils = require('./testUtils');
const matTestUtils = require('./matTestUtils');
const generateAPITests = require('./generateAPITests');
const generateClassMethodTests = require('./generateClassMethodTests');
const cv = global.dut;

const getNodeMajorVersion = () => parseInt(process.version.split('.')[0].slice(1))
const cvVersionGreaterEqual = (major, minor, revision) =>
  cv.version.major > major
  || (cv.version.major === major && cv.version.minor > minor)
  || (cv.version.major === major && cv.version.minor === minor && cv.version.revision >= revision)
const cvVersionLowerThan = (major, minor, revision) => !cvVersionGreaterEqual(major, minor, revision)
const cvVersionEqual = (major, minor, revision) =>
  cv.version.major === major && cv.version.minor === minor && cv.version.revision === revision

module.exports = Object.assign(
  {},
  testUtils,
  matTestUtils,
  generateAPITests,
  generateClassMethodTests,
  { getNodeMajorVersion, cvVersionGreaterEqual, cvVersionLowerThan, cvVersionEqual }
);
