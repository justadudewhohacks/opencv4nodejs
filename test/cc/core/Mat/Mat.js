import { Mat, cvTypes } from 'dut';
import {
  assertError,
  assertPropsWithValue,
  funcRequiresArgsObject,
  assertMetaData,
  assertDataDeepEquals,
  MatValuesComparator,
  isZeroMat
} from 'utils';
import { expect } from 'chai';
import accessorTests from './accessorTests';
import constructorTestsFromJsArray from './constructorTestsFromJsArray';
import constructorTestsFromFillVector from './constructorTestsFromFillVector';
import operatorTests from './operatorTests';
import imgprocTests from './imgprocTests';
import { doubleMin, doubleMax } from './typeRanges';

const { normTypes } = cvTypes;

const srcMatData = [
  [doubleMin, doubleMax, 0],
  [doubleMax, 0, -doubleMax],
  [-doubleMax, 0, doubleMin],
  [doubleMin, -doubleMax, 0]
];
const srcMat = new Mat(srcMatData, cvTypes.CV_64F);
const mask = new Mat([
  [0, 0, 0],
  [1, 1, 1],
  [0, 0, 0],
  [1, 1, 1]
], cvTypes.CV_8U);
const expectedCopyData = srcMatData.map((row, r) => row.map(val => ((r % 2) ? val : 0)));
const expectedCopy = new Mat(expectedCopyData, cvTypes.CV_64F);

describe('Mat', () => {
  constructorTestsFromJsArray();
  constructorTestsFromFillVector();
  operatorTests();
  accessorTests();
  imgprocTests();

  describe('constructor from channels', () => {
    const matEmpty8U = new Mat(4, 3, cvTypes.CV_8U);
    const matEmpty8UC2 = new Mat(4, 3, cvTypes.CV_8UC2);

    it('should throw if rows mismatch', () => {
      assertError(
        () => new Mat([matEmpty8U, new Mat(5, 3, matEmpty8U.type)]),
        'rows mismatch'
      );
    });

    it('should throw if cols mismatch', () => {
      assertError(
        () => new Mat([matEmpty8U, new Mat(4, 2, matEmpty8U.type)]),
        'cols mismatch'
      );
    });

    it('should throw if channel is not a Mat', () => {
      assertError(
        () => new Mat([matEmpty8U, matEmpty8U, 'foo']),
        'expected channel 2 to be an instance of Mat'
      );
    });

    it('should work constructable from single channel', () => {
      assertMetaData(new Mat([matEmpty8U]))(matEmpty8U);
    });

    it('should be constructable from 2 single channels', () => {
      assertMetaData(new Mat([matEmpty8U, matEmpty8U]))(4, 3, cvTypes.CV_8UC2);
    });

    it('should be constructable from 3 single channels', () => {
      assertMetaData(new Mat([matEmpty8U, matEmpty8U, matEmpty8U]))(4, 3, cvTypes.CV_8UC3);
    });

    it('should be constructable from more then 4 single channels', () => {
      const channels = 10;
      assertPropsWithValue(new Mat(Array(channels).fill(0).map(() => matEmpty8U)))({ channels });
    });

    it('should be constructable from double channeled', () => {
      assertMetaData(new Mat([matEmpty8UC2]))(matEmpty8UC2);
    });

    it('should be constructable from mixed channels', () => {
      assertPropsWithValue(new Mat([matEmpty8UC2, matEmpty8U]))({ channels: 3 });
    });
  });

  describe('copy', () => {
    it('should copy data', () => {
      const dstMat = srcMat.copy();
      assertMetaData(dstMat)(srcMat);
      assertDataDeepEquals(srcMat.getDataAsArray(), dstMat.getDataAsArray());
    });

    it('should copy masked data', () => {
      const dstMat = srcMat.copy(mask);
      assertMetaData(dstMat)(expectedCopy);
      assertDataDeepEquals(expectedCopyData, dstMat.getDataAsArray());
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

    it('should copy data', () => {
      const dstMat = srcMat.copyTo(new Mat(srcMat.rows, srcMat.cols, srcMat.type));
      assertMetaData(dstMat)(srcMat);
      assertDataDeepEquals(srcMat.getDataAsArray(), dstMat.getDataAsArray());
    });

    it('should copy masked data', () => {
      const dstMat = srcMat.copyTo(new Mat(srcMat.rows, srcMat.cols, srcMat.type, 0), mask);
      assertMetaData(dstMat)(expectedCopy);
      assertDataDeepEquals(expectedCopyData, dstMat.getDataAsArray());
    });
  });

  describe('convertTo', () => {
    funcRequiresArgsObject(args => new Mat().convertTo(args));

    it('should throw if type invalid', () => {
      assertError(() => srcMat.convertTo({ type: undefined }), 'Invalid type for type');
      assertError(() => srcMat.convertTo({ type: null }), 'Invalid type for type');
    });

    it('should convert mat', () => {
      const dstMat = srcMat.convertTo({ type: cvTypes.CV_32S });
      assertMetaData(dstMat)(srcMat.rows, srcMat.cols, cvTypes.CV_32S);
    });
  });

  describe('norm', () => {
    it('should use calculate default normal value if no args passed', () => {
      const mat = new Mat([
        [0, Math.sqrt(4), Math.sqrt(4)],
        [Math.sqrt(8), Math.sqrt(16), Math.sqrt(32)]
      ], cvTypes.CV_64F);
      expect(mat.norm()).to.equal(8);
    });

    it('should calculate norm to other mat', () => {
      const mat = new Mat([
        [0, -0.5, 1.5]
      ], cvTypes.CV_64F);
      const mat2 = new Mat([
        [1.0, 0.5, 0.5]
      ], cvTypes.CV_64F);
      expect(mat.norm({ src2: mat2 })).to.equal(Math.sqrt(3));
    });
  });

  describe('normalize', () => {
    it('should use default normalization if no args passed', () => {
      assertMetaData(srcMat.normalize())(srcMat);
    });

    it('should normalize range of CV_8U', () => {
      const mat = new Mat([
        [0, 127, 255],
        [63, 195, 7]
      ], cvTypes.CV_8U);
      const normMat = mat.normalize({ normType: normTypes.NORM_MINMAX, alpha: 0, beta: 100 });
      const cmpVals = MatValuesComparator(mat, normMat);
      assertMetaData(normMat)(2, 3, cvTypes.CV_8U);
      expect(isZeroMat(normMat)).to.be.false;
      cmpVals((_, normVal) => {
        expect(normVal).to.be.a('number');
        expect(normVal).to.be.within(0, 100);
      });
    });

    it('should normalize range of CV_64F', () => {
      const mat = new Mat([
        [0.5, 1000.12345, 1000],
        [-1000.12345, 123.456, -123.456]
      ], cvTypes.CV_64F);
      const normMat = mat.normalize({ normType: normTypes.NORM_MINMAX, alpha: 0, beta: 10 });
      const cmpVals = MatValuesComparator(mat, normMat);
      assertMetaData(normMat)(2, 3, cvTypes.CV_64F);
      expect(isZeroMat(normMat)).to.be.false;
      cmpVals((_, normVal) => {
        expect(normVal).to.be.a('number');
        expect(normVal).to.be.within(0, 10);
      });
    });
  });

  describe('splitChannels', () => {
    it('should return an array of all channels', () => {
      const channels = new Mat(4, 3, cvTypes.CV_8UC3).splitChannels();
      expect(channels).to.be.an('array').lengthOf(3);
      channels.forEach(channel => assertMetaData(channel)(4, 3, cvTypes.CV_8U));
    });
  });

  describe.skip('new from node buffer', () => {
    it('new from node buffer', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('getData', () => {
    it('getData', () => {
      expect(true).to.be.false;
    });
  });
});

