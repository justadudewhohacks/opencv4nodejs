import { Mat, matTypes } from 'dut';
import { assert, expect } from 'chai';
import { deepEquals, expectMetaData } from './matTestUtils';

const charMax = 127;
const charMin = -charMax - 1;
const ucharMax = (charMax * 2) + 1;

const shortMax = 32767;
const shortMin = -shortMax - 1;
const ushortMax = (shortMax * 2) + 1;

const intMax = 2147483647;
const intMin = -intMax - 1;

const floatMin = 1.8E-38;
const floatMax = 3.4E+38;

const doubleMin = 2.2E-308;
const doubleMax = 1.79E+308;

describe('Mat', () => {
  describe('constructor, getData', () => {
    it('should throw column must be an array', () => {
      let errMsg = '';
      try {
        const matData = [1, 1, 1];
        new Mat(matData, matTypes.CV_8U);
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
        new Mat(matData, matTypes.CV_8U);
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
      const type = matTypes.CV_8UC1;
      const matData = [
        [ucharMax, 0, 0],
        [0, ucharMax, 0],
        [0, 0, ucharMax],
        [ucharMax, 0, 0]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8UC2 with correct data', () => {
      const type = matTypes.CV_8UC2;
      const matData = [
        [[ucharMax, 0], [0, 0], [0, ucharMax]],
        [[0, 0], [ucharMax, 0], [0, ucharMax]],
        [[0, 0], [0, 0], [ucharMax, 0]],
        [[ucharMax, 0], [0, 0], [0, 0]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8UC3 with correct data', () => {
      const type = matTypes.CV_8UC3;
      const matData = [
        [[ucharMax, 0, 0], [0, 0, 0], [0, ucharMax, ucharMax]],
        [[0, 0, ucharMax], [ucharMax, 0, 0], [ucharMax, 0, ucharMax]],
        [[0, 0, ucharMax], [0, 0, 0], [ucharMax, 0, 0]],
        [[ucharMax, 0, ucharMax], [0, 0, 0], [0, 0, ucharMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8UC4 with correct data', () => {
      const type = matTypes.CV_8UC4;
      const matData = [
        [[ucharMax, 0, 0, 0], [ucharMax, 0, 0, 0], [0, ucharMax, ucharMax, ucharMax]],
        [[0, 0, ucharMax, 0], [ucharMax, ucharMax, 0, 0], [ucharMax, 0, ucharMax, ucharMax]],
        [[0, 0, ucharMax, 0], [ucharMax, 0, 0, 0], [ucharMax, 0, 0, ucharMax]],
        [[ucharMax, 0, ucharMax, 0], [ucharMax, 0, 0, 0], [0, 0, ucharMax, ucharMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8SC1 with correct data', () => {
      const type = matTypes.CV_8SC1;
      const matData = [
        [charMax, charMin, charMin],
        [charMin, charMax, charMin],
        [charMin, charMin, charMax],
        [charMax, charMin, charMin]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8SC2 with correct data', () => {
      const type = matTypes.CV_8SC2;
      const matData = [
        [[charMax, charMin], [charMin, charMin], [charMin, charMax]],
        [[charMin, charMin], [charMax, charMin], [charMin, charMax]],
        [[charMin, charMin], [charMin, charMin], [charMax, charMin]],
        [[charMax, charMin], [charMin, charMin], [charMin, charMin]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8SC3 with correct data', () => {
      const type = matTypes.CV_8SC3;
      const matData = [
        [[charMax, charMin, charMin], [charMin, charMin, charMin], [charMin, charMax, charMax]],
        [[charMin, charMin, charMax], [charMax, charMin, charMin], [charMax, charMin, charMax]],
        [[charMin, charMin, charMax], [charMin, charMin, charMin], [charMax, charMin, charMin]],
        [[charMax, charMin, charMax], [charMin, charMin, charMin], [charMin, charMin, charMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_8SC4 with correct data', () => {
      const type = matTypes.CV_8SC4;
      const matData = [
        [[charMax, charMin, charMin, charMin], [charMax, charMin, charMin, charMin], [charMin, charMax, charMax, charMax]],
        [[charMin, charMin, charMax, charMin], [charMax, charMax, charMin, charMin], [charMax, charMin, charMax, charMax]],
        [[charMin, charMin, charMax, charMin], [charMax, charMin, charMin, charMin], [charMax, charMin, charMin, charMax]],
        [[charMax, charMin, charMax, charMin], [charMax, charMin, charMin, charMin], [charMin, charMin, charMax, charMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16UC1 with correct data', () => {
      const type = matTypes.CV_16UC1;
      const matData = [
        [ushortMax, 0, 0],
        [0, ushortMax, 0],
        [0, 0, ushortMax],
        [ushortMax, 0, 0]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16UC2 with correct data', () => {
      const type = matTypes.CV_16UC2;
      const matData = [
        [[ushortMax, 0], [0, 0], [0, ushortMax]],
        [[0, 0], [ushortMax, 0], [0, ushortMax]],
        [[0, 0], [0, 0], [ushortMax, 0]],
        [[ushortMax, 0], [0, 0], [0, 0]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16UC3 with correct data', () => {
      const type = matTypes.CV_16UC3;
      const matData = [
        [[ushortMax, 0, 0], [0, 0, 0], [0, ushortMax, ushortMax]],
        [[0, 0, ushortMax], [ushortMax, 0, 0], [ushortMax, 0, ushortMax]],
        [[0, 0, ushortMax], [0, 0, 0], [ushortMax, 0, 0]],
        [[ushortMax, 0, ushortMax], [0, 0, 0], [0, 0, ushortMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16UC4 with correct data', () => {
      const type = matTypes.CV_16UC4;
      const matData = [
        [[ushortMax, 0, 0, 0], [ushortMax, 0, 0, 0], [0, ushortMax, ushortMax, ushortMax]],
        [[0, 0, ushortMax, 0], [ushortMax, ushortMax, 0, 0], [ushortMax, 0, ushortMax, ushortMax]],
        [[0, 0, ushortMax, 0], [ushortMax, 0, 0, 0], [ushortMax, 0, 0, ushortMax]],
        [[ushortMax, 0, ushortMax, 0], [ushortMax, 0, 0, 0], [0, 0, ushortMax, ushortMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16SC1 with correct data', () => {
      const type = matTypes.CV_16SC1;
      const matData = [
        [shortMax, shortMin, shortMin],
        [shortMin, shortMax, shortMin],
        [shortMin, shortMin, shortMax],
        [shortMax, shortMin, shortMin]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16SC2 with correct data', () => {
      const type = matTypes.CV_16SC2;
      const matData = [
        [[shortMax, shortMin], [shortMin, shortMin], [shortMin, shortMax]],
        [[shortMin, shortMin], [shortMax, shortMin], [shortMin, shortMax]],
        [[shortMin, shortMin], [shortMin, shortMin], [shortMax, shortMin]],
        [[shortMax, shortMin], [shortMin, shortMin], [shortMin, shortMin]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16SC3 with correct data', () => {
      const type = matTypes.CV_16SC3;
      const matData = [
        [[shortMax, shortMin, shortMin], [shortMin, shortMin, shortMin], [shortMin, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax], [shortMax, shortMin, shortMin], [shortMax, shortMin, shortMax]],
        [[shortMin, shortMin, shortMax], [shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin]],
        [[shortMax, shortMin, shortMax], [shortMin, shortMin, shortMin], [shortMin, shortMin, shortMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_16SC4 with correct data', () => {
      const type = matTypes.CV_16SC4;
      const matData = [
        [[shortMax, shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMin, shortMax, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax, shortMin], [shortMax, shortMax, shortMin, shortMin], [shortMax, shortMin, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin, shortMax]],
        [[shortMax, shortMin, shortMax, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMin, shortMin, shortMax, shortMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_32SC1 with correct data', () => {
      const type = matTypes.CV_32SC1;
      const matData = [
        [intMax, intMin, intMin],
        [intMin, intMax, intMin],
        [intMin, intMin, intMax],
        [intMax, intMin, intMin]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_32SC2 with correct data', () => {
      const type = matTypes.CV_32SC2;
      const matData = [
        [[intMax, intMin], [intMin, intMin], [intMin, intMax]],
        [[intMin, intMin], [intMax, intMin], [intMin, intMax]],
        [[intMin, intMin], [intMin, intMin], [intMax, intMin]],
        [[intMax, intMin], [intMin, intMin], [intMin, intMin]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_32SC3 with correct data', () => {
      const type = matTypes.CV_32SC3;
      const matData = [
        [[intMax, intMin, intMin], [intMin, intMin, intMin], [intMin, intMax, intMax]],
        [[intMin, intMin, intMax], [intMax, intMin, intMin], [intMax, intMin, intMax]],
        [[intMin, intMin, intMax], [intMin, intMin, intMin], [intMax, intMin, intMin]],
        [[intMax, intMin, intMax], [intMin, intMin, intMin], [intMin, intMin, intMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_32SC4 with correct data', () => {
      const type = matTypes.CV_32SC4;
      const matData = [
        [[intMax, intMin, intMin, intMin], [intMax, intMin, intMin, intMin], [intMin, intMax, intMax, intMax]],
        [[intMin, intMin, intMax, intMin], [intMax, intMax, intMin, intMin], [intMax, intMin, intMax, intMax]],
        [[intMin, intMin, intMax, intMin], [intMax, intMin, intMin, intMin], [intMax, intMin, intMin, intMax]],
        [[intMax, intMin, intMax, intMin], [intMax, intMin, intMin, intMin], [intMin, intMin, intMax, intMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_32FC1 with correct data', () => {
      const type = matTypes.CV_32FC1;
      const matData = [
        [floatMax, floatMin, floatMin],
        [floatMin, -floatMax, -floatMin],
        [floatMin, -floatMin, -floatMax],
        [floatMax, floatMin, floatMin]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(matTypes.CV_64FC1, 3, 4);
    });

    it('should initialize CV_32FC2 with correct data', () => {
      const type = matTypes.CV_32FC2;
      const matData = [
        [[floatMax, floatMin], [floatMin, floatMin], [floatMin, -floatMax]],
        [[floatMin, -floatMin], [floatMax, -floatMin], [-floatMin, floatMax]],
        [[floatMin, floatMin], [floatMin, -floatMin], [-floatMax, floatMin]],
        [[floatMax, -floatMin], [floatMin, floatMin], [floatMin, floatMin]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(matTypes.CV_64FC2, 3, 4);
    });

    it('should initialize CV_32FC3 with correct data', () => {
      const type = matTypes.CV_32FC3;
      const matData = [
        [[floatMax, -floatMin, floatMin], [floatMin, -floatMin, floatMin], [floatMin, -floatMax, floatMax]],
        [[floatMin, floatMin, -floatMax], [floatMax, floatMin, floatMin], [floatMax, floatMin, floatMax]],
        [[floatMin, floatMin, floatMax], [-floatMin, -floatMin, -floatMin], [floatMax, -floatMin, floatMin]],
        [[-floatMax, floatMin, floatMax], [floatMin, -floatMin, -floatMin], [floatMin, floatMin, floatMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(matTypes.CV_64FC3, 3, 4);
    });

    it('should initialize CV_32FC4 with correct data', () => {
      const type = matTypes.CV_32FC4;
      const matData = [
        [[floatMax, -floatMin, -floatMin, floatMin], [floatMax, floatMin, floatMin, floatMin], [-floatMin, -floatMax, floatMax, floatMax]],
        [[floatMin, floatMin, floatMax, floatMin], [-floatMax, -floatMax, -floatMin, -floatMin], [floatMax, floatMin, floatMax, floatMax]],
        [[floatMin, floatMin, floatMax, -floatMin], [floatMax, floatMin, -floatMin, floatMin], [-floatMax, -floatMin, floatMin, floatMax]],
        [[-floatMax, floatMin, floatMax, floatMin], [floatMax, floatMin, floatMin, -floatMin], [-floatMin, floatMin, floatMax, floatMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(matTypes.CV_64FC4, 3, 4);
    });

    it('should initialize CV_64FC1 with correct data', () => {
      const type = matTypes.CV_64FC1;
      const matData = [
        [doubleMax, doubleMin, doubleMin],
        [doubleMin, -doubleMax, -doubleMin],
        [doubleMin, -doubleMin, -doubleMax],
        [doubleMax, doubleMin, doubleMin]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_64FC2 with correct data', () => {
      const type = matTypes.CV_64FC2;
      const matData = [
        [[doubleMax, doubleMin], [doubleMin, doubleMin], [doubleMin, -doubleMax]],
        [[doubleMin, -doubleMin], [doubleMax, -doubleMin], [-doubleMin, doubleMax]],
        [[doubleMin, doubleMin], [doubleMin, -doubleMin], [-doubleMax, doubleMin]],
        [[doubleMax, -doubleMin], [doubleMin, doubleMin], [doubleMin, doubleMin]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_64FC3 with correct data', () => {
      const type = matTypes.CV_64FC3;
      const matData = [
        [[doubleMax, -doubleMin, doubleMin], [doubleMin, -doubleMin, doubleMin], [doubleMin, -doubleMax, doubleMax]],
        [[doubleMin, doubleMin, -doubleMax], [doubleMax, doubleMin, doubleMin], [doubleMax, doubleMin, doubleMax]],
        [[doubleMin, doubleMin, doubleMax], [-doubleMin, -doubleMin, -doubleMin], [doubleMax, -doubleMin, doubleMin]],
        [[-doubleMax, doubleMin, doubleMax], [doubleMin, -doubleMin, -doubleMin], [doubleMin, doubleMin, doubleMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });

    it('should initialize CV_64FC4 with correct data', () => {
      const type = matTypes.CV_64FC4;
      const matData = [
        [[doubleMax, -doubleMin, -doubleMin, doubleMin], [doubleMax, doubleMin, doubleMin, doubleMin], [-doubleMin, -doubleMax, doubleMax, doubleMax]],
        [[doubleMin, doubleMin, doubleMax, doubleMin], [-doubleMax, -doubleMax, -doubleMin, -doubleMin], [doubleMax, doubleMin, doubleMax, doubleMax]],
        [[doubleMin, doubleMin, doubleMax, -doubleMin], [doubleMax, doubleMin, -doubleMin, doubleMin], [-doubleMax, -doubleMin, doubleMin, doubleMax]],
        [[-doubleMax, doubleMin, doubleMax, doubleMin], [doubleMax, doubleMin, doubleMin, -doubleMin], [-doubleMin, doubleMin, doubleMax, doubleMax]]
      ];
      const mat = new Mat(matData, type);
      expect(deepEquals(matData, mat.getData())).to.be.true;
      expectMetaData(mat)(type, 3, 4);
    });
  });
});
