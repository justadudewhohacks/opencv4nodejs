const path = require('path');
const { expect } = require('chai');

module.exports = function ({ cv, utils, getTestImg }) {

  const {
    generateAPITests,
    cvVersionGreaterEqual
  } = utils;

  const getClassifier = () => cvVersionGreaterEqual(3, 1, 0)
    ? cv.loadOCRHMMClassifierCNN(path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz'))
    : cv.loadOCRHMMClassifierNM(path.resolve('../data/text-models/OCRHMM_knn_model_data.xml.gz'));

  const getMask = () => new cv.Mat(getTestImg().rows, getTestImg().cols, cv.CV_8U, 1);

  describe('constructor', () => {

  });

  const vocabulary = 'abcdefghijklmnopqrstuvwxyz';
  const transitionP = new cv.Mat(62, 62, cv.CV_64F, 1.0);
  const emissionP = cv.Mat.eye(62, 62, cv.CV_64F);

  describe('run', () => {
    const confidence = 1;

    let dut;
    before(() => {
      dut = new cv.OCRHMMDecoder(getClassifier(), vocabulary, transitionP, emissionP);
    });

    generateAPITests({
      getDut: () => dut,
      methodName: 'run',
      methodNameSpace: 'OCRHMMDecoder',
      getRequiredArgs: () => ([
        getTestImg().bgrToGray(),
        confidence
      ]),
      getOptionalArg: cvVersionGreaterEqual(3, 1, 0) ? getMask : undefined,
      expectOutput: (ret) => {
        expect(ret).to.be.an('string');
      }
    });
  });

  describe('runWithInfo', () => {
    let dut;
    before(() => {
      dut = new cv.OCRHMMDecoder(getClassifier(), vocabulary, transitionP, emissionP);
    });

    generateAPITests({
      getDut: () => dut,
      methodName: 'runWithInfo',
      methodNameSpace: 'OCRHMMDecoder',
      getRequiredArgs: () => ([
        getTestImg().bgrToGray()
      ]),
      getOptionalArg: cvVersionGreaterEqual(3, 1, 0) ? getMask : undefined,
      expectOutput: (ret) => {
        expect(ret).to.have.property('outputText');
        expect(ret).to.have.property('rects');
        expect(ret).to.have.property('words');
        expect(ret).to.have.property('confidences');
      }
    });
  });

};
