const opencv = global.dut;
const { assertPropsWithValue, funcRequiresArgsObject, readTestImage } = global.utils;
const { assert } = require('chai');

describe('ximgproc', () => {
  if (!opencv.xmodules.ximgproc) {
    it('compiled without  ximgproc');
    return;
  }

  let testImg;

  before(async () => {
    testImg = readTestImage().resizeToMax(250);
  });

  describe('SuperpixelSEEDS', () => {
    describe('constructor', () => {
      funcRequiresArgsObject(args => new opencv.SuperpixelSEEDS(args));

      it.skip('should throw if image is no Mat instance', () => {
      });

      it('should be constructable with = required args', () => {
        const args = {
          img: testImg,
          numSuperpixels: 100,
          numLevels: 2
        };
        const superpixelSeeds = new opencv.SuperpixelSEEDS(args);
        assertPropsWithValue(superpixelSeeds)(args);
        assert(superpixelSeeds.img === testImg, 'image not equal');
      });
    });

    describe('iterate', () => {
      let superpixelSeeds;

      before(() => {
        superpixelSeeds = new opencv.SuperpixelSEEDS({
          img: testImg,
          numSuperpixels: 100,
          numLevels: 2
        });
      });

      it('should iterate with default values', () => {
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: testImg.rows, cols: testImg.cols, type: opencv.cvTypes.CV_32S
        });
      });
    });
  });
});
