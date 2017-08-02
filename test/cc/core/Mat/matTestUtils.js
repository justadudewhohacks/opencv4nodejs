import { assert } from 'chai';
import { assertPropsWithValue } from 'utils';

// TODO: proper deepEquals
const deepEquals = (obj0, obj1) => JSON.stringify(obj0) === JSON.stringify(obj1);

exports.deepEquals = deepEquals;

exports.assertDataDeepEquals = (data0, data1) => {
  assert(deepEquals(data0, data1), 'mat data not equal');
};

exports.assertMetaData = mat => (rows, cols, type) => {
  assertPropsWithValue(mat)({
    rows, cols, type
  });
};
