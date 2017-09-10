import cv from 'dut';
import { expect } from 'chai';
import { assertMetaData } from 'utils';

module.exports = () => {
  describe.skip('TrainData', () => {
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
        const varIdx = new cv.Mat(3, 1, cv.cvTypes.CV_8U);
        const sampleIdx = new cv.Mat(3, 1, cv.cvTypes.CV_8U);
        const sampleWeights = new cv.Mat(3, 1, cv.cvTypes.CV_32F);
        const varType = new cv.Mat(3, 1, cv.cvTypes.CV_8U);
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
        expect(trainData).to.have.property('sampleIdx');
        expect(trainData).to.have.property('sampleWeights');
        expect(trainData).to.have.property('varType');
        assertMetaData(trainData.sampleIdx)(sampleIdx);
        assertMetaData(trainData.sampleWeights)(sampleWeights);
        assertMetaData(trainData.varType)(varType);
      });

      it('should be constructable with some optional args', () => {
        const varIdx = new cv.Mat(3, 3, cv.cvTypes.CV_8U);
        const trainData = new cv.TrainData(
          new cv.Mat(3, 3, cv.cvTypes.CV_32F),
          cv.cvTypes.sampleTypes.ROW_SAMPLE,
          new cv.Mat(3, 1, cv.cvTypes.CV_32F),
          varIdx
        );
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('varIdx');
        assertMetaData(trainData.varIdx)(varIdx);
      });

      it('should be constructable with optional args object', () => {
        const opts = {
          sampleWeights: new cv.Mat()
        };
        const trainData = new cv.TrainData(
          new cv.Mat(3, 3, cv.cvTypes.CV_32F),
          cv.cvTypes.sampleTypes.ROW_SAMPLE,
          new cv.Mat(3, 1, cv.cvTypes.CV_32F),
          opts
        );
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('sampleWeights').to.equal(opts.sampleWeights);
      });
    });
  });
};
