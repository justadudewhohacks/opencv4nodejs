import { matTypes, ximgproc } from 'dut';
import { assertPropsWithValue, funcRequiresArgs, readTestImage } from 'utils';
import { assert } from 'chai';

describe.only('ximgproc', () => {
  let testImg;

  before(async () => {
    testImg = (await readTestImage()).resizeToMax(250);
  });

  describe('SuperpixelSEEDS', () => {
    describe('constructor', () => {
      funcRequiresArgs(args => new ximgproc.SuperpixelSEEDS(args));

      it('should throw if image is no Mat instance', async () => {
        // TODO
        // assert(false, 'not implemented yet');
      });

      it('should be constructable with required args', async () => {
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

      it('should iterate with default values', async () => {
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: testImg.rows, cols: testImg.cols, type: matTypes.CV_32S
        });
      });
    });
  });
});
