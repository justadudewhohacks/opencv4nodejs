const cv = global.dut;
const {
  generateAPITests,
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

      it('should implement detectMultiScaleAsync', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleAsync').to.be.a('function');
      });

      it('should implement detectMultiScaleWithRejectLevelsAsync', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleWithRejectLevelsAsync').to.be.a('function');
      });
    });

    describe('detect', () => {
      let cc;
      let testImg;

      before(() => {
        cc = new cv.CascadeClassifier(xmlHaarFile);
        testImg = readTestImage();
      });

      const getRequiredArgs = () => ([
        testImg
      ]);
      const getOptionalArgsMap = () => ([
        ['scaleFactor', 1.2],
        ['minNeighbors', 5],
        ['flags', 0],
        ['minSize', new cv.Size(50, 50)],
        ['maxSize', new cv.Size(250, 250)]
      ]);

      describe('detectMultiScale', () => {
        const expectOutput = (ret) => {
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('numDetections').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.numDetections.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        };

        generateAPITests({
          getDut: () => cc,
          methodName: 'detectMultiScale',
          methodNameSpace: 'CascadeClassifier',
          getRequiredArgs,
          getOptionalArgsMap,
          expectOutput
        });
      });

      (cv.version.minor === 1 ? describe.skip : describe)('detectMultiScaleWithRejectLevels', () => {
        const expectOutput = (ret) => {
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('rejectLevels').to.be.an('array');
          expect(ret).to.have.property('levelWeights').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.rejectLevels.length).to.be.above(0);
          expect(ret.levelWeights.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        };

        generateAPITests({
          getDut: () => cc,
          methodName: 'detectMultiScaleWithRejectLevels',
          methodNameSpace: 'CascadeClassifier',
          getRequiredArgs,
          getOptionalArgsMap,
          expectOutput
        });
      });
    });
  });
};
