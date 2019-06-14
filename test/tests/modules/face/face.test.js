const cv = global.dut;
const { readTestImage } = global.utils;
const recognizerTests = require('./recognizerTests');
const facemarkTests = require('./facemarkTests');
const facemarkStructsTests = require('./facemarkStructsTests');

describe('face', () => {
  if (!cv.modules.face) {
    it('compiled without face');
    return;
  }

  let testImg;

  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

  describe('EigenFaceRecognizer', () => {
    const args = ['num_components', 'threshold'];
    const values = [10, 0.8];
    recognizerTests(() => testImg, args, values, cv.EigenFaceRecognizer);
  });

  describe('FisherFaceRecognizer', () => {
    const args = ['num_components', 'threshold'];
    const values = [10, 0.8];
    recognizerTests(() => testImg, args, values, cv.FisherFaceRecognizer);
  });

  describe('LBPHFaceRecognizer', () => {
    const args = ['radius', 'neighbors', 'grid_x', 'grid_y'];
    const values = [2, 16, 16, 16];
    recognizerTests(() => testImg, args, values, cv.LBPHFaceRecognizer);
  });

  if (global.utils.cvVersionGreaterEqual(3, 4, 0)) {
    facemarkStructsTests();

    describe('FacemarkLBF', () => {
      facemarkTests(() => testImg, cv.FacemarkLBF, cv.FacemarkLBFParams);
    });

    describe('FacemarkAAM', () => {
      facemarkTests(() => testImg, cv.FacemarkAAM, cv.FacemarkAAMParams);
    });
  }
});
