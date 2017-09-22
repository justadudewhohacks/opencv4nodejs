const cv = global.dut;
const { expect } = require('chai');
const { assertMetaData } = global.utils;

module.exports = () => {
  describe('TrainData', () => {
    const cvVarType = cv.cvTypes.variableTypes.VAR_ORDERED;
    describe('constructor', () => {
      it('should be constructable without args', () => {
        expect(new cv.TrainData()).to.be.instanceOf(cv.TrainData);
      });

      it('should be constructable from arguments', () => {
        const samples = new cv.Mat(3, 3, cv.cvTypes.CV_32F);
        const layout = cv.cvTypes.sampleTypes.ROW_SAMPLE;
        const responses = new cv.Mat(3, 1, cv.cvTypes.CV_32F);
        const trainData = new cv.TrainData(samples, layout, responses);

        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('layout').to.equal(layout);
        expect(trainData).to.have.property('samples');
        expect(trainData).to.have.property('responses');
        assertMetaData(trainData.samples)(samples);
        assertMetaData(trainData.responses)(responses);
      });

      it('should be constructable with all optional args', () => {
        const varIdx = [0, 1, 2];
        const sampleIdx = [0, 1, 2];
        const sampleWeights = [0, 0.1, 0.5];
        const varType = [cvVarType, cvVarType, cvVarType, cvVarType];
        const trainData = new cv.TrainData(
          new cv.Mat(3, 3, cv.cvTypes.CV_32F),
          cv.cvTypes.sampleTypes.ROW_SAMPLE,
          new cv.Mat(3, 1, cv.cvTypes.CV_32F),
          varIdx,
          sampleIdx,
          sampleWeights,
          varType
        );
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('varIdx');
        expect(trainData).to.have.property('sampleWeights');
        expect(trainData).to.have.property('varType');
        assertMetaData(trainData.varIdx)(1, 3, cv.cvTypes.CV_32S);
        assertMetaData(trainData.sampleWeights)(1, 3, cv.cvTypes.CV_32F);
        assertMetaData(trainData.varType)(1, 4, cv.cvTypes.CV_8U);
      });

      it('should be constructable with some optional args', () => {
        const varIdx = [0, 1, 2];
        const trainData = new cv.TrainData(
          new cv.Mat(3, 3, cv.cvTypes.CV_32F),
          cv.cvTypes.sampleTypes.ROW_SAMPLE,
          new cv.Mat(3, 1, cv.cvTypes.CV_32F),
          varIdx
        );
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('varIdx');
        assertMetaData(trainData.varIdx)(1, 3, cv.cvTypes.CV_32S);
      });

      it('should be constructable with optional args object', () => {
        const opts = {
          sampleWeights: [0, 0.1, 0.5]
        };
        const trainData = new cv.TrainData(
          new cv.Mat(3, 3, cv.cvTypes.CV_32F),
          cv.cvTypes.sampleTypes.ROW_SAMPLE,
          new cv.Mat(3, 1, cv.cvTypes.CV_32F),
          opts
        );
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('sampleWeights');
        assertMetaData(trainData.sampleWeights)(1, 3, cv.cvTypes.CV_32F);
      });
    });
  });
};
