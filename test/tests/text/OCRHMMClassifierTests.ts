import path from 'path';
import { expect } from 'chai';
import { TestContext } from '../model';

export default function (args: TestContext) {
  const { cv, utils, getTestImg } = args;
  const {
    generateAPITests,
    cvVersionGreaterEqual,
  } = utils;

  const getClassifier = () => (cvVersionGreaterEqual(3, 1, 0)
    ? cv.loadOCRHMMClassifierCNN(path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz'))
    : cv.loadOCRHMMClassifierNM(path.resolve('../data/text-models/OCRHMM_knn_model_data.xml.gz')));

  describe('eval', () => {
    generateAPITests({
      getDut: getClassifier,
      methodName: 'eval',
      methodNameSpace: 'OCRHMMClassifier',
      getRequiredArgs: () => ([
        getTestImg().bgrToGray(),
      ]),
      expectOutput: (ret) => {
        expect(ret).to.have.property('classes').to.be.an('array');
        expect(ret).to.have.property('confidences').to.be.an('array');
      },
    });
  });
}
