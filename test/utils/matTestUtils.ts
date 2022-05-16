import { Mat, Vec4 } from '@u4/opencv4nodejs';
import { assert } from 'chai';
import type openCV from '@u4/opencv4nodejs';
import { assertPropsWithValue } from './testUtils';

// TODO: proper deepEquals
const dangerousDeepEquals = (obj0: any, obj1: any) => JSON.stringify(obj0) === JSON.stringify(obj1);

const matTypeNames = [
  'CV_8UC1', 'CV_8UC2', 'CV_8UC3', 'CV_8UC4',
  'CV_8SC1', 'CV_8SC2', 'CV_8SC3', 'CV_8SC4',
  'CV_16UC1', 'CV_16UC2', 'CV_16UC3', 'CV_16UC4',
  'CV_16SC1', 'CV_16SC2', 'CV_16SC3', 'CV_16SC4',
  'CV_32SC1', 'CV_32SC2', 'CV_32SC3', 'CV_32SC4',
  'CV_32FC1', 'CV_32FC2', 'CV_32FC3', 'CV_32FC4',
  'CV_64FC1', 'CV_64FC2', 'CV_64FC3', 'CV_64FC4',
];

const normalizeValue = (val: number | Vec4 | Array<number>) => ((val as Vec4).x !== undefined ? [(val as Vec4).w, (val as Vec4).x, (val as Vec4).y, (val as Vec4).z]
  : ((val as Array<number>).length !== 4 ? [undefined, val[0], val[1], val[2]] : val)
);

const AssertMatValueEquals = (cmpFunc) => (val0: number, val1: number): void => {
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

const assertMatValueAlmostEquals = AssertMatValueEquals(
  (v0: number, v1: number) => (!v0 && !v1) || (((v0 - 0.0001) < v1) && (v1 < (v0 + 0.0001))),
);

const generateItsFactory = (cv: typeof openCV) => (msg: string, testFunc: Function, exclusions = new Set<string>()): void => matTypeNames.filter((type) => !exclusions.has(type)).forEach((type) => {
  it(`${type} ${msg}`, () => testFunc(cv[type]));
});

const assertMatValueEquals = AssertMatValueEquals((v0: number, v1: number) => v0 === v1);

/* compare float values differently as there will be slight precision loss */
const assertDataAlmostDeepEquals = (data0: number[][], data1: number[][]): void => data0.forEach((row, r) => row.forEach((val, c) => assertMatValueAlmostEquals(val, data1[r][c])));

const assertDataDeepEquals = (data0: any, data1: any): void => {
  assert(dangerousDeepEquals(data0, data1), 'mat data not equal');
};

const MatValuesComparator = (mat0: Mat, mat1: Mat) => (cmpFunc: (a: number, b: number) => void): void => {
  assert(mat0.rows === mat1.rows, 'mat rows mismatch');
  assert(mat0.cols === mat1.cols, 'mat cols mismatch');
  for (let r = 0; r < mat0.rows; r += 1) {
    for (let c = 0; c < mat0.cols; c += 1) {
      cmpFunc(mat0.at(r, c), mat1.at(r, c));
    }
  }
};

const isUniformMat = (mat: Mat, matVal: number): boolean => {
  if (mat.channels === 1) {
    return mat.getDataAsArray().every((r) => r.every((val) => val === matVal));
  }
  return mat.getDataAsArray().every((r) => r.every((vec) => (vec as any).every((val: number) => val === matVal)));
};

const isZeroMat = (mat: Mat) => isUniformMat(mat, 0);

const assertMetaData = (mat: Mat) => (args0: any, cols: number, type: number): void => {
  let propsWithValues = { rows: args0, cols, type };
  const propsFromArg0 = {
    rows: args0.rows,
    cols: args0.cols,
    type: args0.type,
  };
  if (['rows', 'cols', 'type'].every((prop) => !isNaN(propsFromArg0[prop]))) {
    propsWithValues = propsFromArg0;
  }
  assertPropsWithValue(mat)(propsWithValues);
};

export default function (cv: typeof openCV) {
  return {
    assertDataDeepEquals,
    assertDataAlmostDeepEquals,
    assertMatValueAlmostEquals,
    assertMatValueEquals,
    assertMetaData,
    dangerousDeepEquals,
    generateIts: generateItsFactory(cv),
    isZeroMat,
    isUniformMat,
    MatValuesComparator,
  };
}
