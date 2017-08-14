import { matTypes, ximgproc } from 'dut';
import { assertPropsWithValue, funcRequiresArgsObject, readTestImage } from 'utils';
import { assert } from 'chai';

describe('ximgproc', () => {
  let testImg;

  before(async () => {
    testImg = (await readTestImage()).resizeToMax(250);
  });

  describe('SuperpixelSEEDS', () => {
    describe('constructor', () => {
      funcRequiresArgsObject(args => new ximgproc.SuperpixelSEEDS(args));

      it('should throw if image is no Mat instance', () => {
        // TODO
        // assert(false, 'not implemented yet');
      });

      it('should be constructable with required args', () => {
        const args = {
          img: testImg,
          numSuperpixels: 100,
          numLevels: 2
        };
        const superpixelSeeds = new ximgproc.SuperpixelSEEDS(args);
        assertPropsWithValue(superpixelSeeds)(args);
        assert(superpixelSeeds.img === testImg, 'image not equal');
      });
    });

    describe('iterate', () => {
      let superpixelSeeds;

      before(() => {
        superpixelSeeds = new ximgproc.SuperpixelSEEDS({
          img: testImg,
          numSuperpixels: 100,
          numLevels: 2
        });
      });

      it('should iterate with default values', () => {
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: testImg.rows, cols: testImg.cols, type: matTypes.CV_32S
        });
      });
    });
  });
});
