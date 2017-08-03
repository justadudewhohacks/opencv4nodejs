import { Mat, matTypes } from 'dut';
import { funcRequiresArgsObject, readTestImage } from 'utils';
import { expect } from 'chai';
import { assertMetaData, assertDataDeepEquals, deepEquals } from './matTestUtils';


module.exports = () => {
  describe('dilate', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.dilate.bind(mat);
    })());

    it('', async () => {

    });
  });

  describe('erode', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.erode.bind(mat);
    })());

    it('should erode image', async () => {
      const matData = Array(5).fill([0, 255, 0, 255, 0]);
      const kernelData = Array(3).fill([255, 255, 255]);
      const eroded = new Mat(matData, matTypes.CV_8U).erode({
        kernel: new Mat(kernelData, matTypes.CV_8U)
      });
      assertDataDeepEquals(Array(5).fill(Array(5).fill(0)), eroded.getData());
    });
  });


  describe('dilate', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.dilate.bind(mat);
    })());

    it('should dilate image', async () => {
      const matData = Array(5).fill([0, 255, 0, 255, 0]);
      const kernelData = Array(3).fill([255, 255, 255]);
      const eroded = new Mat(matData, matTypes.CV_8U).dilate({
        kernel: new Mat(kernelData, matTypes.CV_8U)
      });
      assertDataDeepEquals(Array(5).fill(Array(5).fill(255)), eroded.getData());
    });
  });

  describe('warpPerspective', () => {
    funcRequiresArgsObject((() => {
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
};
