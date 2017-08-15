import { Mat, matTypes } from 'dut';
import { assertError } from 'utils';
import { getExampleMatData } from './exampleData';
import { assertMatValueEquals } from './matTestUtils';

const createAndAssertAtReturnsCorrectValues = (type) => {
  const matData = getExampleMatData(type);
  const mat = new Mat(matData, type);

  for (let r = 0; r < 4; r += 1) {
    for (let c = 0; c < 3; c += 1) {
      assertMatValueEquals(mat.at(r, c), matData[r][c]);
    }
  }
};

module.exports = () => {
  describe('at', () => {
    it('should throw index out of bounds', () => {
      const type = matTypes.CV_8U;
      const mat = new Mat(getExampleMatData(type), type);
      assertError(() => mat.at(-1, 0), 'Index out of bounds');
      assertError(() => mat.at(0, -1), 'Index out of bounds');
      assertError(() => mat.at(4, 0), 'Index out of bounds');
      assertError(() => mat.at(0, 3), 'Index out of bounds');
    });

    it('CV_8UC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8UC1);
    });

    it('CV_8UC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8UC2);
    });

    it('CV_8UC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8UC3);
    });

    it('CV_8UC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8UC4);
    });

    it('CV_8SC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8SC1);
    });

    it('CV_8SC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8SC2);
    });

    it('CV_8SC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8SC3);
    });

    it('CV_8SC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_8SC4);
    });

    it('CV_16UC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16UC1);
    });

    it('CV_16UC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16UC2);
    });

    it('CV_16UC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16UC3);
    });

    it('CV_16UC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16UC4);
    });

    it('CV_16SC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16SC1);
    });

    it('CV_16SC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16SC2);
    });

    it('CV_16SC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16SC3);
    });

    it('CV_16SC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_16SC4);
    });

    it('CV_32SC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32SC1);
    });

    it('CV_32SC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32SC2);
    });

    it('CV_32SC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32SC3);
    });

    it('CV_32SC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32SC4);
    });

    it('CV_32FC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32FC1);
    });

    it('CV_32FC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32FC2);
    });

    it('CV_32FC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32FC3);
    });

    it('CV_32FC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_32FC4);
    });

    it('CV_64FC1 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_64FC1);
    });

    it('CV_64FC2 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_64FC2);
    });

    it('CV_64FC3 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_64FC3);
    });

    it('CV_64FC4 should return correct values at each pixel position', () => {
      createAndAssertAtReturnsCorrectValues(matTypes.CV_64FC4);
    });
  });
};

