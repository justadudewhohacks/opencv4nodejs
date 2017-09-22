const cv = global.dut;
const { expect } = require('chai');

module.exports = () => {
  describe('HOGDescriptor', () => {
    describe('constructor', () => {
      it('should be constructable with default args', () => {
        const hog = new cv.HOGDescriptor();
        ['winSize', 'blockSize', 'blockStride', 'cellSize'].forEach(
          prop => expect(hog).to.have.property(prop).instanceOf(cv.Size)
        );
      });

      it('should be constructable with custom args', () => {
        const hog = new cv.HOGDescriptor({
          winSize: new cv.Size(40, 40),
          blockSize: new cv.Size(20, 20),
          blockStride: new cv.Size(10, 10),
          cellSize: new cv.Size(30, 30),
          nbins: 18,
          derivAperture: 2,
          winSigma: 1.8,
          L2HysThreshold: 0.4,
          gammaCorrection: true,
          signedGradient: true
        });
        [{ p: 'winSize', dim: 40 }, { p: 'blockSize', dim: 20 }, { p: 'blockStride', dim: 10 }, { p: 'cellSize', dim: 30 }].forEach(
          (pv) => {
            expect(hog).to.have.property(pv.p).instanceOf(cv.Size);
            const { width, height } = hog[pv.p];
            expect(width).to.equal(pv.dim);
            expect(height).to.equal(pv.dim);
          }
        );
        expect(hog).to.have.property('nbins').to.equal(18);
        expect(hog).to.have.property('derivAperture').to.equal(2);
        expect(hog).to.have.property('winSigma').to.equal(1.8);
        expect(hog).to.have.property('L2HysThreshold').to.equal(0.4);
        expect(hog).to.have.property('gammaCorrection').to.be.true;
        expect(hog).to.have.property('signedGradient').to.be.true;
      });

      it('should implement compute', () => {
        const hog = new cv.HOGDescriptor();
        expect(hog).to.have.property('compute').to.be.a('function');
      });
    });

    describe('compute', () => {
      it('should be callable with single channel img', () => {
        const desc = new cv.HOGDescriptor().compute({
          img: new cv.Mat(200, 200, cv.cvTypes.CV_8U)
        });
        expect(desc).to.be.an('array');
      });

      it('should be callable with triple channel img', () => {
        const desc = new cv.HOGDescriptor().compute({
          img: new cv.Mat(200, 200, cv.cvTypes.CV_8UC3)
        });
        expect(desc).to.be.an('array');
      });
    });
  });
};
