import type openCV from '@u4/opencv4nodejs';
import * as testUtils from './testUtils';
import { generateAPITests } from './generateAPITests';
import matTestUtilsFactory from './matTestUtils';
import readExampleImagesFactory from './readExampleImages';
import generateClassMethodTestsFactory from './generateClassMethodTests';

const getNodeMajorVersion = () => parseInt(process.version.split('.')[0].slice(1))

export default function(cv: typeof openCV) {
  const cvVersionGreaterEqual = (major: number, minor: number, revision: number): boolean => cv.version.major > major
    || (cv.version.major === major && cv.version.minor > minor)
    || (cv.version.major === major && cv.version.minor === minor && cv.version.revision >= revision)
  const cvVersionLowerThan = (major: number, minor: number, revision: number): boolean => !cvVersionGreaterEqual(major, minor, revision)
  const cvVersionEqual = (major: number, minor: number, revision: number): boolean =>
    cv.version.major === major && cv.version.minor === minor && cv.version.revision === revision

  const matTestUtils = matTestUtilsFactory(cv);
  const readExampleImages = readExampleImagesFactory(cv);
  const generateClassMethodTests = generateClassMethodTestsFactory(cv);

  return {
    ...testUtils,
    ...matTestUtils,
    ...readExampleImages,
    cvVersionGreaterEqual,
    cvVersionLowerThan,
    cvVersionEqual,
    generateAPITests,
    generateClassMethodTests,
    getNodeMajorVersion
  };
};
