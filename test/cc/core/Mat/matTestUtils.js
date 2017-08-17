import { cvTypes } from 'dut';
import { assert } from 'chai';
import { assertPropsWithValue } from 'utils';

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

exports.assertMetaData = mat => (rows, cols, type) => {
  assertPropsWithValue(mat)({
    rows, cols, type
  });
};
