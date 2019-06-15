const { assert } = require('chai');
const { assertPropsWithValue } = require('./testUtils');

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

const normalizeValue = val =>
(val.x !== undefined ? [val.w, val.x, val.y, val.z] :
  (val.length !== 4 ? [undefined, val[0], val[1], val[2]] : val)
);

const AssertMatValueEquals = cmpFunc => (val0, val1) => {
  assert(typeof val0 === typeof val1, 'expected mat values to have same type');
  if (typeof val0 === 'number') {
    assert(cmpFunc(val0, val1), 'expected mat flat values to be equal');
  } else {
    assert(typeof val0 === 'object', 'expected val0 to be an object');
    assert(typeof val1 === 'object', 'expected val1 to be an object');

    const v0 = normalizeValue(val0);
    const v1 = normalizeValue(val1);
    [0, 1, 2, 3].forEach(n => assert(cmpFunc(v0[n], v1[n]), `expected mat values to be equal at index ${n}`));
  }
};

const assertMatValueAlmostEquals = AssertMatValueEquals(
  (v0, v1) => (!v0 && !v1) || (((v0 - 0.0001) < v1) && (v1 < (v0 + 0.0001)))
);

const generateItsFactory = (cv) => (msg, testFunc, exclusions = new Set()) =>
  matTypeNames.filter(type => !exclusions.has(type)).forEach((type) => {
    it(`${type} ${msg}`, () => testFunc(cv[type]));
  });

const assertMatValueEquals = AssertMatValueEquals((v0, v1) => v0 === v1);

/* compare float values differently as there will be slight precision loss */
const assertDataAlmostDeepEquals = (data0, data1) =>
  data0.forEach((row, r) => row.forEach((val, c) => assertMatValueAlmostEquals(val, data1[r][c])));

const assertDataDeepEquals = (data0, data1) => {
  assert(dangerousDeepEquals(data0, data1), 'mat data not equal');
};

const MatValuesComparator = (mat0, mat1) => (cmpFunc) => {
  assert(mat0.rows === mat1.rows, 'mat rows mismatch');
  assert(mat0.cols === mat1.cols, 'mat cols mismatch');
  for (let r = 0; r < mat0.rows; r += 1) {
    for (let c = 0; c < mat0.cols; c += 1) {
      cmpFunc(mat0.at(r, c), mat1.at(r, c));
    }
  }
};

const isUniformMat = (mat, matVal) => {
  if (mat.channels === 1) {
    return mat.getDataAsArray().every(r => r.every(val => val === matVal));
  }
  return mat.getDataAsArray().every(r => r.every(vec => vec.every(val => val === matVal)));
};

const isZeroMat = mat => isUniformMat(mat, 0);

const assertMetaData = mat => (arg0, cols, type) => {
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

module.exports = function(cv) {
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
    MatValuesComparator
  }
}