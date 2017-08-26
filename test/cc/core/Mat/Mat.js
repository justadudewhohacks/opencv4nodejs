import { Mat, Vec, Point, Size, cvTypes } from 'dut';
import {
  assertError,
  assertPropsWithValue,
  assertMatValueEquals,
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

const { normTypes, connectedComponentsTypes } = cvTypes;

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

    // TODO figure out whats wrong with 3.3.0
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

  const zeros = new Mat(
    Array(5).fill(0).map(() => Array(5).fill(0)),
    cvTypes.CV_8U
  );
  const connectedComponentsMat = new Mat([
    [0, 255, 255, 255, 0],
    [0, 255, 255, 255, 0],
    [0, 255, 255, 255, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
  ], cvTypes.CV_8U);

  describe('connectedComponents', () => {
    it('should not find any connected components', () => {
      const contours = zeros.connectedComponents();
      assertMetaData(contours)(zeros.rows, zeros.cols, cvTypes.CV_32S);
      expect(isZeroMat(contours)).to.be.true;
    });

    it('should find connected component', () => {
      const mat = connectedComponentsMat;
      const contours = mat.connectedComponents();
      assertMetaData(contours)(mat.rows, mat.cols, cvTypes.CV_32S);
      expect(isZeroMat(contours)).to.be.false;
    });
  });

  describe('connectedComponentsWithStats', () => {
    const {
      CC_STAT_LEFT,
      CC_STAT_TOP,
      CC_STAT_WIDTH,
      CC_STAT_HEIGHT,
      CC_STAT_AREA
    } = connectedComponentsTypes;
    const zerosRetObj = zeros.connectedComponentsWithStats();
    const matRetObj = connectedComponentsMat.connectedComponentsWithStats();

    it('should return labels, stats and centroids', () => {
      expect(zerosRetObj).to.have.property('labels').instanceOf(Mat);
      expect(zerosRetObj).to.have.property('stats').instanceOf(Mat);
      expect(zerosRetObj).to.have.property('centroids').instanceOf(Mat);
    });

    it('should not find any connected components', () => {
      assertMetaData(zerosRetObj.labels)(zeros.rows, zeros.cols, cvTypes.CV_32S);
      expect(isZeroMat(zerosRetObj.labels)).to.be.true;
    });

    it('should not find any connected components', () => {
      assertMetaData(zeros.rows, zeros.cols, cvTypes.CV_32S);
      expect(isZeroMat(zerosRetObj.labels)).to.be.true;
    });

    it('should find connected component', () => {
      const mat = connectedComponentsMat;
      assertMetaData(mat.rows, mat.cols, cvTypes.CV_32S);
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
      expect(stats.at(label255, CC_STAT_LEFT)).to.equal(1);
      expect(stats.at(label255, CC_STAT_TOP)).to.equal(0);
      expect(stats.at(label255, CC_STAT_WIDTH)).to.equal(3);
      expect(stats.at(label255, CC_STAT_HEIGHT)).to.equal(3);
      expect(stats.at(label255, CC_STAT_AREA)).to.equal(9);
      expect(stats.at(label0, CC_STAT_LEFT)).to.equal(0);
      expect(stats.at(label0, CC_STAT_TOP)).to.equal(0);
      expect(stats.at(label0, CC_STAT_WIDTH)).to.equal(5);
      expect(stats.at(label0, CC_STAT_HEIGHT)).to.equal(5);
      expect(stats.at(label0, CC_STAT_AREA)).to.equal(16);
    });
  });

  describe('drawing', () => {
    it('drawLine', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawLine({
        pt1: new Point(0, 0),
        pt2: new Point(9, 9),
        color: new Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawCircle', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawCircle({
        center: new Point(4, 4),
        radius: 2,
        color: new Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawRectangle', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawRectangle({
        pt1: new Point(2, 2),
        pt2: new Point(8, 8),
        color: new Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawEllipse', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawEllipse({
        center: new Point(4, 4),
        boundingRectSize: new Size(4, 4),
        angle: Math.PI / 4,
        color: new Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });
  });

  describe.skip('distanceTransform', () => {
    it('distanceTransform', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('distanceTransformWithLabels', () => {
    it('distanceTransformWithLabels', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('blur', () => {
    it('blur', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('gaussianBlur', () => {
    it('gaussianBlur', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('medianBlur', () => {
    it('medianBlur', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('findContours', () => {
    it('findContours', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('contourArea', () => {
    it('contourArea', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('isContourConvex', () => {
    it('isContourConvex', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('convexHull', () => {
    it('convexHull', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('getData', () => {
    it('getData', () => {
      expect(true).to.be.false;
    });
  });
});

