import { Mat, matTypes } from 'dut';
import { funcRequiresArgs, readTestImage } from 'utils';
import { expect } from 'chai';
import { deepEquals, expectMetaData } from './matTestUtils';

describe.only('Mat', () => {
  describe('warpPerspective', () => {
    funcRequiresArgs((() => {
      const mat = new Mat();
      return mat.warpPerspective.bind(mat);
    })());

    it('should warp image perspective', async () => {
      const img = await readTestImage();
      const transformationMatrix = new Mat(
        [
          [0.5, 0, 0],
          [0, 0.5, 0],
          [0, 0, 1]
        ],
        matTypes.CV_64F
      );

      const warped = img.warpPerspective({ transformationMatrix });
      expect(deepEquals(warped.getData(), img.getData())).to.be.false;
      expectMetaData(warped)(img.type, img.cols, img.rows);
    });
  });
});
