const cv = global.dut;
const {
  generateAPITests,
  assertError,
  assertPropsWithValue,
  assertMetaData,
  assertDataDeepEquals,
  readTestImage,
  MatValuesComparator,
  isZeroMat
} = global.utils;
const { expect } = require('chai');
const accessorTests = require('./accessorTests');
const constructorTestsFromJsArray = require('./constructorTestsFromJsArray');
const constructorTestsFromFillVector = require('./constructorTestsFromFillVector');
const operatorTests = require('./operatorTests');
const imgprocTests = require('./imgprocTests');
const calib3dTests = require('./calib3dTests');
const { doubleMin, doubleMax } = require('./typeRanges');

const srcMatData = [
  [doubleMin, doubleMax, 0],
  [doubleMax, 0, -doubleMax],
  [-doubleMax, 0, doubleMin],
  [doubleMin, -doubleMax, 0]
];
const srcMat = new cv.Mat(srcMatData, cv.CV_64F);
const copyMask = new cv.Mat([
  [0, 0, 0],
  [1, 1, 1],
  [0, 0, 0],
  [1, 1, 1]
], cv.CV_8U);

describe('Mat', () => {
  let testImg;
  const getTestImg = () => testImg;
  before(() => {
    testImg = readTestImage();
  });

  constructorTestsFromJsArray();
  constructorTestsFromFillVector();
  operatorTests();
  accessorTests();

  describe('imgproc methods', () => imgprocTests(getTestImg));
  describe('calib3d methods', () => calib3dTests());

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
    const expectOutput = (res) => {
      assertMetaData(res)(srcMat.rows, srcMat.cols, srcMat.type);
    };

    generateAPITests({
      getDut: () => srcMat,
      methodName: 'copy',
      methodNameSpace: 'Mat',
      getOptionalArgs: () => ([
        copyMask
      ]),
      expectOutput
    });
  });

  describe('copyTo', () => {
    const expectOutput = (res) => {
      assertMetaData(res)(srcMat.rows, srcMat.cols, srcMat.type);
    };

    generateAPITests({
      getDut: () => srcMat,
      methodName: 'copyTo',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        new cv.Mat()
      ]),
      getOptionalArgs: () => ([
        copyMask
      ]),
      expectOutput
    });
  });

  describe('convertTo', () => {
    const expectOutput = (res) => {
      assertMetaData(res)(srcMat.rows, srcMat.cols, cv.CV_32S);
    };

    generateAPITests({
      getDut: () => srcMat,
      methodName: 'convertTo',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        cv.CV_32S
      ]),
      getOptionalArgsMap: () => ([
        ['alpha', 0.5],
        ['beta', 0.5]
      ]),
      expectOutput
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
    const mat = new cv.Mat(4, 3, cv.CV_8UC3);
    const expectOutput = (res) => {
      expect(res).to.be.an('array').lengthOf(3);
      res.forEach(channel => assertMetaData(channel)(mat.rows, mat.cols, cv.CV_8U));
    };

    generateAPITests({
      getDut: () => mat,
      methodName: 'splitChannels',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('addWeighted', () => {
    const expectOutput = (res) => {
      assertDataDeepEquals([
        [120, 140, 160],
        [180, 200, 220]
      ], res.getDataAsArray());
    };

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

    generateAPITests({
      getDut: () => mat1,
      methodName: 'addWeighted',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        alpha,
        mat2,
        beta,
        gamma
      ]),
      expectOutput
    });
  });

  describe('minMaxLoc', () => {
    const expectOutput = (res, dut, args) => {
      if (!args.filter(arg => !(typeof arg === 'function')).length) {
        // without mask
        expect(res.minVal).to.equal(0.1);
        expect(res.maxVal).to.equal(0.6);
        assertPropsWithValue(res.minLoc)({ x: 0, y: 0 });
        assertPropsWithValue(res.maxLoc)({ x: 2, y: 1 });
      } else {
        // with mask
        expect(res.minVal).to.equal(0.2);
        expect(res.maxVal).to.equal(0.5);
        assertPropsWithValue(res.minLoc)({ x: 1, y: 0 });
        assertPropsWithValue(res.maxLoc)({ x: 1, y: 1 });
      }
    };

    const mat = new cv.Mat([
      [0.1, 0.2, 0.3],
      [0.4, 0.5, 0.6]
    ], cv.CV_64F);

    const mask = new cv.Mat([
      [0, 1, 1],
      [1, 1, 0]
    ], cv.CV_8U);

    generateAPITests({
      getDut: () => mat,
      methodName: 'minMaxLoc',
      methodNameSpace: 'Mat',
      getOptionalArgs: () => ([
        mask
      ]),
      expectOutput
    });
  });

  describe('getData', () => {
    const matC1 = new cv.Mat([
      [255, 255, 255],
      [0, 0, 0]
    ], cv.CV_8U);

    const matC3 = new cv.Mat([
      [[255, 255, 255], [255, 255, 255], [255, 255, 255]],
      [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    ], cv.CV_8UC3);

    describe('sync', () => {
      it('should return buffer of with data of single channeled Mat', () => {
        const buf = matC1.getData();
        expect(buf).instanceOf(Buffer).lengthOf(6);
      });

      it('should return buffer of with data of triple channeled Mat', () => {
        const buf = matC3.getData();
        expect(buf).instanceOf(Buffer).lengthOf(18);
      });
    });

    describe('async', () => {
      it('should return buffer with data of single channeled Mat', () => {
        matC1.getDataAsync((err, buf) => {
          expect(buf).instanceOf(Buffer).lengthOf(6);
        });
      });

      it('should return buffer with data of triple channeled Mat', () => {
        matC3.getDataAsync((err, buf) => {
          expect(buf).instanceOf(Buffer).lengthOf(18);
        });
      });
    });
  });

  describe('inRange', () => {
    const expectOutput = (inRangeMat) => {
      assertMetaData(inRangeMat)(2, 3, cv.CV_8U);
      assertDataDeepEquals(
        [
          [255, 255, 255],
          [0, 0, 255]
        ],
        inRangeMat.getDataAsArray()
      );
    };

    const mat = new cv.Mat([
      [[255, 255, 255], [255, 255, 255], [255, 255, 255]],
      [[0, 0, 0], [100, 100, 100], [101, 101, 101]]
    ], cv.CV_8UC3);

    const lower = new cv.Vec(101, 101, 101);
    const upper = new cv.Vec(255, 255, 255);

    generateAPITests({
      getDut: () => mat,
      methodName: 'inRange',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        lower,
        upper
      ]),
      expectOutput
    });
  });

  describe('discrete transform', () => {
    const dtMat = new cv.Mat([
      [0.9, 0.9, 0, 0],
      [0.9, 0, -0.9, -0.9],
      [-0.9, 0, 0.9, -0.9],
      [0.9, 0, -0.9, 0]
    ], cv.CV_64F);

    const expectOutput = (res) => {
      assertMetaData(res)(dtMat.rows, dtMat.cols, cv.CV_64F);
    };

    const flags = 0;

    describe('dct', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'dct',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgs: () => ([
          flags
        ]),
        expectOutput
      });
    });

    describe('idct', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'idct',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgs: () => ([
          flags
        ]),
        expectOutput
      });
    });

    describe('dft', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'dft',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgsMap: () => ([
          ['flags', flags],
          ['nonZeroRows', 0]
        ]),
        expectOutput
      });
    });

    describe('idft', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'idft',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgsMap: () => ([
          ['flags', flags],
          ['nonZeroRows', 0]
        ]),
        expectOutput
      });
    });

    describe('mulSpectrums', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'mulSpectrums',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          dtMat
        ]),
        getOptionalArgsMap: () => ([
          ['dftRows', true],
          ['conjB', true]
        ]),
        expectOutput
      });
    });
  });

  describe('findNonZero', () => {
    const expectOutput = (res) => {
      expect(res).to.be.an('array').lengthOf(3);
    };

    const mat = new cv.Mat([
      [1, 0, 1],
      [0, 1, 0]
    ], cv.CV_8U);

    generateAPITests({
      getDut: () => mat,
      methodName: 'findNonZero',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('padToSquare', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(res)(3, 3, cv.CV_8UC3);
    };

    describe('cols > rows', () => {
      const mat = new cv.Mat([
        [[255, 255, 255], [0, 0, 0], [255, 255, 255]],
        [[0, 0, 0], [255, 255, 255], [0, 0, 0]]
      ], cv.CV_8UC3);

      generateAPITests({
        getDut: () => mat,
        getOptionalArgs: () => [new cv.Vec(255, 255, 255)],
        methodName: 'padToSquare',
        methodNameSpace: 'Mat',
        expectOutput
      });
    });

    describe('rows > cols', () => {
      const mat = new cv.Mat([
        [[255, 255, 255], [0, 0, 0]],
        [[0, 0, 0], [255, 255, 255]],
        [[0, 0, 0], [255, 255, 255]]
      ], cv.CV_8UC3);

      generateAPITests({
        getDut: () => mat,
        getOptionalArgs: () => [new cv.Vec(255, 255, 255)],
        methodName: 'padToSquare',
        methodNameSpace: 'Mat',
        expectOutput
      });
    });

    describe('rows === cols', () => {
      const mat = new cv.Mat([
        [[255, 255, 255], [0, 0, 0], [0, 0, 0]],
        [[0, 0, 0], [255, 255, 255], [0, 0, 0]],
        [[0, 0, 0], [255, 255, 255], [0, 0, 0]]
      ], cv.CV_8UC3);

      generateAPITests({
        getDut: () => mat,
        getOptionalArgs: () => [new cv.Vec(255, 255, 255)],
        methodName: 'padToSquare',
        methodNameSpace: 'Mat',
        expectOutput
      });
    });
  });
});

