const testUtils = require('./testUtils');
const { generateAPITests } = require('./generateAPITests');
const matTestUtilsFactory = require('./matTestUtils');
const readExampleImagesFactory = require('./readExampleImages');
const generateClassMethodTestsFactory = require('./generateClassMethodTests');

const getNodeMajorVersion = () => parseInt(process.version.split('.')[0].slice(1))

module.exports = function(cv) {
  const cvVersionGreaterEqual = (major, minor, revision) =>
    cv.version.major > major
    || (cv.version.major === major && cv.version.minor > minor)
    || (cv.version.major === major && cv.version.minor === minor && cv.version.revision >= revision)
  const cvVersionLowerThan = (major, minor, revision) => !cvVersionGreaterEqual(major, minor, revision)
  const cvVersionEqual = (major, minor, revision) =>
    cv.version.major === major && cv.version.minor === minor && cv.version.revision === revision

  const matTestUtils = matTestUtilsFactory(cv);
  const readExampleImages = readExampleImagesFactory(cv);
  const generateClassMethodTests = generateClassMethodTestsFactory(cv);

  return Object.assign(
    {},
    testUtils,
    matTestUtils,
    readExampleImages,
    {
      cvVersionGreaterEqual,
      cvVersionLowerThan,
      cvVersionEqual,
      generateAPITests,
      generateClassMethodTests,
      getNodeMajorVersion
    }
  );
};
