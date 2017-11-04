const cv = global.dut;

const {
  generateAPITests,
  asyncFuncShouldRequireArgs,
  funcShouldRequireArgs,
  _funcShouldRequireArgs,
  assertMetaData,
  assertDataDeepEquals,
  assertMatValueEquals,
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
  describe('resizing', () => {
    describe('rescale', () => {
      const mat = new cv.Mat(16, 16, cv.CV_8UC3);
      const factor = 2.0;

      const expectOutput = (res) => {
        assertMetaData(res)(mat.rows * 2, mat.cols * 2, cv.CV_8UC3);
      };

      generateAPITests({
        getDut: () => mat,
        methodName: 'rescale',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          factor
        ]),
        expectOutput
      });
    });

    describe('resize', () => {
      const rows = 8;
      const cols = 8;
      const mat = new cv.Mat(16, 16, cv.CV_8UC3);

      const expectOutput = (res) => {
        assertMetaData(res)(rows, cols, cv.CV_8UC3);
      };

      generateAPITests({
        getDut: () => mat,
        methodName: 'resize',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          rows,
          cols
        ]),
        expectOutput
      });
    });

    describe('resizeToMax', () => {
      const mat = new cv.Mat(16, 32, cv.CV_8UC3);
      const maxRowsOrCols = 8;

      const expectOutput = (res) => {
        assertMetaData(res)(4, 8, cv.CV_8UC3);
      };

      generateAPITests({
        getDut: () => mat,
        methodName: 'resizeToMax',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          maxRowsOrCols
        ]),
        expectOutput
      });
    });
  });

  describe('bgrToGray', () => {
    const expectOutput = (res) => {
      assertMetaData(res)(rgbMat.rows, rgbMat.cols, cv.CV_8U);
    };

    generateAPITests({
      getDut: () => rgbMat,
      methodName: 'bgrToGray',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('cvtColor', () => {
    const expectOutput = (res) => {
      assertMetaData(res)(rgbMat.rows, rgbMat.cols, cv.CV_8UC3);
      expect(dangerousDeepEquals(res.getDataAsArray(), rgbMatData)).to.be.false;
    };

    generateAPITests({
      getDut: () => rgbMat,
      methodName: 'cvtColor',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        cv.COLOR_BGR2Lab
      ]),
      expectOutput
    });
  });

  describe('morphological operators', () => {
    const mat = new cv.Mat(Array(5).fill([0, 255, 0, 255, 0]), cv.CV_8U);
    const kernel = new cv.Mat(Array(3).fill([255, 255, 255]), cv.CV_8U);

    const optionalArgsMap = [
      ['anchor', new cv.Point(0, 0)],
      ['iterations', 5],
      ['borderType', cv.BORDER_REFLECT]
    ];

    describe('erode', () => {
      const expectOutput = (eroded) => {
        assertDataDeepEquals(Array(5).fill(Array(5).fill(0)), eroded.getDataAsArray());
      };

      generateAPITests({
        getDut: () => mat,
        methodName: 'erode',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kernel
        ]),
        getOptionalArgsMap: () => optionalArgsMap,
        expectOutput
      });
    });

    describe('dilate', () => {
      const expectOutput = (dilated) => {
        assertDataDeepEquals(Array(5).fill(Array(5).fill(255)), dilated.getDataAsArray());
      };

      generateAPITests({
        getDut: () => mat,
        methodName: 'dilate',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kernel
        ]),
        getOptionalArgsMap: () => optionalArgsMap,
        expectOutput
      });
    });

    describe('morphologyEx', () => {
      const expectOutput = (morphed) => {
        assertMetaData(mat)(morphed);
      };

      const op = cv.MORPH_TOPHAT;

      generateAPITests({
        getDut: () => mat,
        methodName: 'morphologyEx',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kernel,
          op
        ]),
        getOptionalArgsMap: () => optionalArgsMap,
        expectOutput
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

  describe('distanceTransform', () => {
    const grayMat = new cv.Mat([
      [0, 0, 0, 0, 0],
      [0, 128, 255, 128, 0],
      [0, 255, 255, 255, 0],
      [0, 128, 255, 128, 0],
      [0, 0, 0, 0, 0]
    ], cv.CV_8U);
    const distanceType = cv.DIST_L1;
    const maskSize = 3;

    describe('distanceTransform', () => {
      const dstType = cv.CV_8U;

      const expectOutput = (res, dut, args) => {
        const assertType = args.length > 2 && args[2] === cv.CV_8U ? cv.CV_8U : cv.CV_32F;
        assertMetaData(res)(grayMat.rows, grayMat.cols, assertType);
      };

      generateAPITests({
        getDut: () => grayMat,
        methodName: 'distanceTransform',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distanceType,
          maskSize
        ]),
        getOptionalArgs: () => ([
          dstType
        ]),
        expectOutput
      });
    });

    describe('distanceTransformWithLabels', () => {
      const distLabelType = cv.DIST_LABEL_PIXEL;

      const expectOutput = (res) => {
        expect(res).to.have.property('dst').instanceOf(cv.Mat);
        expect(res).to.have.property('labels').instanceOf(cv.Mat);
        assertMetaData(res.dst)(grayMat.rows, grayMat.cols, cv.CV_32F);
        assertMetaData(res.labels)(grayMat.rows, grayMat.cols, cv.CV_32S);
      };

      generateAPITests({
        getDut: () => grayMat,
        methodName: 'distanceTransformWithLabels',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distanceType,
          maskSize
        ]),
        getOptionalArgs: () => ([
          distLabelType
        ]),
        expectOutput
      });
    });
  });

  describe('smoothing', () => {
    const expectOutput = (blurred) => {
      assertMetaData(blurred)(rgbMat.rows, rgbMat.cols, rgbMat.type);
      expect(dangerousDeepEquals(blurred.getDataAsArray(), rgbMat.getDataAsArray())).to.be.false;
    };

    describe('blur', () => {
      const kSize = new cv.Size(3, 3);

      generateAPITests({
        getDut: () => rgbMat,
        methodName: 'blur',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kSize
        ]),
        getOptionalArgsMap: () => ([
          ['anchor', new cv.Point(1, 1)],
          ['borderType', cv.BORDER_CONSTANT]
        ]),
        expectOutput
      });
    });

    describe('gaussianBlur', () => {
      const kSize = new cv.Size(3, 3);
      const sigmaX = 1.2;

      generateAPITests({
        getDut: () => rgbMat,
        methodName: 'gaussianBlur',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kSize,
          sigmaX
        ]),
        getOptionalArgsMap: () => ([
          ['sigmaY', 1.2],
          ['borderType', cv.BORDER_CONSTANT]
        ]),
        expectOutput
      });
    });

    describe('medianBlur', () => {
      const kSize = 3;

      generateAPITests({
        getDut: () => rgbMat,
        methodName: 'medianBlur',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          kSize
        ]),
        expectOutput
      });
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

  describe('connectedComponents', () => {
    const connectedComponentsMat = new cv.Mat([
      [0, 255, 255, 255, 0],
      [0, 255, 255, 255, 0],
      [0, 255, 255, 255, 0],
      [0, 0, 0, 0, 0],
      [0, 0, 0, 0, 0]
    ], cv.CV_8U);

    const connectivity = 4;
    const ltype = cv.CV_16U;

    describe('connectedComponents', () => {
      const expectOutput = (res, dut, args) => {
        const assertType = (args[1] === cv.CV_16U || (args[0] && args[0].ltype === cv.CV_16U)) ? cv.CV_16U : cv.CV_32S;
        assertMetaData(res)(connectedComponentsMat.rows, connectedComponentsMat.cols, assertType);
      };

      generateAPITests({
        getDut: () => connectedComponentsMat,
        methodName: 'connectedComponents',
        methodNameSpace: 'Mat',
        getOptionalArgsMap: () => ([
          ['connectivity', connectivity],
          ['ltype', ltype]
        ]),
        expectOutput
      });
    });

    describe('connectedComponentsWithStats', () => {
      const expectOutput = (res, dut, args) => {
        const assertType = (args[1] === cv.CV_16U || (args[0] && args[0].ltype === cv.CV_16U)) ? cv.CV_16U : cv.CV_32S;
        expect(res).to.have.property('labels').instanceOf(cv.Mat);
        expect(res).to.have.property('stats').instanceOf(cv.Mat);
        expect(res).to.have.property('centroids').instanceOf(cv.Mat);
        assertMetaData(res.labels)(connectedComponentsMat.rows, connectedComponentsMat.cols, assertType);
        expect(isZeroMat(res.labels)).to.be.false;
        const label0 = res.labels.at(0, 0);
        const label255 = res.labels.at(0, 1);
        const centroid = [
          res.centroids.at(label255, 0),
          res.centroids.at(label255, 1)
        ];
        const expectedCenter = [2, 1];
        assertMatValueEquals(centroid, expectedCenter);
        expect(res.stats.at(label255, cv.CC_STAT_LEFT)).to.equal(1);
        expect(res.stats.at(label255, cv.CC_STAT_TOP)).to.equal(0);
        expect(res.stats.at(label255, cv.CC_STAT_WIDTH)).to.equal(3);
        expect(res.stats.at(label255, cv.CC_STAT_HEIGHT)).to.equal(3);
        expect(res.stats.at(label255, cv.CC_STAT_AREA)).to.equal(9);
        expect(res.stats.at(label0, cv.CC_STAT_LEFT)).to.equal(0);
        expect(res.stats.at(label0, cv.CC_STAT_TOP)).to.equal(0);
        expect(res.stats.at(label0, cv.CC_STAT_WIDTH)).to.equal(5);
        expect(res.stats.at(label0, cv.CC_STAT_HEIGHT)).to.equal(5);
        expect(res.stats.at(label0, cv.CC_STAT_AREA)).to.equal(16);
      };

      generateAPITests({
        getDut: () => connectedComponentsMat,
        methodName: 'connectedComponentsWithStats',
        methodNameSpace: 'Mat',
        getOptionalArgsMap: () => ([
          ['connectivity', connectivity],
          ['ltype', ltype]
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

    const getMask = () => new cv.Mat([
      [cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD],
      [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
      [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
      [cv.GC_BGD, cv.GC_FGD, cv.GC_FGD, cv.GC_FGD, cv.GC_BGD],
      [cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD, cv.GC_BGD]
    ], cv.CV_8U);
    const getBgdModel = () => new cv.Mat(1, 65, cv.CV_64F, 0);
    const getFgdModel = () => new cv.Mat(1, 65, cv.CV_64F, 0);
    const iterCount = 4;

    describe('with mask', () => {
      const expectOutput = (res, dut, args) => {
        const bgdModel = args[2];
        const fgdModel = args[3];
        expect(isZeroMat(bgdModel)).to.be.false;
        expect(isZeroMat(fgdModel)).to.be.false;
      };
      const rect = new cv.Rect();
      const mode = cv.GC_INIT_WITH_MASK;

      generateAPITests({
        getDut: () => img,
        methodName: 'grabCut',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          getMask(),
          rect,
          getBgdModel(),
          getFgdModel(),
          iterCount
        ]),
        getOptionalArgs: () => ([
          mode
        ]),
        expectOutput
      });
    });

    describe('with rect', () => {
      const mask = getMask();
      const rect = new cv.Rect(1, 1, 3, 3);
      const bgdModel = getBgdModel();
      const fgdModel = getFgdModel();
      const mode = cv.GC_INIT_WITH_RECT;

      img.grabCut(mask, rect, bgdModel, fgdModel, iterCount, mode);
      expect(isZeroMat(mask)).to.be.false;
      expect(isZeroMat(bgdModel)).to.be.false;
      expect(isZeroMat(fgdModel)).to.be.false;
    });
  });

  describe('moments', () => {
    let grayImg;
    before(() => {
      grayImg = getTestImg().bgrToGray();
    });

    const isBinaryImg = true;
    generateAPITests({
      getDut: () => grayImg,
      methodName: 'moments',
      methodNameSpace: 'Mat',
      getOptionalArgs: () => ([
        isBinaryImg
      ]),
      expectOutput: res => expect(res).to.be.instanceOf(cv.Moments)
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

  describe('pyramid', () => {
    let img;
    let sizeDown;
    let sizeUp;
    before(() => {
      img = getTestImg();
      sizeDown = new cv.Size(img.cols / 2, img.rows / 2);
      sizeUp = new cv.Size(img.cols * 2, img.rows * 2);
    });

    describe('pyrDown', () => {
      generateAPITests({
        getDut: () => img,
        methodName: 'pyrDown',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgsMap: () => ([
          ['size', sizeDown],
          ['borderType', cv.BORDER_REFLECT]
        ]),
        expectOutput: outImg => assertMetaData(outImg)(sizeDown.height, sizeDown.width, cv.CV_8UC3)
      });
    });

    describe('pyrUp', () => {
      generateAPITests({
        getDut: () => img,
        methodName: 'pyrUp',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([]),
        getOptionalArgsMap: () => ([
          ['size', sizeUp],
          ['borderType', cv.BORDER_DEFAULT]
        ]),
        expectOutput: outImg => assertMetaData(outImg)(sizeUp.height, sizeUp.width, cv.CV_8UC3)
      });
    });

    describe('buildPyramid', () => {
      const expectOutput = (pyramid) => {
        expect(pyramid).to.be.an('array').lengthOf(4);
        pyramid.forEach((outImg, i) => {
          /* eslint-disable no-restricted-properties */
          const scale = 1 / Math.pow(2, i);
          expect(outImg).to.be.instanceOf(cv.Mat);
          assertMetaData(outImg)(img.rows * scale, img.cols * scale, cv.CV_8UC3);
        });
      };

      const maxlevel = 3;
      const borderType = cv.BORDER_REFLECT;
      generateAPITests({
        getDut: () => img,
        methodName: 'buildPyramid',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          maxlevel
        ]),
        getOptionalArgs: () => ([
          borderType
        ]),
        expectOutput
      });
    });
  });

  describe('hough', () => {
    let img;
    before(() => {
      img = getTestImg().rescale(0.25).bgrToGray();
    });

    const rho = 0.5;
    const theta = Math.PI / 4;
    const threshold = 100;

    describe('houghLines', () => {
      const expectOutput = (out) => {
        expect(out).to.be.an('array');
        expect(out.length).to.be.above(0);
        out.forEach((vec) => {
          expect(vec).to.have.property('x');
          expect(vec).to.have.property('y');
          expect(vec).to.not.have.property('z');
          expect(vec).to.not.have.property('w');
        });
      };

      generateAPITests({
        getDut: () => img,
        methodName: 'houghLines',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          rho,
          theta,
          threshold
        ]),
        getOptionalArgsMap: () => ([
          ['srn', 0.5],
          ['stn', 0.5],
          ['min_theta', 0],
          ['max_theta', Math.PI]
        ]),
        expectOutput
      });
    });

    describe('houghLinesP', () => {
      const expectOutput = (out) => {
        expect(out).to.be.an('array');
        expect(out.length).to.be.above(0);
        out.forEach((vec) => {
          expect(vec).to.have.property('x');
          expect(vec).to.have.property('y');
          expect(vec).to.have.property('z');
          expect(vec).to.have.property('w');
        });
      };

      generateAPITests({
        getDut: () => img,
        methodName: 'houghLinesP',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          rho,
          theta,
          threshold
        ]),
        getOptionalArgsMap: () => ([
          ['minLineLength', 0.5],
          ['maxLineGap', 0.5]
        ]),
        expectOutput
      });
    });

    describe('houghCircles', () => {
      const expectOutput = (out) => {
        expect(out).to.be.an('array');
        expect(out.length).to.be.above(0);
        out.forEach((vec) => {
          expect(vec).to.have.property('x');
          expect(vec).to.have.property('y');
          expect(vec).to.have.property('z');
          expect(vec).to.not.have.property('w');
        });
      };

      const method = cv.HOUGH_GRADIENT;
      const dp = 2;
      const minDist = 20;

      generateAPITests({
        getDut: () => img,
        methodName: 'houghCircles',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          method,
          dp,
          minDist
        ]),
        getOptionalArgsMap: () => ([
          ['param1', 50],
          ['param2', 50],
          ['minRadius', 4],
          ['maxRadius', 40]
        ]),
        expectOutput
      });
    });
  });
};
