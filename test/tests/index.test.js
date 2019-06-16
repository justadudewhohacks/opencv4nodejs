const cv = require('../requireCv')();
const utils = require('../utils')(cv);

const coreTestSuite = require('./core')
const imgprocTestSuite = require('./imgproc')
const calib3dTestSuite = require('./calib3d')
const features2dTestSuite = require('./features2d')

describe('cv', () => {

  const {
    readTestImage
  } = utils

  console.log(cv.modules)

  let testImg = null;
  const getTestImg = () => {
    if (testImg === null) {
      throw new Error('getTestImg not defined, before hook not called yet');

    }
    return testImg;
  };
  before(() => {
    testImg = utils.readTestImage();
  });

  if (cv.modules.core) {
    describe('core', () => coreTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.imgproc) {
    describe('imgproc', () => imgprocTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.calib3d) {
    describe('calib3d', () => calib3dTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.features2d) {
    describe('features2d', () => features2dTestSuite({ cv, utils, getTestImg }));
  }

})
