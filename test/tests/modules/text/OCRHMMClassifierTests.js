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
      classifier = cv.loadOCRHMMClassifierCNN(path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz'));
      testImg = readTestImage();
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
