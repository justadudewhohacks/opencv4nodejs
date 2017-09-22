const { assert } = require('chai');

const opencv = global.dut;

const assertError = (func, msg) => {
  let errMsg = '';
  try {
    func();
  } catch (err) {
    errMsg = err.toString();
  }
  assert.include(errMsg, msg);
};

exports.assertError = assertError;

exports.assertPropsWithValue = obj => (props) => {
  Object.keys(props).forEach(key =>
    assert(props[key] === obj[key], `${key} - expected: ${props[key]}, have: ${obj[key]}`)
  );
};

exports.funcShouldRequireArgs = (func) => {
  it('should throw if no args', () => {
    assertError(func, 'expected arg 0 to be');
  });
};

exports.readTestImage = () => opencv.imread('../data/Lenna.png');
