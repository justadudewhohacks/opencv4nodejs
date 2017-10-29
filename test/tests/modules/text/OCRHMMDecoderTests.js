const cv = global.dut;
const {
  readTestImage,
  generateAPITests
} = global.utils;

const path = require('path');
const { expect } = require('chai');

module.exports = () => {
  describe('OCRHMMDecoder', () => {
    let classifier;
    let testImg;
    let mask;

    before(() => {
      classifier = cv.version.minor > 0
        ? cv.loadOCRHMMClassifierCNN(path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz'))
        : cv.loadOCRHMMClassifierNM(path.resolve('../data/text-models/OCRHMM_knn_model_data.xml.gz'));
      testImg = readTestImage().bgrToGray();
      mask = new cv.Mat(testImg.rows, testImg.cols, cv.CV_8U, 1);
    });

    describe('constructor', () => {

    });

    const vocabulary = 'abcdefghijklmnopqrstuvwxyz';
    const transitionP = new cv.Mat(62, 62, cv.CV_64F, 1.0);
    const emissionP = cv.Mat.eye(62, 62, cv.CV_64F);

    describe('run', () => {
      const confidence = 1;

      let dut;
      before(() => {
        dut = new cv.OCRHMMDecoder(classifier, vocabulary, transitionP, emissionP);
      });

      generateAPITests({
        getDut: () => dut,
        methodName: 'run',
        methodNameSpace: 'OCRHMMDecoder',
        getRequiredArgs: () => ([
          testImg,
          confidence
        ]),
        getOptionalArgs: () => (cv.version.minor > 0 ? ([
          mask
        ]) : ([])),
        expectOutput: (ret) => {
          expect(ret).to.be.an('string');
        }
      });
    });

    describe('runWithInfo', () => {
      let dut;
      before(() => {
        dut = new cv.OCRHMMDecoder(classifier, vocabulary, transitionP, emissionP);
      });

      generateAPITests({
        getDut: () => dut,
        methodName: 'runWithInfo',
        methodNameSpace: 'OCRHMMDecoder',
        getRequiredArgs: () => ([
          testImg
        ]),
        getOptionalArgs: () => (cv.version.minor > 0 ? ([
          mask
        ]) : ([])),
        expectOutput: (ret) => {
          expect(ret).to.have.property('outputText');
          expect(ret).to.have.property('rects');
          expect(ret).to.have.property('words');
          expect(ret).to.have.property('confidences');
        }
      });
    });
  });
};
