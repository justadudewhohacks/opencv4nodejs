const cv = global.dut;
const {
  assertError,
  assertPropsWithValue,
  assertMatValueEquals,
  assertMetaData,
  assertDataDeepEquals,
  funcShouldRequireArgs,
  MatValuesComparator,
  isZeroMat
} = global.utils;
const { expect } = require('chai');
const accessorTests = require('./accessorTests');
const constructorTestsFromJsArray = require('./constructorTestsFromJsArray');
const constructorTestsFromFillVector = require('./constructorTestsFromFillVector');
const operatorTests = require('./operatorTests');
const imgprocTests = require('./imgprocTests');
const { doubleMin, doubleMax } = require('./typeRanges');

const srcMatData = [
  [doubleMin, doubleMax, 0],
  [doubleMax, 0, -doubleMax],
  [-doubleMax, 0, doubleMin],
  [doubleMin, -doubleMax, 0]
];
const srcMat = new cv.Mat(srcMatData, cv.CV_64F);
const mask = new cv.Mat([
  [0, 0, 0],
  [1, 1, 1],
  [0, 0, 0],
  [1, 1, 1]
], cv.CV_8U);
const expectedCopyData = srcMatData.map((row, r) => row.map(val => ((r % 2) ? val : 0)));
const expectedCopy = new cv.Mat(expectedCopyData, cv.CV_64F);

describe('Mat', () => {
  constructorTestsFromJsArray();
  constructorTestsFromFillVector();
  operatorTests();
  accessorTests();
  imgprocTests();

  describe('constructor from channels', () => {
    const matEmpty8U = new cv.Mat(4, 3, cv.CV_8U);
    const matEmpty8UC2 = new cv.Mat(4, 3, cv.CV_8UC2);

    it('should throw if rows mismatch', () => {
      assertError(
        () => new cv.Mat([matEmpty8U, new cv.Mat(5, 3, matEmpty8U.type)]),
        'rows mismatch'
      );
    });

    it('should throw if cols mismatch', () => {
      assertError(
        () => new cv.Mat([matEmpty8U, new cv.Mat(4, 2, matEmpty8U.type)]),
        'cols mismatch'
      );
    });

    it('should throw if channel is not a Mat', () => {
      assertError(
        () => new cv.Mat([matEmpty8U, matEmpty8U, 'foo']),
        'expected channel 2 to be an instance of Mat'
      );
    });

    it('should work constructable from single channel', () => {
      assertMetaData(new cv.Mat([matEmpty8U]))(matEmpty8U);
    });

    it('should be constructable from 2 single channels', () => {
      assertMetaData(new cv.Mat([matEmpty8U, matEmpty8U]))(4, 3, cv.CV_8UC2);
    });

    it('should be constructable from 3 single channels', () => {
      assertMetaData(new cv.Mat([matEmpty8U, matEmpty8U, matEmpty8U]))(4, 3, cv.CV_8UC3);
    });

    it('should be constructable from more then 4 single channels', () => {
      const channels = 10;
      assertPropsWithValue(new cv.Mat(Array(channels).fill(0).map(() => matEmpty8U)))({ channels });
    });

    it('should be constructable from double channeled', () => {
      assertMetaData(new cv.Mat([matEmpty8UC2]))(matEmpty8UC2);
    });

    it('should be constructable from mixed channels', () => {
      assertPropsWithValue(new cv.Mat([matEmpty8UC2, matEmpty8U]))({ channels: 3 });
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
    funcShouldRequireArgs((() => new cv.Mat().copyTo.bind(new cv.Mat()))());

    it('should copy data', () => {
      const dstMat = srcMat.copyTo(new cv.Mat(srcMat.rows, srcMat.cols, srcMat.type));
      assertMetaData(dstMat)(srcMat);
      assertDataDeepEquals(srcMat.getDataAsArray(), dstMat.getDataAsArray());
    });

    it('should copy masked data', () => {
      const dstMat = srcMat.copyTo(new cv.Mat(srcMat.rows, srcMat.cols, srcMat.type, 0), mask);
      assertMetaData(dstMat)(expectedCopy);
      assertDataDeepEquals(expectedCopyData, dstMat.getDataAsArray());
    });
  });

  describe('convertTo', () => {
    funcShouldRequireArgs((() => new cv.Mat().convertTo.bind(new cv.Mat()))());

    it('can be called if required args passed', () => {
      expect(() => srcMat.convertTo(cv.CV_32S)).to.not.throw();
    });

    it('should throw if code invalid', () => {
      assertError(() => srcMat.convertTo(undefined), 'Mat::ConvertTo - expected arg 0 to be of type: UINT');
      assertError(() => srcMat.convertTo(null), 'Mat::ConvertTo - expected arg 0 to be of type: UINT');
    });

    it('should convert mat', () => {
      const dstMat = srcMat.convertTo(cv.CV_32S);
      assertMetaData(dstMat)(srcMat.rows, srcMat.cols, cv.CV_32S);
    });
  });

  describe('norm', () => {
    it('should calculate default normal value if no args passed', () => {
      const mat = new cv.Mat([
        [0, Math.sqrt(4), Math.sqrt(4)],
        [Math.sqrt(8), Math.sqrt(16), Math.sqrt(32)]
      ], cv.CV_64F);
      expect(mat.norm()).to.equal(8);
    });

    it('should calculate norm to other mat', () => {
      const mat = new cv.Mat([
        [0, -0.5, 1.5]
      ], cv.CV_64F);
      const mat2 = new cv.Mat([
        [1.0, 0.5, 0.5]
      ], cv.CV_64F);
      expect(mat.norm(mat2)).to.equal(Math.sqrt(3));
    });
  });

  describe('normalize', () => {
    it('should use default normalization if no args passed', () => {
      assertMetaData(srcMat.normalize())(srcMat);
    });

    it('should normalize range of CV_8U', () => {
      const mat = new cv.Mat([
        [0, 127, 255],
        [63, 195, 7]
      ], cv.CV_8U);
      const normMat = mat.normalize({ normType: cv.NORM_MINMAX, alpha: 0, beta: 100 });
      const cmpVals = MatValuesComparator(mat, normMat);
      assertMetaData(normMat)(2, 3, cv.CV_8U);
      expect(isZeroMat(normMat)).to.be.false;
      cmpVals((_, normVal) => {
        expect(normVal).to.be.a('number');
        expect(normVal).to.be.within(0, 100);
      });
    });

    // TODO figure out whats wrong with 3.3.0
    (cv.version.minor === 3 ? it.skip : it)('should normalize range of CV_64F', () => {
      const mat = new cv.Mat([
        [0.5, 1000.12345, 1000],
        [-1000.12345, 123.456, -123.456]
      ], cv.CV_64F);
      const normMat = mat.normalize({ normType: cv.NORM_MINMAX, alpha: 0, beta: 10 });
      const cmpVals = MatValuesComparator(mat, normMat);
      assertMetaData(normMat)(2, 3, cv.CV_64F);
      expect(isZeroMat(normMat)).to.be.false;
      cmpVals((_, normVal) => {
        expect(normVal).to.be.a('number');
        expect(normVal).to.be.within(0, 10);
      });
    });
  });

  describe('splitChannels', () => {
    it('should return an array of all channels', () => {
      const channels = new cv.Mat(4, 3, cv.CV_8UC3).splitChannels();
      expect(channels).to.be.an('array').lengthOf(3);
      channels.forEach(channel => assertMetaData(channel)(4, 3, cv.CV_8U));
    });
  });

  const zeros = new cv.Mat(
    Array(5).fill(0).map(() => Array(5).fill(0)),
    cv.CV_8U
  );
  const connectedComponentsMat = new cv.Mat([
    [0, 255, 255, 255, 0],
    [0, 255, 255, 255, 0],
    [0, 255, 255, 255, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
  ], cv.CV_8U);

  describe('connectedComponents', () => {
    it('should not find any connected components', () => {
      const contours = zeros.connectedComponents();
      assertMetaData(contours)(zeros.rows, zeros.cols, cv.CV_32S);
      expect(isZeroMat(contours)).to.be.true;
    });

    it('should find connected component', () => {
      const mat = connectedComponentsMat;
      const contours = mat.connectedComponents();
      assertMetaData(contours)(mat.rows, mat.cols, cv.CV_32S);
      expect(isZeroMat(contours)).to.be.false;
    });
  });

  describe('connectedComponentsWithStats', () => {
    const zerosRetObj = zeros.connectedComponentsWithStats();
    const matRetObj = connectedComponentsMat.connectedComponentsWithStats();

    it('should return labels, stats and centroids', () => {
      expect(zerosRetObj).to.have.property('labels').instanceOf(cv.Mat);
      expect(zerosRetObj).to.have.property('stats').instanceOf(cv.Mat);
      expect(zerosRetObj).to.have.property('centroids').instanceOf(cv.Mat);
    });

    it('should not find any connected components', () => {
      assertMetaData(zerosRetObj.labels)(zeros.rows, zeros.cols, cv.CV_32S);
      expect(isZeroMat(zerosRetObj.labels)).to.be.true;
    });

    it('should not find any connected components', () => {
      assertMetaData(zeros.rows, zeros.cols, cv.CV_32S);
      expect(isZeroMat(zerosRetObj.labels)).to.be.true;
    });

    it('should find connected component', () => {
      const mat = connectedComponentsMat;
      assertMetaData(mat.rows, mat.cols, cv.CV_32S);
      expect(isZeroMat(matRetObj.labels)).to.be.false;
    });

    it('should find correct centroid', () => {
      const label255 = matRetObj.labels.at(0, 1);
      const centroid = [
        matRetObj.centroids.at(label255, 0),
        matRetObj.centroids.at(label255, 1)
      ];
      const expectedCenter = [2, 1];
      assertMatValueEquals(centroid, expectedCenter);
    });

    it('should return correct stats', () => {
      const { stats } = matRetObj;
      const label0 = matRetObj.labels.at(0, 0);
      const label255 = matRetObj.labels.at(0, 1);
      expect(stats.at(label255, cv.CC_STAT_LEFT)).to.equal(1);
      expect(stats.at(label255, cv.CC_STAT_TOP)).to.equal(0);
      expect(stats.at(label255, cv.CC_STAT_WIDTH)).to.equal(3);
      expect(stats.at(label255, cv.CC_STAT_HEIGHT)).to.equal(3);
      expect(stats.at(label255, cv.CC_STAT_AREA)).to.equal(9);
      expect(stats.at(label0, cv.CC_STAT_LEFT)).to.equal(0);
      expect(stats.at(label0, cv.CC_STAT_TOP)).to.equal(0);
      expect(stats.at(label0, cv.CC_STAT_WIDTH)).to.equal(5);
      expect(stats.at(label0, cv.CC_STAT_HEIGHT)).to.equal(5);
      expect(stats.at(label0, cv.CC_STAT_AREA)).to.equal(16);
    });
  });

  describe('addWeighted', () => {
    const alpha = 1;
    const beta = 0.5;
    const gamma = 100;

    const mat1 = new cv.Mat([
      [10, 20, 30],
      [40, 50, 60]
    ], cv.CV_8U);
    const mat2 = new cv.Mat([
      [20, 40, 60],
      [80, 100, 120]
    ], cv.CV_8U);

    funcShouldRequireArgs((() => new cv.Mat().convertTo.bind(new cv.Mat()))());

    it('can be called with required args', () => {
      const weighted = mat1.addWeighted(alpha, mat2, beta, gamma);
      assertMetaData(weighted)(2, 3, cv.CV_8U);
    });

    it('can be called with optional args', () => {
      const weighted = mat1.addWeighted(alpha, mat2, beta, gamma, 2);
      assertMetaData(weighted)(2, 3, cv.CV_16U);
    });

    it('should calculate the weighted sum', () => {
      const expected = [
        [120, 140, 160],
        [180, 200, 220]
      ];

      const weighted = mat1.addWeighted(alpha, mat2, beta, gamma);
      assertDataDeepEquals(expected, weighted.getDataAsArray());
    });
  });

  describe.skip('getData', () => {
    it('getData', () => {
      expect(true).to.be.false;
    });
  });
});

