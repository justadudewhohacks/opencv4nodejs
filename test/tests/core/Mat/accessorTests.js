const { expect } = require('chai');
const getExampleMatData = require('./getExampleMatData');

module.exports = function ({ cv, utils }) {

  const {
    assertError,
    assertMatValueEquals,
    assertMatValueAlmostEquals,
    assertDataDeepEquals,
    assertDataAlmostDeepEquals,
    generateIts
  } = utils

  const isFloatType = type =>
    [cv.CV_32FC1, cv.CV_32FC2, cv.CV_32FC3, cv.CV_32FC4]
    .some(matType => matType === type);

  const createAndAssertAtReturnsCorrectValues = (type) => {
    const matData = getExampleMatData(cv, type);
    const mat = new cv.Mat(matData, type);
    const assertCmp = isFloatType(type) ? assertMatValueAlmostEquals : assertMatValueEquals;
    for (let r = 0; r < 4; r += 1) {
      for (let c = 0; c < 3; c += 1) {
        assertCmp(mat.at(r, c), matData[r][c]);
      }
    }
  };

  const createAndAssertSetsCorrectArrayValues = (type) => {
    const matData = getExampleMatData(cv, type);
    const mat = new cv.Mat(4, 3, type);
    for (let r = 0; r < 4; r += 1) {
      for (let c = 0; c < 3; c += 1) {
        mat.set(r, c, matData[r][c]);
      }
    }
    if (isFloatType(type)) {
      assertDataAlmostDeepEquals(matData, mat.getDataAsArray());
    } else {
      assertDataDeepEquals(matData, mat.getDataAsArray());
    }
  };

  const createAndAssertSetsCorrectVecValues = (type) => {
    const matData = getExampleMatData(cv, type);
    const mat = new cv.Mat(4, 3, type);
    for (let r = 0; r < 4; r += 1) {
      for (let c = 0; c < 3; c += 1) {
        const arr = matData[r][c];
        const vec = arr.length === 2 ? new cv.Vec(arr[0], arr[1]) :
          (arr.length === 3 ? new cv.Vec(arr[0], arr[1], arr[2]) : new cv.Vec(arr[0], arr[1], arr[2], arr[3]));
        mat.set(r, c, vec);
      }
    }
    if (isFloatType(type)) {
      assertDataAlmostDeepEquals(matData, mat.getDataAsArray());
    } else {
      assertDataDeepEquals(matData, mat.getDataAsArray());
    }
  };

  describe('at', () => {
    it('should support idx(arrays) as arguments', () => {
      const type = cv.CV_8U;
      const mat = new cv.Mat(getExampleMatData(cv, type), type);
      expect(mat.at([0, 0])).to.be.equal(255);
    });

    it('should throw when idx.length !== mat.dims', () => {
      const type = cv.CV_8U;
      const mat = new cv.Mat(getExampleMatData(cv, type), type);
      assertError(() => mat.at([0, 0, 0]),
        'expected array length to be equal to the dims');
    });

    it('should throw index out of bounds', () => {
      const type = cv.CV_8U;
      const mat = new cv.Mat(getExampleMatData(cv, type), type);
      assertError(() => mat.at(-1, 0), 'Index out of bounds');
      assertError(() => mat.at(0, -1), 'Index out of bounds');
      assertError(() => mat.at(4, 0), 'Index out of bounds');
      assertError(() => mat.at(0, 3), 'Index out of bounds');
    });

    generateIts('should return correct values at each pixel position', createAndAssertAtReturnsCorrectValues);
  });

  describe.skip('atRaw', () => {
    it('atRaw', () => {
      expect(true).to.be.false;
    });
  });

  describe('set', () => {
    describe('with array or flat values', () => {
      generateIts('should set correct values at each pixel position', createAndAssertSetsCorrectArrayValues);
    });

    describe('with vec values', () => {
      generateIts(
        'should set correct values at each pixel position',
        createAndAssertSetsCorrectVecValues,
        new Set(['CV_8UC1', 'CV_8SC1', 'CV_16UC1', 'CV_16SC1', 'CV_32SC1', 'CV_32FC1', 'CV_64FC1'])
      );
    });
  });
};
