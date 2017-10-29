const cv = global.dut;
const {
  assertMetaData,
  generateAPITests
} = global.utils;

const path = require('path');
const { expect } = require('chai');

const OCRHMMClassifierTests = require('./OCRHMMClassifierTests');
const OCRHMMDecoderTests = require('./OCRHMMDecoderTests');

describe('text', () => {
  if (!cv.xmodules.text) {
    it('compiled without text');
    return;
  }

  OCRHMMClassifierTests();
  OCRHMMDecoderTests();

  describe('loadOCRHMMClassifierNM', () => {
    generateAPITests({
      getDut: () => cv,
      methodName: 'loadOCRHMMClassifierNM',
      getRequiredArgs: () => ([
        path.resolve('../data/text-models/OCRHMM_knn_model_data.xml.gz')
      ]),
      expectOutput: (classifier) => {
        expect(classifier).to.be.instanceOf(cv.OCRHMMClassifier);
      }
    });
  });

  if (cv.version.minor > 0) {
    describe('loadOCRHMMClassifierCNN', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'loadOCRHMMClassifierCNN',
        getRequiredArgs: () => ([
          path.resolve('../data/text-models/OCRBeamSearch_CNN_model_data.xml.gz')
        ]),
        expectOutput: (classifier) => {
          expect(classifier).to.be.instanceOf(cv.OCRHMMClassifier);
        }
      });
    });

    describe('createOCRHMMTransitionsTable', () => {
      const vocabulary = 'abcdefghijklmnopqrstuvwxyz';
      const lexicon = ['foo', 'bar', 'what', 'the', 'heck'];

      generateAPITests({
        getDut: () => cv,
        methodName: 'createOCRHMMTransitionsTable',
        getRequiredArgs: () => ([
          vocabulary,
          lexicon
        ]),
        expectOutput: (transitionPTable) => {
          expect(transitionPTable).to.be.instanceOf(cv.Mat);
          assertMetaData(transitionPTable)(26, 26, cv.CV_64F);
        }
      });
    });
  }
});
