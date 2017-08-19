import { Mat, cvTypes } from 'dut';
import {
  assertError,
  assertDataDeepEquals,
  assertMetaData
} from 'utils';
import { expect } from 'chai';

const operatorRequiresArg = (func, isScalar) => {
  it('should throw if no args', () => {
    assertError(
      () => {
        const mat = new Mat();
        return mat[func].bind(mat)();
      },
      `expected arg to be ${isScalar ? 'a Scalar' : 'an instance of Mat'}`
    );
  });
};

module.exports = () => {
  describe('add', () => {
    operatorRequiresArg('add');

    it('add matrices', () => {
      const mat = new Mat([
        [10, 20],
        [10, 20]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [20, 40],
        [20, 40]
      ];
      const res = mat.add(mat);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('sub', () => {
    operatorRequiresArg('sub');

    it('subtract matrices', () => {
      const mat0 = new Mat([
        [20, 40],
        [20, 40]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [10, 20],
        [10, 20]
      ], cvTypes.CV_8U);
      const expectedResult = mat1.getDataAsArray();
      const res = mat0.sub(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('mul', () => {
    operatorRequiresArg('mul', true);

    it('multiply matrix by scalar', () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], cvTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [40, 80],
        [40, 80]
      ];
      const res = mat.mul(scalar);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('div', () => {
    operatorRequiresArg('div', true);

    it('divide matrix by scalar', () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], cvTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [10, 20],
        [10, 20]
      ];
      const res = mat.div(scalar);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('and', () => {
    operatorRequiresArg('and');

    it('apply and to matrices', () => {
      const mat0 = new Mat([
        [15, 15],
        [15, 15]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [15, 0],
        [12, 3]
      ];
      const res = mat0.and(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('or', () => {
    operatorRequiresArg('or');

    it('apply or to matrices', () => {
      const mat0 = new Mat([
        [15, 15],
        [0, 0]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [15, 15],
        [12, 3]
      ];
      const res = mat0.or(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('hMul', () => {
    operatorRequiresArg('hMul');

    it('apply or to matrices', () => {
      const mat0 = new Mat([
        [20, 40],
        [60, 80]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [5, 4],
        [2, 1]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [100, 160],
        [120, 80]
      ];
      const res = mat0.hMul(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('hDiv', () => {
    operatorRequiresArg('hDiv');

    it('apply or to matrices', () => {
      const mat0 = new Mat([
        [20, 40],
        [60, 80]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [2, 5],
        [10, 20]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [10, 8],
        [6, 4]
      ];
      const res = mat0.hDiv(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('dot', () => {
    operatorRequiresArg('dot');

    it('apply or to matrices', () => {
      const mat0 = new Mat([
        [20, 40],
        [60, 80]
      ], cvTypes.CV_8U);
      const mat1 = new Mat([
        [10, 10],
        [10, 10]
      ], cvTypes.CV_8U);
      const res = mat0.dot(mat1);
      expect(res).to.equal(2000);
    });
  });

  describe('bitwiseAnd', () => {
    operatorRequiresArg('bitwiseAnd');

    it('apply bitwiseAnd to matrices', () => {
      const mat0 = new Mat([
        [[15, 15], [15, 15]],
        [[15, 15], [15, 15]]
      ], cvTypes.CV_8UC2);
      const mat1 = new Mat([
        [[15, 0], [0, 0]],
        [[12, 12], [3, 3]]
      ], cvTypes.CV_8UC2);
      const res = mat0.bitwiseAnd(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8UC2);
      assertDataDeepEquals(res.getDataAsArray(), mat1.getDataAsArray());
    });
  });

  describe('bitwiseNot', () => {
    it('apply bitwiseNot to matrix', () => {
      const mat0 = new Mat([
        [[255, 127], [15, 7]],
        [[63, 31], [3, 0]]
      ], cvTypes.CV_8UC2);
      const expectedResult = [
        [[0, 128], [240, 248]],
        [[192, 224], [252, 255]]
      ];
      const res = mat0.bitwiseNot();
      assertMetaData(res)(2, 2, cvTypes.CV_8UC2);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('bitwiseOr', () => {
    operatorRequiresArg('bitwiseOr');

    it('apply bitwiseOr to matrices', () => {
      const mat0 = new Mat([
        [[15, 15], [15, 15]],
        [[15, 15], [15, 15]]
      ], cvTypes.CV_8UC2);
      const mat1 = new Mat([
        [[15, 0], [0, 0]],
        [[12, 12], [3, 3]]
      ], cvTypes.CV_8UC2);
      const res = mat0.bitwiseOr(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8UC2);
      assertDataDeepEquals(res.getDataAsArray(), mat0.getDataAsArray());
    });
  });

  describe('bitwiseXor', () => {
    operatorRequiresArg('bitwiseXor');

    it('apply bitwiseXor to matrices', () => {
      const mat0 = new Mat([
        [[15, 15], [15, 15]],
        [[15, 15], [15, 15]]
      ], cvTypes.CV_8UC2);
      const mat1 = new Mat([
        [[15, 0], [0, 0]],
        [[12, 12], [3, 3]]
      ], cvTypes.CV_8UC2);
      const expectedResult = [
        [[0, 15],  [15, 15]],
        [[3, 3], [12, 12]]
      ];
      const res = mat0.bitwiseXor(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8UC2);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('absdiff', () => {
    operatorRequiresArg('absdiff');

    it('apply absdiff to matrices', () => {
      const mat0 = new Mat([
        [[255, 50], [255, 50]],
        [[100, 0], [100, 0]]
      ], cvTypes.CV_8UC2);
      const mat1 = new Mat([
        [[0, 0], [255, 255]],
        [[0, 0], [255, 255]]
      ], cvTypes.CV_8UC2);
      const expectedResult = [
        [[255, 50], [0, 205]],
        [[100, 0], [155, 255]]
      ];
      const res = mat0.absdiff(mat1);
      assertMetaData(res)(2, 2, cvTypes.CV_8UC2);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('exp', () => {
    it('apply exp to matrix', () => {
      const res = new Mat([
        [Math.log(1), Math.log(2)],
        [0, Math.log(4)]
      ], cvTypes.CV_64F).exp();
      assertMetaData(res)(2, 2, cvTypes.CV_64F);
    });
  });

  describe('sqrt', () => {
    it('apply sqrt to matrix', () => {
      const mat0 = new Mat([
        [4, 16],
        [0, 64]
      ], cvTypes.CV_64F);
      const expectedResult = [
        [2, 4],
        [0, 8]
      ];

      const res = mat0.sqrt();
      assertMetaData(res)(2, 2, cvTypes.CV_64F);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });

  describe('transpose', () => {
    it('apply transpose to matrix', () => {
      const mat0 = new Mat([
        [255, 0],
        [0, 255],
        [0, 0]
      ], cvTypes.CV_8U);
      const expectedResult = [
        [255, 0, 0],
        [0, 255, 0]
      ];

      const res = mat0.transpose();
      assertMetaData(res)(2, 3, cvTypes.CV_8U);
      assertDataDeepEquals(res.getDataAsArray(), expectedResult);
    });
  });
};
