const { assert, expect } = require('chai');
const fs = require('fs');

const cv = global.dut;

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

exports.expectFloat = (val, expected) =>
  expect(val).to.be.a('number').above(expected - 0.01).below(expected + 0.01);

exports.readTestImage = (isPng = true) => (isPng ? cv.imread('../data/Lenna.png') : cv.imread('../data/got.jpg'));

exports.getTmpDataFilePath = (file) => {
  const dir = './tmpdata';
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir);
  }
  const filePath = `${dir}/${file}`;
  if (fs.existsSync(filePath)) {
    fs.unlinkSync(filePath);
  }
  return filePath;
};
