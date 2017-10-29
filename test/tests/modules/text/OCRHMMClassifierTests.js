const cv = global.dut;
const {
  readTestImage,
  generateAPITests
} = global.utils;

const path = require('path');
const { expect } = require('chai');

module.exports = () => {
  describe('OCRHMMClassifier', () => {
    let classifier;
    let testImg;

    before(() => {
      classifier = cv.version.minor > 0
        ? cv.loadOCRHMMClassifierCNN(path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz'))
        : cv.loadOCRHMMClassifierNM(path.resolve('../data/text-models/OCRHMM_knn_model_data.xml.gz'));
      testImg = readTestImage().bgrToGray();
    });

    describe('eval', () => {
      generateAPITests({
        getDut: () => classifier,
        methodName: 'eval',
        methodNameSpace: 'OCRHMMClassifier',
        getRequiredArgs: () => ([
          testImg
        ]),
        expectOutput: (ret) => {
          expect(ret).to.have.property('classes').to.be.an('array');
          expect(ret).to.have.property('confidences').to.be.an('array');
        }
      });
    });
  });
};
