import { cvTypes } from 'dut';
import { assert } from 'chai';
import { assertPropsWithValue } from './testUtils';

// TODO: proper deepEquals
const dangerousDeepEquals = (obj0, obj1) => JSON.stringify(obj0) === JSON.stringify(obj1);

const matTypeNames = [
  'CV_8UC1', 'CV_8UC2', 'CV_8UC3', 'CV_8UC4',
  'CV_8SC1', 'CV_8SC2', 'CV_8SC3', 'CV_8SC4',
  'CV_16UC1', 'CV_16UC2', 'CV_16UC3', 'CV_16UC4',
  'CV_16SC1', 'CV_16SC2', 'CV_16SC3', 'CV_16SC4',
  'CV_32SC1', 'CV_32SC2', 'CV_32SC3', 'CV_32SC4',
  'CV_32FC1', 'CV_32FC2', 'CV_32FC3', 'CV_32FC4',
  'CV_64FC1', 'CV_64FC2', 'CV_64FC3', 'CV_64FC4'
];

exports.generateIts = (msg, testFunc, exclusions = new Set()) =>
  matTypeNames.filter(type => !exclusions.has(type)).forEach((type) => {
    it(`${type} ${msg}`, () => testFunc(cvTypes[type]));
  });

exports.dangerousDeepEquals = dangerousDeepEquals;

exports.assertDataDeepEquals = (data0, data1) => {
  assert(dangerousDeepEquals(data0, data1), 'mat data not equal');
};

const normalizeValue = val =>
  (val.x !== undefined ? [val.w, val.x, val.y, val.z] :
    (val.length !== 4 ? [undefined, val[0], val[1], val[2]] : val)
  );

exports.assertMatValueEquals = (val0, val1) => {
  assert(typeof val0 === typeof val1, 'expected mat values to have same type');
  if (typeof val0 === 'number') {
    assert(val0 === val1, 'expected mat flat values to be equal');
  } else {
    assert(typeof val0 === 'object', 'expected val0 to be an object');
    assert(typeof val1 === 'object', 'expected val1 to be an object');

    const v0 = normalizeValue(val0);
    const v1 = normalizeValue(val1);
    [0, 1, 2, 3].forEach(n => assert(v0[n] === v1[n], `expected mat values to be equal at index ${n}`));
  }
};

exports.MatValuesComparator = (mat0, mat1) => (cmpFunc) => {
  assert(mat0.rows === mat1.rows, 'mat rows mismatch');
  assert(mat0.cols === mat1.cols, 'mat cols mismatch');
  for (let r = 0; r < mat0.rows; r += 1) {
    for (let c = 0; c < mat0.cols; c += 1) {
      cmpFunc(mat0.at(r, c), mat1.at(r, c));
    }
  }
};

exports.isZeroMat = (mat) => {
  if (mat.channels === 1) {
    return mat.getDataAsArray().every(r => r.every(val => val === 0));
  }
  return mat.getDataAsArray().every(r => r.every(vec => vec.every(val => val === 0)));
};

exports.assertMetaData = mat => (arg0, cols, type) => {
  let propsWithValues = {
    rows: arg0, cols, type
  };
  const propsFromArg0 = {
    rows: arg0.rows,
    cols: arg0.cols,
    type: arg0.type
  };
  if (['rows', 'cols', 'type'].every(prop => !isNaN(propsFromArg0[prop]))) {
    propsWithValues = propsFromArg0;
  }
  assertPropsWithValue(mat)(propsWithValues);
};
