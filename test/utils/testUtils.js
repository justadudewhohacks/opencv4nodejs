import { assert } from 'chai';
import opencv from 'dut';

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

exports.funcRequiresArgsObject = (func) => {
  it('should throw if no args', () => {
    assertError(func, 'args object required');
  });

  it('should throw if args empty', () => {
    assertError(() => func({}), 'has no property');
  });
};

exports.readTestImage = () => opencv.imread('../data/Lenna.png');
