const { assert, expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    assertMetaData,
    assertPropsWithValue,
    funcShouldRequireArgs,
    cvVersionGreaterEqual
  } = utils;

  describe('SuperpixelSEEDS', () => {
    const num_superpixels = 100;
    const num_levels = 2;

    describe('constructor', () => {
      it('should throw if no args', () => {
        expect(() => new cv.SuperpixelSEEDS()).to.throw('SuperpixelSEEDS::New - Error: expected argument 0 to be of type');
      });

      it('should be constructable with required args', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(getTestImg().resizeToMax(250), num_superpixels, num_levels);
        expect(superpixelSeeds).to.have.property('image').instanceOf(cv.Mat);
        assertMetaData(superpixelSeeds.image)({
          rows: 250, cols: 250, type: cv.CV_8UC3
        });
        assertPropsWithValue(superpixelSeeds)({
          num_superpixels,
          num_levels
        });
      });
    });

    // TODO: FIX ME
    describe('iterate', () => {
      it('should iterate with default values', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(getTestImg().resizeToMax(250), num_superpixels, num_levels);
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: 250, cols: 250, type: cv.CV_32S
        });
      });
    });
  });

  if (cvVersionGreaterEqual(3, 1, 0)) {
    describe('SuperpixelSLIC', () => {
      const algorithm = cv.SLICO;

      describe('constructor', () => {
        it('should throw if no args', () => {
          expect(() => new cv.SuperpixelSLIC()).to.throw('SuperpixelSLIC::New - Error: expected argument 0 to be of type');
        });

        it('should be constructable with required args', () => {
          const superpixel = new cv.SuperpixelSLIC(getTestImg().resizeToMax(250), algorithm);
          expect(superpixel).to.have.property('image').instanceOf(cv.Mat);
          assertMetaData(superpixel.image)({
            rows: 250, cols: 250, type: cv.CV_8UC3
          });
          assertPropsWithValue(superpixel)({
            algorithm
          });
        });
      });

      describe('iterate', () => {
        it('should iterate with default values', () => {
          const superpixel = new cv.SuperpixelSLIC(getTestImg().resizeToMax(250), algorithm);
          superpixel.iterate();
          assert(superpixel.numCalculatedSuperpixels > 0, 'no superpixels calculated');
          assertPropsWithValue(superpixel.labels)({
            rows: 250, cols: 250, type: cv.CV_32S
          });
        });
      });
    });


    describe('SuperpixelLSC', () => {
      describe('constructor', () => {
        it('should throw if no args', () => {
          expect(() => new cv.SuperpixelLSC()).to.throw('SuperpixelLSC::New - Error: expected argument 0 to be of type');
        });

        it('should be constructable with required args', () => {
          const superpixel = new cv.SuperpixelLSC(getTestImg().resizeToMax(250));
          expect(superpixel).to.have.property('image').instanceOf(cv.Mat);
          assertMetaData(superpixel.image)({
            rows: 250, cols: 250, type: cv.CV_8UC3
          });
        });
      });

      describe('iterate', () => {
        it('should iterate with default values', () => {
          const superpixel = new cv.SuperpixelLSC(getTestImg().resizeToMax(250));
          superpixel.iterate();
          assert(superpixel.numCalculatedSuperpixels > 0, 'no superpixels calculated');
          assertPropsWithValue(superpixel.labels)({
            rows: 250, cols: 250, type: cv.CV_32S
          });
        });
      });
    });
  }

};
