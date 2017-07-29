import { assert } from 'chai';
import { io } from 'dut';

exports.assertError = func => (msg) => {
  let errMsg = '';
  try {
    func();
  } catch (err) {
    errMsg = err.toString();
  }
  assert.include(errMsg, msg);
};

exports.assertPropsWithValue = obj => (props) => {
  Object.keys(props).forEach(key =>
    assert(props[key] === obj[key], `${key} - expected: ${props[key]}, have: ${obj[key]}`)
  );
};

exports.funcRequiresArgs = (func) => {
  it('should throw if no args', () => {
    let errMsg = '';
    try {
      func();
    } catch (err) {
      errMsg = err.toString();
    }
    assert.include(errMsg, 'args object required');
  });

  it('should throw if args empty', () => {
    let errMsg = '';
    try {
      func({});
    } catch (err) {
      errMsg = err.toString();
    }
    assert.include(errMsg, 'has no property');
  });
};

exports.readTestImage = () => new Promise((resolve, reject) => {
  io.imread('../data/Lenna.png', (err, img) => {
    if (err) {
      return reject(err);
    }
    return resolve(img);
  });
});
