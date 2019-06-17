const { expect } = require('chai');
const { doubleMin, doubleMax } = require('./typeRanges');

module.exports = function ({ cv, utils, getTestImg }) {

  const {
    generateAPITests,
    assertError,
    assertPropsWithValue,
    assertMetaData,
    assertDataDeepEquals,
    readTestImage,
    MatValuesComparator,
    isZeroMat,
    cvVersionGreaterEqual,
    cvVersionLowerThan
  } = utils

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
      getOptionalArg: () => copyMask,
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
      getOptionalArg: () => copyMask,
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

    // TODO figure out whats wrong with 3.3.0+
    (cvVersionGreaterEqual(3, 3, 0) ? it.skip : it)('should normalize range of CV_64F', () => {
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

    describe('getData after getRegion should throw an error', () => {
      it('should return buffer of with data of single channeled Mat', () => {
        const region = matC3.getRegion(new cv.Rect(0, 0, 2, 2));
        assertError(() => region.getData(), "Mat::GetData - Cannot call GetData when Region of Interest is defined (i.e. after getRegion) use matrix.copyTo to copy ROI to a new matrix")
      });
    });

    describe('async', () => {
      it('should return buffer with data of single channeled Mat', (done) => {
        matC1.getDataAsync((err, buf) => {
          expect(buf).instanceOf(Buffer).lengthOf(6);
          done();
        });
      });

      it('should return buffer with data of triple channeled Mat', (done) => {
        matC3.getDataAsync((err, buf) => {
          expect(buf).instanceOf(Buffer).lengthOf(18);
          done();
        });
      });
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
        getOptionalArg: () => flags,
        expectOutput
      });
    });

    describe('idct', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'idct',
        methodNameSpace: 'Mat',
        getOptionalArg: () => flags,
        expectOutput
      });
    });

    describe('dft', () => {
      generateAPITests({
        getDut: () => dtMat,
        methodName: 'dft',
        methodNameSpace: 'Mat',
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
        getOptionalArgsMap: () => ([
          ['flags', flags],
          ['nonZeroRows', 0]
        ]),
        expectOutput
      });
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
        getOptionalArg: () => new cv.Vec(255, 255, 255),
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
        getOptionalArg: () => new cv.Vec(255, 255, 255),
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
        getOptionalArg: () => new cv.Vec(255, 255, 255),
        methodName: 'padToSquare',
        methodNameSpace: 'Mat',
        expectOutput
      });
    });
  });

  describe('flip', () => {
    const src = new cv.Mat([
      [1, 0, 0],
      [1, 0, 0],
      [1, 0, 0]
    ], cv.CV_64F);

    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(src)(res);
      assertDataDeepEquals([
        [0, 0, 1],
        [0, 0, 1],
        [0, 0, 1]
      ], res.getDataAsArray());
    };

    const flipCode = 1;
    generateAPITests({
      getDut: () => src,
      methodName: 'flip',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => [flipCode],
      expectOutput
    });
  });

  (cvVersionLowerThan(3, 2, 0) ? describe.skip : describe)('rotate', () => {
    const src = new cv.Mat([
      [1, 0, 0],
      [1, 0, 0],
      [1, 0, 0]
    ], cv.CV_64F);

    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(src)(res);
      assertDataDeepEquals([
        [1, 1, 1],
        [0, 0, 0],
        [0, 0, 0]
      ], res.getDataAsArray());
    };

    const rotateCode = cv.ROTATE_90_CLOCKWISE;
    generateAPITests({
      getDut: () => src,
      methodName: 'rotate',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => [rotateCode],
      expectOutput
    });
  });

  describe('pushBack', () => {
    const getPushBackData = () => [
      [0, 1, 2, 3],
      [4, 5, 6, 7]
    ];

    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      expect(res.rows).to.equal(3);
      assertDataDeepEquals(
        [
          [0, 0, 0, 0]
        ].concat(getPushBackData()),
        res.getDataAsArray()
      );
    };

    generateAPITests({
      getDut: () => new cv.Mat(
        [[0, 0, 0, 0]],
        cv.CV_8U
      ),
      methodName: 'pushBack',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        new cv.Mat(
          getPushBackData(),
          cv.CV_8U
        )
      ]),
      expectOutput
    });
  });

  describe('popBack', () => {
    const getDut = () => new cv.Mat(
      [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
      ],
      cv.CV_8U
    );

    const expectOutput = (res, _, args) => {
      expect(res).to.be.instanceOf(cv.Mat);

      const origRows = getDut().rows;
      const expectedRows = origRows - ((typeof args[0] === 'number' && args[0]) || 1);
      expect(res.rows).to.equal(expectedRows);
    };

    const numRowsToPop = 2;
    generateAPITests({
      getDut,
      methodName: 'popBack',
      methodNameSpace: 'Mat',
      getOptionalArg: () => numRowsToPop,
      expectOutput
    });
  });

  describe('copyMakeBorder', () => {
    const top = 1;
    const bottom = 1;
    const left = 1;
    const right = 1;

    const getRequiredArgs = () => ([
      top,
      bottom,
      left,
      right
    ]);

    const borderType = cv.BORDER_CONSTANT;

    const makeExpectOutput = (type, value) => (res, _, args) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(res)(22, 22, type);
      if (args[5] === 255 || (args[4] && args[4].value)) {
        const upperLeft = res.at(0, 0);
        if (typeof upperLeft === 'object') {
          ['x', 'y', 'z', 'w'].forEach(k => expect(upperLeft[k]).to.eq(value[k]));
        } else {
          expect(upperLeft).to.equal(value);
        }
      }
    };

    const makeTest = (type, defaultValue, value) => () => {
      generateAPITests({
        getDut: () => new cv.Mat(20, 20, type, defaultValue),
        methodName: 'copyMakeBorder',
        methodNameSpace: 'Mat',
        getRequiredArgs,
        getOptionalArgsMap: () => ([
          ['borderType', borderType],
          ['value', value]
        ]),
        expectOutput: makeExpectOutput(type, value)
      });
    };

    describe('C1', makeTest(cv.CV_8U, 0, 255));
    describe('C2', makeTest(cv.CV_8UC2, [0, 0], new cv.Vec(255, 200)));
    describe('C3', makeTest(cv.CV_8UC3, [0, 0, 0], new cv.Vec(255, 200, 100)));
    describe('C4', makeTest(cv.CV_8UC4, [0, 0, 0, 0], new cv.Vec(255, 200, 100, 50)));
  });

  describe('checking of non-instance arguments', () => {
    it('should throw errors with correct error '
        + 'messages with non-instance arguments', () => {
      const img = getTestImg();

      assertError(
        () => img.getRegion(0, 1, 2, 3),
        'Mat::GetRegion - Error: expected argument 0 to be of type Rect'
      );
    });
  });

};
