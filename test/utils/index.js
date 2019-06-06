const testUtils = require('./testUtils');
const matTestUtils = require('./matTestUtils');
const defaultTests = require('./defaultTests');
const cv = global.dut;

const getNodeMajorVersion = () => parseInt(process.version.split('.')[0].slice(1))
const cvVersionGreaterEqual = (major, minor, revision) =>
  cv.version.major > major
  || (cv.version.major === major && cv.version.minor >= minor)
  || (cv.version.major === major && cv.version.minor === minor && cv.version.revision >= revision)
const cvVersionLowerThan = (major, minor, revision) => !cvVersionGreaterEqual(major, minor, revision)
const cvVersionEqual = (major, minor, revision) =>
  cv.version.major === major && cv.version.minor === minor && cv.version.revision === revision

module.exports = Object.assign(
  {},
  testUtils,
  matTestUtils,
  defaultTests,
  { getNodeMajorVersion, cvVersionGreaterEqual }
);
