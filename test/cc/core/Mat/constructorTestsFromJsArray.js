import { Mat, cvTypes } from 'dut';
import { assert } from 'chai';
import { assertDataDeepEquals, assertMetaData } from './matTestUtils';
import { getExampleMatData } from './exampleData';

const createAndAssertMatDataEquals = (type) => {
  const matData = getExampleMatData(type);
  const mat = new Mat(matData, type);
  let assertType = type;
  // assert float type to become double type
  if ([cvTypes.CV_32FC1, cvTypes.CV_32FC2, cvTypes.CV_32FC3, cvTypes.CV_32FC4].some(matType => matType === type)) {
    assertType = type + 1;
  }
  assertMetaData(mat)(4, 3, assertType);
  assertDataDeepEquals(matData, mat.getDataAsArray());
};

module.exports = () =>
  describe('constructor from js array', () => {
    it('should throw column must be an array', () => {
      let errMsg = '';
      try {
        const matData = [1, 1, 1];
        new Mat(matData, cvTypes.CV_8U);
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
        new Mat(matData, cvTypes.CV_8U);
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
        new Mat(matData, invalidMatType);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, `invalid matType: ${invalidMatType}`);
    });

    it('should initialize CV_8UC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8UC1);
    });

    it('should initialize CV_8UC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8UC2);
    });

    it('should initialize CV_8UC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8UC3);
    });

    it('should initialize CV_8UC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8UC4);
    });

    it('should initialize CV_8SC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8SC1);
    });

    it('should initialize CV_8SC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8SC2);
    });

    it('should initialize CV_8SC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8SC3);
    });

    it('should initialize CV_8SC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_8SC4);
    });

    it('should initialize CV_16UC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16UC1);
    });

    it('should initialize CV_16UC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16UC2);
    });

    it('should initialize CV_16UC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16UC3);
    });

    it('should initialize CV_16UC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16UC4);
    });

    it('should initialize CV_16SC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16SC1);
    });

    it('should initialize CV_16SC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16SC2);
    });

    it('should initialize CV_16SC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16SC3);
    });

    it('should initialize CV_16SC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_16SC4);
    });

    it('should initialize CV_32SC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32SC1);
    });

    it('should initialize CV_32SC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32SC2);
    });

    it('should initialize CV_32SC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32SC3);
    });

    it('should initialize CV_32SC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32SC4);
    });

    it('should initialize CV_32FC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32FC1);
    });

    it('should initialize CV_32FC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32FC2);
    });

    it('should initialize CV_32FC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32FC3);
    });

    it('should initialize CV_32FC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_32FC4);
    });

    it('should initialize CV_64FC1 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_64FC1);
    });

    it('should initialize CV_64FC2 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_64FC2);
    });

    it('should initialize CV_64FC3 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_64FC3);
    });

    it('should initialize CV_64FC4 with correct data', () => {
      createAndAssertMatDataEquals(cvTypes.CV_64FC4);
    });
  });
