const { charMax, charMin, ucharMax, shortMax, shortMin, ushortMax, intMax,
  intMin, floatMin, floatMax, doubleMin, doubleMax } = require('./typeRanges');

module.exports = function ({ cv, utils }) {

  const {
    assertDataDeepEquals,
    assertDataAlmostDeepEquals,
    assertMetaData
  } = utils;

  const rows = 4;
  const cols = 3;
  const matDataFromValue = val => Array(rows).fill(Array(cols).fill(val));
  const createAndAssertMatFilled = (type, value) => {
    const mat = new cv.Mat(rows, cols, type, value);

    assertMetaData(mat)(rows, cols, type);
    if ([cv.CV_32FC1, cv.CV_32FC2, cv.CV_32FC3, cv.CV_32FC4].some(matType => matType === type)) {
      assertDataAlmostDeepEquals(matDataFromValue(value), mat.getDataAsArray());
    } else {
      assertDataDeepEquals(matDataFromValue(value), mat.getDataAsArray());
    }
  };

  describe('constructor fill with value', () => {
    it('should initialize CV_8UC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8UC1, ucharMax);
    });

    it('should initialize CV_8UC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8UC2, [ucharMax, 0]);
    });

    it('should initialize CV_8UC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8UC3, [ucharMax, 0, ucharMax]);
    });

    it('should initialize CV_8UC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8UC4, [ucharMax, 0, ucharMax, 0]);
    });

    it('should initialize CV_8SC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8SC1, charMax);
      createAndAssertMatFilled(cv.CV_8SC1, charMin);
    });

    it('should initialize CV_8SC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8SC2, [charMax, charMin]);
    });

    it('should initialize CV_8SC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8SC3, [charMax, charMin, 0]);
    });

    it('should initialize CV_8SC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_8SC4, [charMax, charMin, 0, charMax]);
    });

    it('should initialize CV_16UC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16UC1, ushortMax);
    });

    it('should initialize CV_16UC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16UC2, [ushortMax, 0]);
    });

    it('should initialize CV_16UC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16UC3, [ushortMax, 0, ushortMax]);
    });

    it('should initialize CV_16UC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16UC4, [ushortMax, 0, ushortMax, 0]);
    });

    it('should initialize CV_16SC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16SC1, shortMax);
      createAndAssertMatFilled(cv.CV_16SC1, shortMin);
    });

    it('should initialize CV_16SC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16SC2, [shortMax, shortMin]);
    });

    it('should initialize CV_16SC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16SC3, [shortMax, shortMin, 0]);
    });

    it('should initialize CV_16SC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_16SC4, [shortMax, shortMin, 0, shortMax]);
    });

    it('should initialize CV_32SC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32SC1, intMax);
      createAndAssertMatFilled(cv.CV_32SC1, intMin);
    });

    it('should initialize CV_32SC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32SC2, [intMax, intMin]);
    });

    it('should initialize CV_32SC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32SC3, [intMax, intMin, 0]);
    });

    it('should initialize CV_32SC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32SC4, [intMax, intMin, 0, intMax]);
    });

    it('should initialize CV_32FC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32FC1, floatMax);
      createAndAssertMatFilled(cv.CV_32FC1, floatMin);
      createAndAssertMatFilled(cv.CV_32FC1, -floatMax);
      createAndAssertMatFilled(cv.CV_32FC1, -floatMin);
    });

    it('should initialize CV_32FC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32FC2, [floatMax, floatMin]);
      createAndAssertMatFilled(cv.CV_32FC2, [-floatMax, -floatMin]);
    });

    it('should initialize CV_32FC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32FC3, [floatMax, floatMin, 0]);
      createAndAssertMatFilled(cv.CV_32FC3, [-floatMax, -floatMin, 0]);
    });

    it('should initialize CV_32FC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_32FC4, [floatMax, floatMin, -floatMax, -floatMin]);
    });

    it('should initialize CV_64FC1 with correct data', () => {
      createAndAssertMatFilled(cv.CV_64FC1, doubleMax);
      createAndAssertMatFilled(cv.CV_64FC1, doubleMin);
      createAndAssertMatFilled(cv.CV_64FC1, -doubleMax);
      createAndAssertMatFilled(cv.CV_64FC1, -doubleMin);
    });

    it('should initialize CV_64FC2 with correct data', () => {
      createAndAssertMatFilled(cv.CV_64FC2, [doubleMax, doubleMin]);
      createAndAssertMatFilled(cv.CV_64FC2, [-doubleMax, -doubleMin]);
    });

    it('should initialize CV_64FC3 with correct data', () => {
      createAndAssertMatFilled(cv.CV_64FC3, [doubleMax, doubleMin, 0]);
      createAndAssertMatFilled(cv.CV_64FC3, [-doubleMax, -doubleMin, 0]);
    });

    it('should initialize CV_64FC4 with correct data', () => {
      createAndAssertMatFilled(cv.CV_64FC4, [doubleMax, doubleMin, -doubleMax, -doubleMin]);
    });
  });

};