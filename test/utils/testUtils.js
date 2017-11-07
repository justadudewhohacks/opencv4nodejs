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

const assertErrorAsyncPromised = (func, msg) => {
  const ret = func();

  if (!ret.then || !ret.catch) {
    assert(false, 'func does not return a promise');
    return Promise.reject(ret);
  }

  return ret.then(() => {
    assert(false, 'no error was thrown');
  })
  .catch((err) => {
    assert.include(err.toString(), msg);
  });
};

exports.assertError = assertError;

const makeCompareValues = floatSafe => (val1, val2) => {
  if (floatSafe && typeof val1 === 'number' && typeof val2 === 'number') {
    return Math.abs(val1 - val2) < 0.001;
  }
  return val1 === val2;
};

exports.assertPropsWithValue = obj => (props, floatSafe = false) => {
  const compareValues = makeCompareValues(floatSafe);
  Object.keys(props).forEach(key =>
    assert(compareValues(props[key], obj[key]), `${key} - expected: ${props[key]}, have: ${obj[key]}`)
  );
};

exports.funcShouldRequireArgs = (func) => {
  it('should throw if no args', () => {
    assertError(func, 'expected arg 0 to be');
  });
};

exports._funcShouldRequireArgs = (func) => {
  it('should throw if no args', () => {
    assertError(func, 'expected argument 0 to be');
  });
};

exports.asyncFuncShouldRequireArgs = (func) => {
  it('should throw if no args', (done) => {
    assertErrorAsyncPromised(func, 'expected argument 0 to be')
    .then(() => done());
  });
};


exports._asyncFuncShouldRequireArgs = (func) => {
  it('should throw if no args', (done) => {
    assertErrorAsyncPromised(func, 'expected arg 0 to be')
    .then(() => done());
  });
};

exports.expectFloat = (val, expected) =>
  expect(val).to.be.a('number').above(expected - 0.01).below(expected + 0.01);

const getTestImagePath = (isPng = true) =>
  (isPng ? '../data/Lenna.png' : '../data/got.jpg');

exports.getTestImagePath = getTestImagePath;

exports.readTestImage = (isPng = true) => cv.imread(getTestImagePath(isPng));

exports.readPeoplesImage = () => cv.imread('../data/people.jpeg');

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
