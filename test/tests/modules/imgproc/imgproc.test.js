const cv = global.dut;
const {
  assertError,
  assertPropsWithValue,
  assertMetaData,
  funcShouldRequireArgs,
  readTestImage,
  generateAPITests
} = global.utils;
const { expect } = require('chai');
const contourTests = require('./contourTests');

describe('imgproc', () => {
  let testImg;

  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

  contourTests();

  describe('getStructuringElement', () => {
    const rows = 4;
    const cols = 3;
    const shape = cv.MORPH_CROSS;
    const kernelSize = new cv.Size(cols, rows);
    const anchor = new cv.Point(0, 1);

    funcShouldRequireArgs(cv.getStructuringElement);

    it('should be constructable with required args', () => {
      const kernel = cv.getStructuringElement(
        shape,
        kernelSize
      );
      assertPropsWithValue(kernel)({ rows, cols });
    });

    it('should be constructable with anchor', () => {
      const kernel = cv.getStructuringElement(
        shape,
        kernelSize,
        anchor
      );
      assertPropsWithValue(kernel)({ rows, cols });
    });
  });

  describe('calcHist', () => {
    funcShouldRequireArgs(cv.calcHist);

    it('should return 1 dimensional hist', () => {
      const histAxes = [
        {
          channel: 0,
          bins: 8,
          ranges: [0, 256]
        }
      ];
      const hist1D = cv.calcHist(testImg, histAxes);
      assertPropsWithValue(hist1D)({ rows: 8, cols: 1, dims: 2 });
    });

    it('should return 2 dimensional hist', () => {
      const histAxes = [
        {
          channel: 0,
          bins: 8,
          ranges: [0, 256]
        },
        {
          channel: 1,
          bins: 32,
          ranges: [0, 256]
        }
      ];
      const hist2D = cv.calcHist(testImg, histAxes);
      assertPropsWithValue(hist2D)({ rows: 8, cols: 32, dims: 2 });
    });

    // TODO causes sigsegv on 3.0.0 and 3.1.0
    (cv.version.minor < 2 ? it.skip : it)('should return 3 dimensional hist', () => {
      const histAxes = [
        {
          channel: 0,
          bins: 8,
          ranges: [0, 256]
        },
        {
          channel: 1,
          bins: 8,
          ranges: [0, 256]
        },
        {
          channel: 2,
          bins: 8,
          ranges: [0, 256]
        }
      ];
      const hist3D = cv.calcHist(testImg, histAxes);
      assertPropsWithValue(hist3D)({ dims: 3 });
    });
  });

  describe('fitLine', () => {
    const distType = cv.DIST_L2;
    const param = 0;
    const reps = 0.01;
    const aeps = 0.01;

    it('should throw if points array is empty', () => {
      assertError(
        () => cv.fitLine([], distType, param, reps, aeps),
        'FitLine - expected arg0 to be an Array with atleast 2 Points'
      );
    });

    it('should throw if array contains insufficient number of points', () => {
      assertError(
        () => cv.fitLine([new cv.Point(0, 0)], distType, param, reps, aeps),
        'FitLine - expected arg0 to be an Array with atleast 2 Points'
      );
    });

    it('should return lineParams for 2D points', () => {
      const points2D = [new cv.Point(0, 0), new cv.Point(10, 10)];
      const lineParams = cv.fitLine(points2D, distType, param, reps, aeps);
      expect(lineParams).to.be.an('array').lengthOf(4);
      expect(lineParams).to.not.have.members(Array(4).fill(0));
    });

    it('should return lineParams for 2D fp points', () => {
      const points2D = [new cv.Point(0, 0), new cv.Point(10.9, 10.1)];
      const lineParams = cv.fitLine(points2D, distType, param, reps, aeps);
      expect(lineParams).to.be.an('array').lengthOf(4);
      expect(lineParams).to.not.have.members(Array(4).fill(0));
    });

    it('should return lineParams for 3D points', () => {
      const points3D = [new cv.Point(0, 0, 0), new cv.Point(10, 10, 10)];
      const lineParams = cv.fitLine(points3D, distType, param, reps, aeps);
      expect(lineParams).to.be.an('array').lengthOf(6);
      expect(lineParams).to.not.have.members(Array(6).fill(0));
    });

    it('should return lineParams for 3D fp points', () => {
      const points3D = [new cv.Point(0, 0, 0), new cv.Point(10.9, 10.1, 10.5)];
      const lineParams = cv.fitLine(points3D, distType, param, reps, aeps);
      expect(lineParams).to.be.an('array').lengthOf(6);
      expect(lineParams).to.not.have.members(Array(6).fill(0));
    });
  });

  (cv.version.minor < 2 ? describe.skip : describe)('canny', () => {
    const th1 = 2.8;
    const th2 = 0.8;
    const L2gradient = true;
    const dx = new cv.Mat([
      [0, 0, 0, 0],
      [0, 9.9, 9.9, 0],
      [0, 0, 0, 0]
    ], cv.CV_16S);
    const dy = new cv.Mat([
      [0, 0, 0, 0],
      [0, 4.9, 4.9, 0],
      [0, 0, 0, 0]
    ], cv.CV_16S);

    funcShouldRequireArgs(() => cv.canny());

    it('can be called with required args', () => {
      const canny = cv.canny(dx, dy, th1, th2);
      assertMetaData(canny)(3, 4, cv.CV_8U);
    });

    it('can be called with optional args', () => {
      const canny = cv.canny(dx, dy, th1, th2, L2gradient);
      assertMetaData(canny)(3, 4, cv.CV_8U);
    });
  });

  describe('transformation matrix getters', () => {
    const srcPoints = [new cv.Point(0, 0), new cv.Point(10, 10), new cv.Point(0, 10)];
    const dstPoints = [new cv.Point(0, 0), new cv.Point(20, 20), new cv.Point(0, 20)];

    describe('getAffineTransform', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'getAffineTransform',
        getRequiredArgs: () => ([
          srcPoints,
          dstPoints
        ]),
        hasAsync: false,
        usesMacroInferno: true,
        expectOutput: res => expect(res).to.be.instanceOf(cv.Mat)
      });
    });

    describe('getPerspectiveTransform', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'getPerspectiveTransform',
        getRequiredArgs: () => ([
          srcPoints.concat(new cv.Point(10, 0)),
          dstPoints.concat(new cv.Point(20, 0))
        ]),
        hasAsync: false,
        usesMacroInferno: true,
        expectOutput: res => expect(res).to.be.instanceOf(cv.Mat)
      });
    });
  });
});
