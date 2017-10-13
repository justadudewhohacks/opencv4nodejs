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

const getTestImagePath = (isPng = true) =>
  (isPng ? '../data/Lenna.png' : '../data/got.jpg');

exports.getTestImagePath = getTestImagePath;

exports.readTestImage = (isPng = true) => cv.imread(getTestImagePath(isPng));

exports.getTestVideoPath = () => '../data/traffic.mp4';

const tmpdataDir = './tmpdata';

const ensureTmpdataDirExists = () => {
  if (!fs.existsSync(tmpdataDir)) {
    fs.mkdirSync(tmpdataDir);
  }
};

exports.clearTmpData = () => {
  ensureTmpdataDirExists();

  const files = fs.readdirSync(tmpdataDir);
  files.forEach((file) => {
    fs.unlinkSync(`${tmpdataDir}/${file}`);
  });
};

exports.getTmpDataFilePath = (file) => {
  ensureTmpdataDirExists();

  const filePath = `${tmpdataDir}/${file}`;
  if (fs.existsSync(filePath)) {
    fs.unlinkSync(filePath);
  }
  return filePath;
};

exports.fileExists = filePath => fs.existsSync(filePath);
