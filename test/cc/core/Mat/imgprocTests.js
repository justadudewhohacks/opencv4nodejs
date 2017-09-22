const cv = global.dut;

const {
  assertError,
  funcShouldRequireArgs,
  readTestImage,
  assertMetaData,
  assertDataDeepEquals,
  dangerousDeepEquals,
  isZeroMat
} = global.utils;
const { expect } = require('chai');

const rgbMatData = [
  Array(5).fill([255, 125, 0]),
  Array(5).fill([0, 0, 0]),
  Array(5).fill([125, 75, 125]),
  Array(5).fill([75, 255, 75])
];
const rgbMat = new cv.Mat(rgbMatData, cv.CV_8UC3);

module.exports = () => {
  describe('bgrToGray', () => {
    it('should convert mat to gray scale', () => {
      const converted = rgbMat.bgrToGray();
      assertMetaData(converted)(rgbMat.rows, rgbMat.cols, cv.CV_8U);
      expect(dangerousDeepEquals(converted.getDataAsArray(), rgbMatData)).to.be.false;
    });
  });

  describe('cvtColor', () => {
    funcShouldRequireArgs((() => new cv.Mat().cvtColor.bind(new cv.Mat()))());

    it('can be called if required args passed', () => {
      expect(() => rgbMat.cvtColor(cv.COLOR_BGR2Lab)).to.not.throw();
    });

    it('should throw if code invalid', () => {
      assertError(() => rgbMat.cvtColor(undefined), 'Mat::CvtColor - expected arg 0 to be of type: UINT');
      assertError(() => rgbMat.cvtColor(null), 'Mat::CvtColor - expected arg 0 to be of type: UINT');
    });

    it('should convert color', () => {
      const converted = rgbMat.cvtColor(cv.COLOR_BGR2Lab);
      assertMetaData(converted)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(converted.getDataAsArray(), rgbMatData)).to.be.false;
    });
  });

  describe('morphological operators', () => {
    const mat = new cv.Mat(Array(5).fill([0, 255, 0, 255, 0]), cv.CV_8U);
    const kernel = new cv.Mat(Array(3).fill([255, 255, 255]), cv.CV_8U);
    const iterations = 5;
    const borderType = cv.BORDER_REFLECT;
    describe('erode', () => {
      funcShouldRequireArgs((() => new cv.Mat().erode.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => mat.erode(kernel)).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => mat.erode(kernel, iterations, borderType)).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => mat.erode(kernel, { borderType })).to.not.throw();
      });

      it('should erode image', () => {
        const eroded = mat.erode(kernel);
        assertDataDeepEquals(Array(5).fill(Array(5).fill(0)), eroded.getDataAsArray());
      });
    });

    describe('dilate', () => {
      funcShouldRequireArgs((() => new cv.Mat().dilate.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => mat.dilate(kernel)).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => mat.dilate(kernel, iterations, borderType)).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => mat.dilate(kernel, { borderType })).to.not.throw();
      });

      it('should dilate image', () => {
        const dilated = mat.dilate(kernel);
        assertDataDeepEquals(Array(5).fill(Array(5).fill(255)), dilated.getDataAsArray());
      });
    });
  });

  describe('warping', () => {
    const img = readTestImage();
    const transformationMatrix = new cv.Mat(
      [
        [0.5, 0, 0],
        [0, 0.5, 0],
        [0, 0, 1]
      ],
      cv.CV_64F
    );
    const transformationMatrixAffine = new cv.Mat(
      [
        [0.5, 0, 0],
        [0, 0.5, 1]
      ],
      cv.CV_64F
    );
    const flags = cv.INTER_CUBIC;

    describe('warpAffine', () => {
      funcShouldRequireArgs((() => new cv.Mat().warpAffine.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => img.warpAffine(transformationMatrixAffine)).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => img.warpAffine(transformationMatrixAffine, flags)).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => img.warpAffine(transformationMatrixAffine, { flags })).to.not.throw();
      });

      it('should warp image perspective', () => {
        const warped = img.warpAffine(transformationMatrixAffine);
        assertMetaData(warped)(img.rows, img.cols, img.type);
        expect(dangerousDeepEquals(warped.getDataAsArray(), img.getDataAsArray())).to.be.false;
      });
    });

    describe('warpPerspective', () => {
      funcShouldRequireArgs((() => new cv.Mat().warpPerspective.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => img.warpPerspective(transformationMatrix)).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => img.warpPerspective(transformationMatrix, flags)).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => img.warpPerspective(transformationMatrix, { flags })).to.not.throw();
      });

      it('should warp image perspective', () => {
        const warped = img.warpPerspective(transformationMatrix);
        assertMetaData(warped)(img.rows, img.cols, img.type);
        expect(dangerousDeepEquals(warped.getDataAsArray(), img.getDataAsArray())).to.be.false;
      });
    });
  });

  describe('drawing', () => {
    const getImg = () => new cv.Mat(10, 10, cv.CV_8UC3, [0, 0, 0]);
    const color = new cv.Vec(255, 255, 255);
    const thickness = 2;
    const lineType = cv.LINE_4;

    describe('drawLine', () => {
      const ptFrom = new cv.Point(0, 0);
      const ptTo = new cv.Point(9, 9);

      funcShouldRequireArgs((() => new cv.Mat().drawLine.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => getImg().drawLine(
          ptFrom,
          ptTo,
          color
        )).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => getImg().drawLine(
          ptFrom,
          ptTo,
          color,
          lineType,
          thickness
        )).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => getImg().drawLine(
          ptFrom,
          ptTo,
          color,
          { thickness })).to.not.throw();
      });

      it('should draw something', () => {
        const img = getImg();
        const ret = img.drawLine(
          ptFrom,
          ptTo,
          color
        );
        expect(ret).to.equal(img);
        expect(isZeroMat(img)).to.be.false;
      });
    });

    describe('drawCircle', () => {
      const center = new cv.Point(4, 4);
      const radius = 2;
      funcShouldRequireArgs((() => new cv.Mat().drawCircle.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => getImg().drawCircle(
          center,
          radius,
          color
        )).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => getImg().drawCircle(
          center,
          radius,
          color,
          lineType,
          thickness
        )).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => getImg().drawCircle(
          center,
          radius,
          color,
          { thickness })).to.not.throw();
      });

      it('should draw something', () => {
        const mat = getImg();
        const ret = mat.drawCircle(
          center,
          radius,
          color
        );
        expect(ret).to.equal(mat);
        expect(isZeroMat(mat)).to.be.false;
      });
    });

    describe('drawRectangle', () => {
      const upperLeft = new cv.Point(2, 2);
      const bottomRight = new cv.Point(8, 8);
      funcShouldRequireArgs((() => new cv.Mat().drawRectangle.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => getImg().drawRectangle(
          upperLeft,
          bottomRight,
          color
        )).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => getImg().drawRectangle(
          upperLeft,
          bottomRight,
          color,
          lineType,
          thickness
        )).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => getImg().drawRectangle(
          upperLeft,
          bottomRight,
          color,
          { thickness })).to.not.throw();
      });

      it('should draw something', () => {
        const mat = getImg();
        const ret = mat.drawRectangle(
          upperLeft,
          bottomRight,
          color
        );
        expect(ret).to.equal(mat);
        expect(isZeroMat(mat)).to.be.false;
      });
    });

    describe('drawEllipse', () => {
      const center = new cv.Point(4, 4);
      const box = new cv.RotatedRect(center, new cv.Size(4, 4), Math.PI / 4);

      funcShouldRequireArgs((() => new cv.Mat().drawEllipse.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => getImg().drawEllipse(
          box,
          color
        )).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => getImg().drawEllipse(
          box,
          color,
          lineType,
          thickness
        )).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => getImg().drawEllipse(
          box,
          color,
          { thickness })).to.not.throw();
      });

      it('should draw something', () => {
        const mat = getImg();
        const ret = mat.drawEllipse(
          box,
          color
        );
        expect(ret).to.equal(mat);
        expect(isZeroMat(mat)).to.be.false;
      });
    });

    describe('putText', () => {
      const text = 'a';
      const origin = new cv.Point(0, 20);
      const fontFace = cv.FONT_ITALIC;
      const fontScale = 1.2;

      funcShouldRequireArgs((() => new cv.Mat().putText.bind(new cv.Mat()))());

      it('can be called if required args passed', () => {
        expect(() => getImg().putText(
          text,
          origin,
          fontFace,
          fontScale,
          color
        )).to.not.throw();
      });

      it('can be called with optional args', () => {
        expect(() => getImg().putText(
          text,
          origin,
          fontFace,
          fontScale,
          color,
          lineType,
          thickness
        )).to.not.throw();
      });

      it('can be called with optional args object', () => {
        expect(() => getImg().putText(
          text,
          origin,
          fontFace,
          fontScale,
          color,
          { thickness }
        )).to.not.throw();
      });

      it('should draw something', () => {
        const mat = new cv.Mat(20, 20, cv.CV_8UC3, [0, 0, 0]);
        const ret = mat.putText(
          text,
          origin,
          fontFace,
          fontScale,
          color
        );
        expect(ret).to.equal(mat);
        expect(isZeroMat(mat)).to.be.false;
      });
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
