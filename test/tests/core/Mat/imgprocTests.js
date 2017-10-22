const cv = global.dut;

const {
  generateAPITests,
  assertError,
  asyncFuncShouldRequireArgs,
  funcShouldRequireArgs,
  _funcShouldRequireArgs,
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

module.exports = (getTestImg) => {
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
    let img;
    let size;
    before(() => {
      img = getTestImg();
      size = new cv.Size(img.cols, img.rows);
    });

    const expectOutput = (warped) => {
      assertMetaData(warped)(img.rows, img.cols, img.type);
    };

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

    generateAPITests({
      getDut: () => img,
      methodName: 'warpAffine',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        transformationMatrixAffine
      ]),
      getOptionalArgsMap: () => ([
        ['size', size],
        ['flags', cv.INTER_CUBIC],
        ['borderMode', cv.BORDER_REFLECT]
      ]),
      expectOutput
    });

    generateAPITests({
      getDut: () => img,
      methodName: 'warpPerspective',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        transformationMatrix
      ]),
      getOptionalArgsMap: () => ([
        ['size', size],
        ['flags', cv.INTER_CUBIC],
        ['borderMode', cv.BORDER_REFLECT]
      ]),
      expectOutput
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

  describe('blur', () => {
    const kSize = new cv.Size(3, 3);
    const anchor = new cv.Point(1, 1);
    const borderType = cv.BORDER_CONSTANT;
    funcShouldRequireArgs((() => rgbMat.blur.bind(rgbMat))());

    it('can be called if required args passed', () => {
      expect(() => rgbMat.blur(kSize)).to.not.throw();
    });

    it('can be called with optional args', () => {
      expect(() => rgbMat.blur(
        kSize,
        anchor,
        borderType
      )).to.not.throw();
    });

    it('can be called with optional args object', () => {
      expect(() => rgbMat.blur(
        kSize,
        { anchor, borderType }
      )).to.not.throw();
    });

    it('should blur something', () => {
      const blurred = rgbMat.blur(kSize);
      assertMetaData(blurred)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(blurred.getDataAsArray(), rgbMat.getDataAsArray())).to.be.false;
    });
  });

  describe('gaussianBlur', () => {
    const kSize = new cv.Size(3, 3);
    const sigmaX = 1.2;
    const sigmaY = 0.8;
    const borderType = cv.BORDER_CONSTANT;
    funcShouldRequireArgs((() => rgbMat.gaussianBlur.bind(rgbMat))());

    it('can be called if required args passed', () => {
      expect(() => rgbMat.gaussianBlur(kSize, sigmaX)).to.not.throw();
    });

    it('can be called with optional args', () => {
      expect(() => rgbMat.gaussianBlur(
        kSize,
        sigmaX,
        sigmaY,
        borderType
      )).to.not.throw();
    });

    it('can be called with optional args object', () => {
      expect(() => rgbMat.gaussianBlur(
        kSize,
        sigmaX,
        { sigmaY, borderType }
      )).to.not.throw();
    });

    it('should blur something', () => {
      const blurred = rgbMat.gaussianBlur(kSize, sigmaX);
      assertMetaData(blurred)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(blurred.getDataAsArray(), rgbMat.getDataAsArray())).to.be.false;
    });
  });

  describe('medianBlur', () => {
    const kSize = 3;

    funcShouldRequireArgs((() => rgbMat.medianBlur.bind(rgbMat))());

    it('should blur something', () => {
      const blurred = rgbMat.medianBlur(kSize);
      assertMetaData(blurred)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(blurred.getDataAsArray(), rgbMat.getDataAsArray())).to.be.false;
    });
  });

  describe('thresholding', () => {
    const mat = new cv.Mat([
      [255, 255, 255],
      [0, 100, 101]
    ], cv.CV_8U);

    describe('threshold', () => {
      const expectOutput = (thresholded) => {
        assertMetaData(thresholded)(mat.rows, mat.cols, cv.CV_8U);
        assertDataDeepEquals(
          [
            [255, 255, 255],
            [0, 0, 255]
          ],
          thresholded.getDataAsArray()
        );
      };

      const th = 100;
      const maxVal = 255;
      const thresholdType = cv.THRESH_BINARY;

      generateAPITests({
        getDut: () => mat,
        methodName: 'threshold',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          th,
          maxVal,
          thresholdType
        ]),
        expectOutput
      });
    });

    describe('adaptiveThreshold', () => {
      const expectOutput = (thresholded) => {
        assertMetaData(thresholded)(mat.rows, mat.cols, cv.CV_8U);
      };

      const maxVal = 255;
      const adaptiveMethod = cv.ADAPTIVE_THRESH_MEAN_C;
      const thresholdType = cv.THRESH_BINARY;
      const blockSize = 3;
      const C = 0.9;

      generateAPITests({
        getDut: () => mat,
        methodName: 'adaptiveThreshold',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          maxVal,
          adaptiveMethod,
          thresholdType,
          blockSize,
          C
        ]),
        expectOutput
      });
    });
  });

  describe('grabCut', () => {
    const img = new cv.Mat([
      [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]],
      [[0, 0, 0], [255, 255, 255], [255, 255, 255], [255, 255, 255], [0, 0, 0]],
      [[0, 0, 0], [255, 255, 255], [255, 255, 255], [255, 255, 255], [0, 0, 0]],
      [[0, 0, 0], [255, 255, 255], [255, 255, 255], [255, 255, 255], [0, 0, 0]],
      [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]
    ], cv.CV_8UC3);

    funcShouldRequireArgs((() => img.grabCut.bind(img))());

    it('can be called with mask', () => {
      const mask = new cv.Mat([
        [cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD],
        [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
        [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
        [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
        [cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD]
      ], cv.CV_8U);
      const rect = new cv.Rect();
      const bgdModel = new cv.Mat(1, 65, cv.CV_64F, 0);
      const fgdModel = new cv.Mat(1, 65, cv.CV_64F, 0);
      const iterCount = 4;
      const mode = cv.GC_INIT_WITH_MASK;

      img.grabCut(mask, rect, bgdModel, fgdModel, iterCount, mode);
      expect(isZeroMat(bgdModel)).to.be.false;
      expect(isZeroMat(fgdModel)).to.be.false;
    });

    it('can be called with roi rect', () => {
      const mask = new cv.Mat(img.rows, img.cols, cv.CV_8U);
      const rect = new cv.Rect(1, 1, 3, 3);
      const bgdModel = new cv.Mat(1, 65, cv.CV_64F, 0);
      const fgdModel = new cv.Mat(1, 65, cv.CV_64F, 0);
      const iterCount = 4;
      const mode = cv.GC_INIT_WITH_RECT;

      img.grabCut(mask, rect, bgdModel, fgdModel, iterCount, mode);
      expect(isZeroMat(mask)).to.be.false;
      expect(isZeroMat(bgdModel)).to.be.false;
      expect(isZeroMat(fgdModel)).to.be.false;
    });
  });

  describe('matchTemplate', () => {
    let img;
    const templOffset = { x: 10, y: 10 };
    let templ;
    before(() => {
      img = getTestImg().bgrToGray();
      templ = img.getRegion(new cv.Rect(templOffset.x, templOffset.y, img.cols / 8, img.rows / 8));
    });

    const getImg = () => img;

    const expectOutput = (res) => {
      expect(res).instanceOf(cv.Mat);
      expect(res.cols).to.equal((img.cols - templ.cols) + 1);
      expect(res.rows).to.equal((img.rows - templ.rows) + 1);
      expect(res).instanceOf(cv.Mat);
      const minLoc = res.minMaxLoc().minLoc;
      expect(minLoc.x).to.equal(templOffset.x);
      expect(minLoc.y).to.equal(templOffset.y);
    };

    const expectWithMaskOutput = (res) => {
      expect(res).instanceOf(cv.Mat);
      expect(res.cols).to.equal((img.cols - templ.cols) + 1);
      expect(res.rows).to.equal((img.rows - templ.rows) + 1);
      expect(res).instanceOf(cv.Mat);
      const minLoc = res.minMaxLoc().minLoc;
      expect(minLoc.x).to.equal(templOffset.x);
      expect(minLoc.y).to.equal(templOffset.y);
    };

    describe('sync', () => {
      _funcShouldRequireArgs(() => getImg().matchTemplate());

      it('should return match results', () => {
        expectOutput(img.matchTemplate(templ, cv.TM_SQDIFF_NORMED));
      });

      it('should match template with mask', () => {
        const mask = new cv.Mat(templ.rows, templ.cols, cv.CV_8U, 0);
        const maskedRegion = new cv.Mat(templ.rows / 2, templ.cols / 2, cv.CV_8U, 1);
        maskedRegion.copyTo(mask.getRegion(new cv.Rect(0, 0, templ.cols / 2, templ.rows / 2)));

        expectWithMaskOutput(img.matchTemplate(templ, cv.TM_SQDIFF, mask));
      });
    });

    describe('async', () => {
      asyncFuncShouldRequireArgs(() => getImg().matchTemplateAsync());

      it('should return match results', (done) => {
        img.matchTemplateAsync(templ, cv.TM_SQDIFF_NORMED, (err, res) => {
          expectOutput(res);
          done();
        });
      });

      it('should match template with mask', (done) => {
        const mask = new cv.Mat(templ.rows, templ.cols, cv.CV_8U, 0);
        const maskedRegion = new cv.Mat(templ.rows / 2, templ.cols / 2, cv.CV_8U, 1);
        maskedRegion.copyTo(mask.getRegion(new cv.Rect(0, 0, templ.cols / 2, templ.rows / 2)));

        img.matchTemplateAsync(templ, cv.TM_SQDIFF, mask, (err, res) => {
          expectWithMaskOutput(res);
          done();
        });
      });
    });
  });

  describe('derivative filters', () => {
    let img;
    before(() => {
      img = getTestImg();
    });

    const expectOutput = (binImg) => {
      assertMetaData(binImg)(img.rows, img.cols, cv.CV_64FC3);
    };

    describe('canny', () => {
      const th1 = 2.8;
      const th2 = 0.8;

      generateAPITests({
        getDut: () => img,
        methodName: 'canny',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          th1,
          th2
        ]),
        getOptionalArgsMap: () => ([
          ['apertureSize', 5],
          ['L2gradient', true]
        ]),
        expectOutput: (binImg) => {
          assertMetaData(binImg)(img.rows, img.cols, cv.CV_8U);
        }
      });
    });

    describe('sobel', () => {
      const ddepth = cv.CV_64F;
      const dx = 1;
      const dy = 0;

      generateAPITests({
        getDut: () => img,
        methodName: 'sobel',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          ddepth,
          dx,
          dy
        ]),
        getOptionalArgsMap: () => ([
          ['ksize', 5],
          ['scale', 2],
          ['delta', 0.5],
          ['borderType', cv.BORDER_CONSTANT]
        ]),
        expectOutput
      });
    });

    describe('scharr', () => {
      const ddepth = cv.CV_64F;
      const dx = 1;
      const dy = 0;

      generateAPITests({
        getDut: () => img,
        methodName: 'scharr',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          ddepth,
          dx,
          dy
        ]),
        getOptionalArgsMap: () => ([
          ['scale', 2],
          ['delta', 0.5],
          ['borderType', cv.BORDER_CONSTANT]
        ]),
        expectOutput
      });
    });

    describe('laplacian', () => {
      const ddepth = cv.CV_64F;

      generateAPITests({
        getDut: () => img,
        methodName: 'laplacian',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          ddepth
        ]),
        getOptionalArgsMap: () => ([
          ['ksize', 5],
          ['scale', 2],
          ['delta', 0.5],
          ['borderType', cv.BORDER_CONSTANT]
        ]),
        expectOutput
      });
    });
  });
};
