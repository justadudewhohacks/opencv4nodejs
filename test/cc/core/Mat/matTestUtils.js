import { assert } from 'chai';
import { assertPropsWithValue } from 'utils';

// TODO: proper deepEquals
const dangerousDeepEquals = (obj0, obj1) => JSON.stringify(obj0) === JSON.stringify(obj1);

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
