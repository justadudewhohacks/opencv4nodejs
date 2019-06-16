const cv = require('../requireCv')();
const utils = require('../utils')(cv);
const { expect } = require('chai');

const coreTestSuite = require('./core')
const imgprocTestSuite = require('./imgproc')
const calib3dTestSuite = require('./calib3d')
const features2dTestSuite = require('./features2d')
const ioTestSuite = require('./io')
const dnnTestSuite = require('./dnn')
const machinelearningTestSuite = require('./machinelearning')
const faceTestSuite = require('./face')
const objdetectTestSuite = require('./objdetect')
const photoTestSuite = require('./photo')
const textTestSuite = require('./text')
const trackingTestSuite = require('./tracking')
const videoTestSuite = require('./video')
const xfeatures2dTestSuite = require('./xfeatures2d')
const ximgprocTestSuite = require('./ximgproc')

describe('cv', () => {

  console.log(cv.modules)

  let testImg = null;
  let peoplesTestImg = null;

  const getTestImg = () => {
    if (testImg === null) {
      throw new Error('getTestImg not defined, before hook not called yet');
    }
    return testImg;
  };

  const getPeoplesTestImg = () => {
    if (peoplesTestImg === null) {
      throw new Error('getPeoplesTestImg not defined, before hook not called yet');
    }
    return peoplesTestImg;
  };

  before(() => {
    testImg = utils.readTestImage();
    peoplesTestImg = utils.readPeoplesTestImage();
  });

  if (!process.env.TEST_MODULE_LIST) {
    it('all modules should be built', () => {
      const modules = [
        'core', 'imgproc',  'calib3d', 'features2d', 'io',
        'dnn', 'ml', 'face', 'objdetect', 'photo', 'text',
        'tracking', 'video', 'xfeatures2d', 'ximgproc'
      ]
      modules.forEach(m => expect(cv.modules).to.have.property(m));
    })
  }

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

  if (cv.modules.objdetect) {
    describe('objdetect', () => objdetectTestSuite({ cv, utils, getTestImg, getPeoplesTestImg }));
  }

  if (cv.modules.photo) {
    describe('photo', () => photoTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.text) {
    describe('text', () => textTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.tracking) {
    describe('tracking', () => trackingTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.video) {
    describe('video', () => videoTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.xfeatures2d) {
    describe('xfeatures2d', () => xfeatures2dTestSuite({ cv, utils, getTestImg }));
  }

  if (cv.modules.ximgproc) {
    describe('ximgproc', () => ximgprocTestSuite({ cv, utils, getTestImg }));
  }

})
