import { Mat, matTypes, Vec } from 'dut';
import { assertError } from 'utils';
import { expect } from 'chai';
import { getExampleMatData } from './exampleData';
import { assertMatValueEquals, assertDataDeepEquals, generateIts } from './matTestUtils';

const createAndAssertAtReturnsCorrectValues = (type) => {
  const matData = getExampleMatData(type);
  const mat = new Mat(matData, type);
  for (let r = 0; r < 4; r += 1) {
    for (let c = 0; c < 3; c += 1) {
      assertMatValueEquals(mat.at(r, c), matData[r][c]);
    }
  }
};

const createAndAssertSetsCorrectArrayValues = (type) => {
  const matData = getExampleMatData(type);
  const mat = new Mat(4, 3, type);
  for (let r = 0; r < 4; r += 1) {
    for (let c = 0; c < 3; c += 1) {
      mat.set(r, c, matData[r][c]);
    }
  }
  assertDataDeepEquals(matData, mat.getDataAsArray());
};

const createAndAssertSetsCorrectVecValues = (type) => {
  const matData = getExampleMatData(type);
  const mat = new Mat(4, 3, type);
  for (let r = 0; r < 4; r += 1) {
    for (let c = 0; c < 3; c += 1) {
      const arr = matData[r][c];
      const vec = arr.length === 2 ? new Vec(arr[0], arr[1]) :
        (arr.length === 3 ? new Vec(arr[0], arr[1], arr[2]) : new Vec(arr[0], arr[1], arr[2], arr[3]));
      mat.set(r, c, vec);
    }
  }
  assertDataDeepEquals(matData, mat.getDataAsArray());
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

    generateIts('should return correct values at each pixel position', createAndAssertAtReturnsCorrectValues);
  });

  describe('atRaw', () => {
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

