import { Mat, matTypes } from 'dut';
import { assertError, funcRequiresArgsObject, readTestImage } from 'utils';
import { expect } from 'chai';
import { assertMetaData, assertDataDeepEquals, deepEquals } from './matTestUtils';
import constructorTestsFromJsArray from './constructorTestsFromJsArray';
import constructorTestsFromFillVector from './constructorTestsFromFillVector';
import operatorTests from './operatorTests';
import { doubleMin, doubleMax } from './typeRanges';

const srcMatData = [
  [doubleMin, doubleMax, 0],
  [doubleMax, 0, -doubleMax],
  [-doubleMax, 0, doubleMin],
  [doubleMin, -doubleMax, 0]
];
const srcMat = new Mat(srcMatData, matTypes.CV_64F);
const mask = new Mat([
  [0, 0, 0],
  [1, 1, 1],
  [0, 0, 0],
  [1, 1, 1]
], matTypes.CV_8U);
const expectedCopyData = srcMatData.map((row, r) => row.map(val => ((r % 2) ? val : 0)));
const expectedCopy = new Mat(expectedCopyData, matTypes.CV_64F);

describe('Mat', () => {
  constructorTestsFromJsArray();
  constructorTestsFromFillVector();
  operatorTests();

  describe('copy', () => {
    it('should copy data', async () => {
      const dstMat = srcMat.copy();
      assertMetaData(dstMat)(srcMat.rows, srcMat.cols, srcMat.type);
      assertDataDeepEquals(srcMat.getData(), dstMat.getData());
    });

    it('should copy masked data', async () => {
      const dstMat = srcMat.copy(mask);
      assertMetaData(dstMat)(expectedCopy.rows, expectedCopy.cols, expectedCopy.type);
      assertDataDeepEquals(expectedCopyData, dstMat.getData());
    });
  });

  describe('copyTo', () => {
    assertError(
      (() => {
        const mat = new Mat();
        return mat.copyTo.bind(mat);
      })(),
      'expected arg: destination mat'
    );

    it('should copy data', async () => {
      const dstMat = srcMat.copyTo(new Mat(srcMat.rows, srcMat.cols, srcMat.type));
      assertMetaData(dstMat)(srcMat.rows, srcMat.cols, srcMat.type);
      assertDataDeepEquals(srcMat.getData(), dstMat.getData());
    });

    it('should copy masked data', async () => {
      const dstMat = srcMat.copyTo(new Mat(srcMat.rows, srcMat.cols, srcMat.type, 0), mask);
      assertMetaData(dstMat)(expectedCopy.rows, expectedCopy.cols, expectedCopy.type);
      assertDataDeepEquals(expectedCopyData, dstMat.getData());
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
});

