import { Mat, matTypes } from 'dut';
import { funcRequiresArgs, readTestImage } from 'utils';
import { expect } from 'chai';
import { assertMetaData, deepEquals } from './matTestUtils';
import constructorTestsFromJsArray from './constructorTestsFromJsArray';
import constructorTestsFromFillVector from './constructorTestsFromFillVector';
import operatorTests from './operatorTests';


describe('Mat', () => {
  constructorTestsFromJsArray();
  constructorTestsFromFillVector();
  operatorTests();

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
      assertMetaData(warped)(img.rows, img.cols, img.type);
      expect(deepEquals(warped.getData(), img.getData())).to.be.false;
    });
  });
});

