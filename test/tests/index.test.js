const cv = require('../requireCv')();
const utils = require('../utils')(cv);

const coreTestSuite = require('./core')
const imgprocTestSuite = require('./imgproc')
const calib3dTestSuite = require('./calib3d')
const features2dTestSuite = require('./features2d')
const ioTestSuite = require('./io')
const dnnTestSuite = require('./dnn')
const machinelearningTestSuite = require('./machinelearning')
const faceTestSuite = require('./face')

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

  if (cv.modules.io) {
    describe('io', () => ioTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.dnn) {
    describe('dnn', () => dnnTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.machinelearning) {
    describe('machinelearning', () => machinelearningTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.face) {
    describe('face', () => faceTestSuite({ cv, utils, getTestImg }));
  }

})
