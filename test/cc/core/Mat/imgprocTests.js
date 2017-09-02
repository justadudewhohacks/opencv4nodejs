import cv from 'dut';

import {
  assertError,
  funcRequiresArgsObject,
  readTestImage,
  assertMetaData,
  assertDataDeepEquals,
  dangerousDeepEquals,
  isZeroMat
} from 'utils';
import { expect } from 'chai';

const { Mat, cvTypes } = cv;

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
      const img = readTestImage();
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


  describe('drawing', () => {
    it('drawLine', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawLine({
        pt1: new cv.Point(0, 0),
        pt2: new cv.Point(9, 9),
        color: new cv.Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawCircle', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawCircle({
        center: new cv.Point(4, 4),
        radius: 2,
        color: new cv.Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawRectangle', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawRectangle({
        pt1: new cv.Point(2, 2),
        pt2: new cv.Point(8, 8),
        color: new cv.Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    it('drawEllipse', () => {
      const mat = new Mat(10, 10, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.drawEllipse({
        box: new cv.RotatedRect(new cv.Point(4, 4), new cv.Size(4, 4), Math.PI / 4),
        color: new cv.Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });

    // TODO
    it('putText', () => {
      const mat = new Mat(20, 20, cvTypes.CV_8UC3, [0, 0, 0]);
      const ret = mat.putText({
        text: 'a',
        org: new cv.Point(0, 20),
        fontFace: cv.cvTypes.hersheyFonts.FONT_ITALIC,
        fontScale: 1,
        color: new cv.Vec(255, 255, 255)
      });
      expect(ret).to.equal(mat);
      expect(isZeroMat(mat)).to.be.false;
    });
  });

  describe.skip('distanceTransform', () => {
    it('distanceTransform', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('distanceTransformWithLabels', () => {
    it('distanceTransformWithLabels', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('blur', () => {
    it('blur', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('gaussianBlur', () => {
    it('gaussianBlur', () => {
      expect(true).to.be.false;
    });
  });

  describe.skip('medianBlur', () => {
    it('medianBlur', () => {
      expect(true).to.be.false;
    });
  });
};
