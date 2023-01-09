import { Mat, Vec4 } from '@u4/opencv4nodejs';
import { assert } from 'chai';
import { assertPropsWithValue } from './testUtils';

// TODO: proper deepEquals
// eslint-disable-next-line @typescript-eslint/no-explicit-any
export const dangerousDeepEquals = (obj0: any, obj1: any) => JSON.stringify(obj0) === JSON.stringify(obj1);

const normalizeValue = (val: number | Vec4 | Array<number>) => ((val as Vec4).x !== undefined ? [(val as Vec4).w, (val as Vec4).x, (val as Vec4).y, (val as Vec4).z]
  : ((val as Array<number>).length !== 4 ? [undefined, val[0], val[1], val[2]] : val)
);

export const AssertMatValueEquals = (cmpFunc) => (val0: number | number[], val1: number | number[]): void => {
  assert(typeof val0 === typeof val1, 'expected mat values to have same type');
  if (typeof val0 === 'number') {
    assert(cmpFunc(val0, val1), 'expected mat flat values to be equal');
  } else {
    assert(typeof val0 === 'object', 'expected val0 to be an object');
    assert(typeof val1 === 'object', 'expected val1 to be an object');

    const v0 = normalizeValue(val0);
    const v1 = normalizeValue(val1);
    [0, 1, 2, 3].forEach((n) => assert(cmpFunc(v0[n], v1[n]), `expected mat values to be equal at index ${n}`));
  }
};

export const assertMatValueAlmostEquals = AssertMatValueEquals(
  (v0: number, v1: number) => (!v0 && !v1) || (((v0 - 0.0001) < v1) && (v1 < (v0 + 0.0001))),
);

export const assertMatValueEquals = AssertMatValueEquals((v0: number | number[], v1: number | number[]) => v0 === v1);

/* compare float values differently as there will be slight precision loss */
export const assertDataAlmostDeepEquals = (data0: number[][], data1: number[][]): void => data0.forEach((row, r) => row.forEach((val, c) => assertMatValueAlmostEquals(val, data1[r][c])));

// eslint-disable-next-line @typescript-eslint/no-explicit-any
export const assertDataDeepEquals = (data0: any, data1: any): void => {
  assert(dangerousDeepEquals(data0, data1), 'mat data not equal');
};

// eslint-disable-next-line no-unused-vars
type CompareInts = (a: number, b: number) => void;

export const MatValuesComparator = (mat0: Mat, mat1: Mat) => (cmpFunc: CompareInts): void => {
  assert(mat0.rows === mat1.rows, 'mat rows mismatch');
  assert(mat0.cols === mat1.cols, 'mat cols mismatch');
  for (let r = 0; r < mat0.rows; r += 1) {
    for (let c = 0; c < mat0.cols; c += 1) {
      cmpFunc(mat0.at(r, c), mat1.at(r, c));
    }
  }
};

export const isUniformMat = (mat: Mat, matVal: number): boolean => {
  if (mat.channels === 1) {
    return mat.getDataAsArray().every((r) => r.every((val) => val === matVal));
  }
  return (mat.getDataAsArray() as unknown as number[][][]).every((r) => r.every((vec) => vec.every((val: number) => val === matVal)));
};

export const isZeroMat = (mat: Mat) => isUniformMat(mat, 0);

export const assertMetaData = (mat: Mat | number[]) => (args0: number | { rows: number, cols: number, type: number }, cols?: number, type?: number): void => {
  if (typeof args0 === 'number') {
    const propsWithValues = { rows: args0 as number, cols, type };
    assertPropsWithValue(mat, propsWithValues);
  } else {
    const meta = args0 as {rows: number, cols: number, type: number};
    assertPropsWithValue(mat, meta);
  }
};
