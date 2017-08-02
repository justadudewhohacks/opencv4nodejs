import { Mat, matTypes } from 'dut';
import { assert } from 'chai';
import { assertDataDeepEquals, assertMetaData } from './matTestUtils';

const funcRequiresArg = (func, acceptsScalar) => {
  it('should throw if no args', () => {
    let errMsg = '';
    try {
      const mat = new Mat();
      mat[func].bind(mat)();
    } catch (err) {
      errMsg = err.toString();
    }
    assert.include(errMsg, `expected arg to be a Mat${acceptsScalar ? ' or Scalar' : ''}`);
  });
};

module.exports = () => {
  describe('add', () => {
    funcRequiresArg('add');

    it('add matrices', async () => {
      const mat = new Mat([
        [10, 20],
        [10, 20]
      ], matTypes.CV_8U);
      const expectedResult = [
        [20, 40],
        [20, 40]
      ];
      const res = mat.add(mat);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('sub', () => {
    funcRequiresArg('sub');

    it('subtract matrices', async () => {
      const mat0 = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [10, 20],
        [10, 20]
      ], matTypes.CV_8U);
      const expectedResult = mat1.getData();
      const res = mat0.sub(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('mul', () => {
    funcRequiresArg('mul', true);

    it('multiply matrix with scalar', async () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [40, 80],
        [40, 80]
      ];
      const res = mat.mul(scalar);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('div', () => {
    funcRequiresArg('div', true);

    it('divide matrix with scalar', async () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [10, 20],
        [10, 20]
      ];
      const res = mat.div(scalar);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('and', () => {
    funcRequiresArg('and');

    it('apply and to matrices', async () => {
      const mat0 = new Mat([
        [15, 15],
        [15, 15]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], matTypes.CV_8U);
      const expectedResult = [
        [15, 0],
        [12, 3]
      ];
      const res = mat0.and(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('or', () => {
    funcRequiresArg('or');

    it('apply or to matrices', async () => {
      const mat0 = new Mat([
        [15, 15],
        [0, 0]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], matTypes.CV_8U);
      const expectedResult = [
        [15, 15],
        [12, 3]
      ];
      const res = mat0.or(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });
};
