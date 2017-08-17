import { Mat, cvTypes } from 'dut';
import { assertError, funcRequiresArgsObject, readTestImage } from 'utils';
import { expect } from 'chai';
import { assertMetaData, assertDataDeepEquals, dangerousDeepEquals } from './matTestUtils';

const rgbMatData = [
  Array(5).fill([255, 125, 0]),
  Array(5).fill([0, 0, 0]),
  Array(5).fill([125, 75, 125]),
  Array(5).fill([75, 255, 75])
];
const rgbMat = new Mat(rgbMatData, cvTypes.CV_8UC3);

module.exports = () => {
  describe('bgrToGray', () => {
    it('should convert mat to gray scale', () => {
      const converted = rgbMat.bgrToGray();
      assertMetaData(converted)(rgbMat.rows, rgbMat.cols, cvTypes.CV_8U);
      expect(dangerousDeepEquals(converted.getDataAsArray(), rgbMatData)).to.be.false;
    });
  });

  describe('cvtColor', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.cvtColor.bind(mat);
    })());

    it('should throw if code invalid', () => {
      assertError(() => rgbMat.cvtColor({ code: undefined }), 'Invalid type for code');
      assertError(() => rgbMat.cvtColor({ code: null }), 'Invalid type for code');
    });

    it('should convert color', () => {
      const converted = rgbMat.cvtColor({ code: cvTypes.colorConversionCodes.COLOR_BGR2Lab });
      assertMetaData(converted)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(converted.getDataAsArray(), rgbMatData)).to.be.false;
    });
  });

  describe('erode', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.erode.bind(mat);
    })());

    it('should erode image', () => {
      const matData = Array(5).fill([0, 255, 0, 255, 0]);
      const kernelData = Array(3).fill([255, 255, 255]);
      const eroded = new Mat(matData, cvTypes.CV_8U).erode({
        kernel: new Mat(kernelData, cvTypes.CV_8U)
      });
      assertDataDeepEquals(Array(5).fill(Array(5).fill(0)), eroded.getDataAsArray());
    });
  });

  describe('dilate', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.dilate.bind(mat);
    })());

    it('should dilate image', () => {
      const matData = Array(5).fill([0, 255, 0, 255, 0]);
      const kernelData = Array(3).fill([255, 255, 255]);
      const eroded = new Mat(matData, cvTypes.CV_8U).dilate({
        kernel: new Mat(kernelData, cvTypes.CV_8U)
      });
      assertDataDeepEquals(Array(5).fill(Array(5).fill(255)), eroded.getDataAsArray());
    });
  });

  describe('warpPerspective', () => {
    funcRequiresArgsObject((() => {
      const mat = new Mat();
      return mat.warpPerspective.bind(mat);
    })());

    it('should warp image perspective', async () => {
      const img = await readTestImage();
      const transformationMatrix = new Mat(
        [
          [0.5, 0, 0],
          [0, 0.5, 0],
          [0, 0, 1]
        ],
        cvTypes.CV_64F
      );

      const warped = img.warpPerspective({ transformationMatrix });
      assertMetaData(warped)(img.rows, img.cols, img.type);
      expect(dangerousDeepEquals(warped.getDataAsArray(), img.getDataAsArray())).to.be.false;
    });
  });
};
