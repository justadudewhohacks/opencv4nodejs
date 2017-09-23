const cv = global.dut;
const {
  funcShouldRequireArgs,
  readTestImage
} = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('CascadeClassifier', () => {
    const xmlHaarFile = cv.HAAR_FRONTALFACE_DEFAULT;

    describe('constructor', () => {
      funcShouldRequireArgs(() => new cv.CascadeClassifier());

      it('should be constructable with xmlFilePath', () => {
        expect(() => new cv.CascadeClassifier(xmlHaarFile)).to.not.throw();
      });

      it('should implement detectMultiScale', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScale').to.be.a('function');
      });

      it('should implement detectMultiScaleWithRejectLevels', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleWithRejectLevels').to.be.a('function');
      });
    });

    describe('detect', () => {
      let cc;
      let testImg;

      before(() => {
        cc = new cv.CascadeClassifier(xmlHaarFile);
        testImg = readTestImage();
      });

      const scaleFactor = 1.2;
      const minNeighbors = 5;
      const flags = 0;
      const minSize = new cv.Size(50, 50);
      const maxSize = new cv.Size(250, 250);

      describe('detectMultiScale', () => {
        funcShouldRequireArgs(() => cc.detectMultiScale());

        it('can be called if required args passed', () => {
          expect(() => cc.detectMultiScale(testImg)).to.not.throw();
        });

        it('can be called with optional args', () => {
          expect(() => cc.detectMultiScale(
            testImg,
            scaleFactor,
            minNeighbors,
            flags,
            minSize,
            maxSize
          )).to.not.throw();
        });

        it('can be called with optional args object', () => {
          expect(() => cc.detectMultiScale(
            testImg,
            {
              scaleFactor,
              minNeighbors,
              minSize,
              maxSize
            }
          )).to.not.throw();
        });

        it('should return objects and numDetections', () => {
          const ret = cc.detectMultiScale(testImg);
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('numDetections').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.numDetections.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        });
      });

      describe('detectMultiScaleWithRejectLevels', () => {
        funcShouldRequireArgs(() => cc.detectMultiScaleWithRejectLevels());

        it('can be called if required args passed', () => {
          expect(() => cc.detectMultiScaleWithRejectLevels(testImg)).to.not.throw();
        });

        it('can be called with optional args', () => {
          expect(() => cc.detectMultiScaleWithRejectLevels(
            testImg,
            scaleFactor,
            minNeighbors,
            flags,
            minSize,
            maxSize
          )).to.not.throw();
        });

        it('can be called with optional args object', () => {
          expect(() => cc.detectMultiScaleWithRejectLevels(
            testImg,
            {
              scaleFactor,
              minNeighbors,
              minSize,
              maxSize
            }
          )).to.not.throw();
        });

        it('should return objects, rejectLevels and levelWeights', () => {
          const ret = cc.detectMultiScaleWithRejectLevels(testImg);
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('rejectLevels').to.be.an('array');
          expect(ret).to.have.property('levelWeights').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.rejectLevels.length).to.be.above(0);
          expect(ret.levelWeights.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        });
      });
    });
  });
};
