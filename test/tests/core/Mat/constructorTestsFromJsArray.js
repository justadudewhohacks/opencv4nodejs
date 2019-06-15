const { assert } = require('chai');
const getExampleMatData = require('./getExampleMatData');

module.exports = function ({ cv, utils }) {

  const {
    assertDataDeepEquals,
    assertDataAlmostDeepEquals,
    assertMetaData
  } = utils;

  const createAndAssertMatDataEquals = (type) => {
    const matData = getExampleMatData(cv, type);
    const mat = new cv.Mat(matData, type);

    assertMetaData(mat)(4, 3, type);
    if ([cv.CV_32FC1, cv.CV_32FC2, cv.CV_32FC3, cv.CV_32FC4].some(matType => matType === type)) {
      assertDataAlmostDeepEquals(matData, mat.getDataAsArray());
    } else {
      assertDataDeepEquals(matData, mat.getDataAsArray());
    }
  };

  describe('constructor from js array', () => {
    it('should throw column must be an array', () => {
      let errMsg = '';
      try {
        const matData = [1, 1, 1];
        new cv.Mat(matData, cv.CV_8U);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'Column should be an array, at column: 0');
    });

    it('should throw columns must be of uniform length', () => {
      let errMsg = '';
      try {
        const matData = [
          [1, 0, 0],
          [0, 1, 0],
          [0, 0]
        ];
        new cv.Mat(matData, cv.CV_8U);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'must be of uniform length, at column: 2');
    });

    it('should throw invalid matType', () => {
      let errMsg = '';
      const invalidMatType = -1;
      try {
        const matData = [
          [1, 0, 0],
          [0, 1, 0],
          [0, 0, 1]
        ];
        new cv.Mat(matData, invalidMatType);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, `invalid matType: ${invalidMatType}`);
    });

    it('should initialize CV_8UC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8UC1);
    });

    it('should initialize CV_8UC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8UC2);
    });

    it('should initialize CV_8UC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8UC3);
    });

    it('should initialize CV_8UC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8UC4);
    });

    it('should initialize CV_8SC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8SC1);
    });

    it('should initialize CV_8SC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8SC2);
    });

    it('should initialize CV_8SC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8SC3);
    });

    it('should initialize CV_8SC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_8SC4);
    });

    it('should initialize CV_16UC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16UC1);
    });

    it('should initialize CV_16UC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16UC2);
    });

    it('should initialize CV_16UC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16UC3);
    });

    it('should initialize CV_16UC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16UC4);
    });

    it('should initialize CV_16SC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16SC1);
    });

    it('should initialize CV_16SC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16SC2);
    });

    it('should initialize CV_16SC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16SC3);
    });

    it('should initialize CV_16SC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_16SC4);
    });

    it('should initialize CV_32SC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32SC1);
    });

    it('should initialize CV_32SC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32SC2);
    });

    it('should initialize CV_32SC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32SC3);
    });

    it('should initialize CV_32SC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32SC4);
    });

    it('should initialize CV_32FC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32FC1);
    });

    it('should initialize CV_32FC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32FC2);
    });

    it('should initialize CV_32FC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32FC3);
    });

    it('should initialize CV_32FC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_32FC4);
    });

    it('should initialize CV_64FC1 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_64FC1);
    });

    it('should initialize CV_64FC2 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_64FC2);
    });

    it('should initialize CV_64FC3 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_64FC3);
    });

    it('should initialize CV_64FC4 with correct data', () => {
      createAndAssertMatDataEquals(cv.CV_64FC4);
    });
  });

};
