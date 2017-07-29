import { Mat, matTypes, ximgproc } from 'dut';
import { assertPropsWithValue, funcRequiresArgs } from 'utils';
import { assert } from 'chai';

describe('ximgproc', () => {
  describe('SuperpixelSEEDS', () => {
    funcRequiresArgs(args => new ximgproc.SuperpixelSEEDS(args));

    it('should throw if image is no Mat instance', async () => {
      // TODO
      // assert(false, 'not implemented yet');
    });

    it('should be constructable with required args', async () => {
      const imgData = Array(250).fill(0).map(() => Array(200).fill(0).map(() => [0, 255, 0]));
      const img = new Mat(imgData, matTypes.CV_8UC3);
      const args = {
        img,
        numSuperpixels: 100,
        numLevels: 2
      };
      const superpixelSeeds = new ximgproc.SuperpixelSEEDS(args);
      assertPropsWithValue(superpixelSeeds)(args);
      assert(superpixelSeeds.img === img, 'image not equal');
    });
  });
});
