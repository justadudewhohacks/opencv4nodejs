import { Mat, matTypes } from 'dut';
import { assertError, funcRequiresArgsObject } from 'utils';
import { assertMetaData, assertDataDeepEquals } from './matTestUtils';
import constructorTestsFromJsArray from './constructorTestsFromJsArray';
import constructorTestsFromFillVector from './constructorTestsFromFillVector';
import operatorTests from './operatorTests';
import imgprocTests from './imgprocTests';
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
  imgprocTests();

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

  describe('convertTo', () => {
    funcRequiresArgsObject(args => new Mat().convertTo(args));

    it('should throw if type invalid', async () => {
      assertError(() => srcMat.convertTo({ type: undefined }), 'Invalid type for type');
      assertError(() => srcMat.convertTo({ type: null }), 'Invalid type for type');
    });

    it('should convert mat', async () => {
      const dstMat = srcMat.convertTo({ type: matTypes.CV_32S });
      assertMetaData(dstMat)(srcMat.rows, srcMat.cols, matTypes.CV_32S);
    });
  });
});

