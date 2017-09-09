import cv from 'dut';
import { expect } from 'chai';

module.exports = () => {
  describe('TrainData', () => {
    describe('constructor', () => {
      it('should be constructable without args', () => {
        expect(new cv.TrainData()).to.be.instanceOf(cv.TrainData);
      });

      it('should be constructable from arguments', () => {
        const samples = new cv.Mat(3, 3, cv.cvTypes.CV_64F);
        const layout = cv.cvTypes.sampleTypes.ROW_SAMPLE;
        const responses = new cv.Mat(1, 1, cv.cvTypes.CV_64F);
        const trainData = new cv.TrainData(samples, layout, responses);
        console.log("trainData")
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('samples').to.equal(samples);
        expect(trainData).to.have.property('layout').to.equal(layout);
        expect(trainData).to.have.property('responses').to.equal(responses);
      });

      it('should be constructable with all optional args', () => {
        const varIdx = new cv.Mat(3, 1, cv.cvTypes.CV_64F);
        const sampleIdx = new cv.Mat(3, 1, cv.cvTypes.CV_64F);
        const sampleWeights = new cv.Mat(3, 1, cv.cvTypes.CV_64F);
        const varType = new cv.Mat(3, 1, cv.cvTypes.CV_64F);
        const trainData = new cv.TrainData(new cv.Mat(), new cv.Mat(), cv.cvTypes.sampleTypes.ROW_SAMPLE, varIdx, sampleIdx, sampleWeights, varType);
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('varIdx').to.equal(varIdx);
        expect(trainData).to.have.property('sampleIdx').to.equal(sampleIdx);
        expect(trainData).to.have.property('sampleWeights').to.equal(sampleWeights);
        expect(trainData).to.have.property('varType').to.equal(varType);
      });

      it('should be constructable with some optional args', () => {
        const varIdx = new cv.Mat(3, 1, cv.cvTypes.CV_64F);
        const trainData = new cv.TrainData(new cv.Mat(3, 1, cv.cvTypes.CV_64F), new cv.Mat(3, 1, cv.cvTypes.CV_64F), cv.cvTypes.sampleTypes.ROW_SAMPLE, varIdx);
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('varIdx').to.equal(varIdx);
      });

      it('should be constructable with optional args object', () => {
        const opts = {
          sampleWeights: new cv.Mat()
        };
        const trainData = new cv.TrainData(new cv.Mat(), new cv.Mat(), cv.cvTypes.sampleTypes.ROW_SAMPLE, opts);
        expect(trainData).to.be.instanceOf(cv.TrainData);
        expect(trainData).to.have.property('sampleWeights').to.equal(opts.sampleWeights);
      });
    });
  });
};
