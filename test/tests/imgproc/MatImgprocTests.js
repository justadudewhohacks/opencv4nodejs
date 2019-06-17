const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    generateAPITests,
    asyncFuncShouldRequireArgs,
    _funcShouldRequireArgs,
    assertMetaData,
    assertDataDeepEquals,
    assertMatValueEquals,
    dangerousDeepEquals,
    expectToBeVec2,
    isZeroMat,
    isUniformMat,
    cvVersionGreaterEqual
  } = utils;

  const rgbMatData = [
    Array(5).fill([255, 125, 0]),
    Array(5).fill([0, 0, 0]),
    Array(5).fill([125, 75, 125]),
    Array(5).fill([75, 255, 75])
  ];
  const rgbMat = new cv.Mat(rgbMatData, cv.CV_8UC3);

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
      const rows = 32;
      const cols = 8;
      const mat = new cv.Mat(16, 16, cv.CV_8UC3);

      const expectOutput = (res) => {
        assertMetaData(res)(rows, cols, cv.CV_8UC3);
      };

      describe('with rows and cols', () => {
        generateAPITests({
          getDut: () => mat,
          methodName: 'resize',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            rows,
            cols
          ]),
          getOptionalArgsMap: () => ([
            ['fx', 0.5],
            ['fy', 0.5],
            ['interpolation', cv.INTER_CUBIC]
          ]),
          expectOutput
        });
      });

      describe('with dsize', () => {
        generateAPITests({
          getDut: () => mat,
          methodName: 'resize',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            new cv.Size(cols, rows)
          ]),
          getOptionalArgsMap: () => ([
            ['fx', 0.5],
            ['fy', 0.5],
            ['interpolation', cv.INTER_CUBIC]
          ]),
          expectOutput
        });
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
      getDut: () => rgbMat.copy(),
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
      getDut: () => rgbMat.copy(),
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
        ['borderMode', cv.BORDER_CONSTANT],
        ['borderValue', new cv.Vec(255, 255, 255)]
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
        ['borderMode', cv.BORDER_CONSTANT],
        ['borderValue', new cv.Vec(255, 255, 255)]
      ]),
      expectOutput
    });
  });

  describe('drawing', () => {
    const getDut = () => new cv.Mat(10, 10, cv.CV_8UC3, [128, 128, 128]);

    const getDrawParams = () => ([
      ['color', new cv.Vec(255, 255, 255)],
      ['thickness', 2],
      ['lineType', cv.LINE_4],
      ['shift', 0]
    ]);

    const expectOutput = (_, dut) => {
      assertMetaData(getDut())(dut);
      expect(isUniformMat(dut, 128)).to.be.false;
    };

    describe('drawLine', () => {
      const ptFrom = new cv.Point(0, 0);
      const ptTo = new cv.Point(9, 9);

      generateAPITests({
        getDut,
        methodName: 'drawLine',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          ptFrom,
          ptTo
        ]),
        getOptionalArgsMap: getDrawParams,
        expectOutput,
        hasAsync: false
      });
    });

    describe('drawArrowedLine', () => {
      const ptFrom = new cv.Point(0, 0);
      const ptTo = new cv.Point(9, 9);
      const tipLength = 0.2;

      const getOptionalArgsMap = () => {
        const drawParams = getDrawParams();
        drawParams.push(['tipLength', tipLength]);
        return drawParams;
      };

      generateAPITests({
        getDut,
        methodName: 'drawArrowedLine',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          ptFrom,
          ptTo
        ]),
        getOptionalArgsMap,
        expectOutput,
        hasAsync: false
      });
    });

    describe('drawRectangle', () => {
      const upperLeft = new cv.Point(2, 2);
      const bottomRight = new cv.Point(8, 8);

      describe('with points', () => {
        generateAPITests({
          getDut,
          methodName: 'drawRectangle',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            upperLeft,
            bottomRight
          ]),
          getOptionalArgsMap: getDrawParams,
          expectOutput,
          hasAsync: false
        });
      });

      describe('with rect', () => {
        generateAPITests({
          getDut,
          methodName: 'drawRectangle',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            new cv.Rect(1, 1, 8, 8)
          ]),
          getOptionalArgsMap: getDrawParams,
          expectOutput,
          hasAsync: false
        });
      });
    });

    describe('drawCircle', () => {
      const center = new cv.Point(4, 4);
      const radius = 2;

      generateAPITests({
        getDut,
        methodName: 'drawCircle',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          center,
          radius
        ]),
        getOptionalArgsMap: getDrawParams,
        expectOutput,
        hasAsync: false
      });
    });

    describe('drawEllipse', () => {
      const center = new cv.Point(4, 4);
      const size = new cv.Size(4, 4);
      const angle = Math.PI / 4;

      describe('with rotated rect', () => {
        const box = new cv.RotatedRect(center, size, angle);
        generateAPITests({
          getDut,
          methodName: 'drawEllipse',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            box
          ]),
          getOptionalArgsMap: () => getDrawParams()
            // no shift
            .slice(0, 3),
          expectOutput,
          hasAsync: false
        });
      });

      describe('with center, axes and angles', () => {
        const startAngle = 0;
        const endAngle = 2 * angle;

        generateAPITests({
          getDut,
          methodName: 'drawEllipse',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            center,
            size,
            angle,
            startAngle,
            endAngle
          ]),
          getOptionalArgsMap: getDrawParams,
          expectOutput,
          hasAsync: false
        });
      });

      describe('drawPolylines', () => {
        const pts = [
          [new cv.Point(4, 4), new cv.Point(4, 8), new cv.Point(8, 8)],
          [new cv.Point(2, 2), new cv.Point(2, 6), new cv.Point(6, 6)]
        ];
        const isClosed = false;

        generateAPITests({
          getDut,
          methodName: 'drawPolylines',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            pts,
            isClosed
          ]),
          getOptionalArgsMap: getDrawParams,
          expectOutput,
          hasAsync: false
        });
      });

      describe('drawFillPoly', () => {
        const pts = [
          [new cv.Point(4, 4), new cv.Point(4, 8), new cv.Point(8, 8)],
          [new cv.Point(2, 2), new cv.Point(2, 6), new cv.Point(6, 6)]
        ];

        generateAPITests({
          getDut,
          methodName: 'drawFillPoly',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            pts
          ]),
          getOptionalArgsMap: () => ([
            ['color', new cv.Vec(255, 255, 255)],
            ['lineType', cv.LINE_4],
            ['shift', 0],
            ['offset', new cv.Point(0, 0)]
          ]),
          expectOutput,
          hasAsync: false
        });
      });

      describe('drawFillConvexPoly', () => {
        const pts = [new cv.Point(4, 4), new cv.Point(4, 8), new cv.Point(8, 8)];

        generateAPITests({
          getDut,
          methodName: 'drawFillConvexPoly',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            pts
          ]),
          getOptionalArgsMap: getDrawParams,
          expectOutput,
          hasAsync: false
        });
      });

      describe('putText', () => {
        const text = 'a';
        const origin = new cv.Point(0, 20);
        const fontFace = cv.FONT_ITALIC;
        const fontScale = 1.2;

        const getOptionalArgsMap = () => {
          const drawParams = getDrawParams();
          drawParams.push(['bottomLeftOrigin', false]);
          return drawParams;
        };

        generateAPITests({
          getDut,
          methodName: 'putText',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            text,
            origin,
            fontFace,
            fontScale
          ]),
          getOptionalArgsMap,
          expectOutput,
          hasAsync: false
        });
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
        getOptionalArg: () => dstType,
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
        getOptionalArg: () => distLabelType,
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
        getOptionalArg: () => mode,
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

  describe('watershed', () => {
    const markers = new cv.Mat([
      [0, 0, 0, 0, 0],
      [0, 2, 0, 0, 0],
      [0, 0, 0, 1, 0],
      [0, 0, 0, 0, 0]
    ], cv.CV_32S);

    generateAPITests({
      getDut: () => rgbMat.copy(),
      methodName: 'watershed',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        markers.copy()
      ]),
      expectOutput: (outMarkers) => {
        expect(outMarkers).to.be.instanceOf(cv.Mat);
        assertMetaData(markers)(outMarkers);
        expect(dangerousDeepEquals(markers.getDataAsArray(), outMarkers.getDataAsArray())).to.be.false;
      }
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
      getOptionalArg: () => isBinaryImg,
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
        getOptionalArg: () => borderType,
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
          expectToBeVec2(vec);
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

  describe('equalizeHist', () => {
    let img;
    before(() => {
      img = getTestImg().rescale(0.25).bgrToGray();
    });

    const expectOutput = (out) => {
      expect(out).to.be.instanceOf(cv.Mat);
      assertMetaData(img)(out);
    };


    generateAPITests({
      getDut: () => img,
      methodName: 'equalizeHist',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('compareHist', () => {
    const expectOutput = (out) => {
      expect(out).to.be.a('number').above(0);
    };

    const method = cv.HISTCMP_CHISQR_ALT;

    const H1 = new cv.Mat(1, 8, cv.CV_32FC3, [0.5, 0.5, 0.5]);
    const H2 = new cv.Mat(1, 8, cv.CV_32FC3, [0.75, 0.75, 0.75]);
    generateAPITests({
      getDut: () => H1,
      methodName: 'compareHist',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        H2,
        method
      ]),
      expectOutput
    });
  });

  describe('floodFill', () => {
    const expectOutput = (out) => {
      expect(!!out).to.be.true;
      expect(out).to.have.property('returnValue').to.be.a('number');
      expect(out).to.have.property('rect').to.be.instanceOf(cv.Rect);
    };

    const seedPoint = new cv.Point(50, 50);
    const mask = new cv.Mat(102, 102, cv.CV_8U, 255);
    const flags = 4;

    describe('C1', () => {
      const newVal = 155;
      generateAPITests({
        getDut: () => new cv.Mat(100, 100, cv.CV_8UC1),
        methodName: 'floodFill',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          seedPoint,
          newVal
        ]),
        getOptionalArgsMap: () => ([
          ['mask', mask],
          ['loDiff', 100],
          ['upDiff', 255],
          ['flags', flags]
        ]),
        expectOutput
      });
    });

    describe('C3', () => {
      const newVal = new cv.Vec(155, 155, 155);
      generateAPITests({
        getDut: () => new cv.Mat(100, 100, cv.CV_8UC3),
        methodName: 'floodFill',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          seedPoint,
          newVal
        ]),
        getOptionalArgsMap: () => ([
          ['mask', mask],
          ['loDiff', new cv.Vec(100, 100, 100)],
          ['upDiff', new cv.Vec(255, 255, 255)],
          ['flags', flags]
        ]),
        expectOutput
      });
    });
  });

  describe('filters', () => {
    const expectOutput = (res) => {
      assertMetaData(res)(100, 100, cv.CV_32F);
    };

    const getDut = () => new cv.Mat(100, 100, cv.CV_8U);
    const ddepth = cv.CV_32F;
    const anchor = new cv.Point(0, 0);
    const borderType = cv.BORDER_CONSTANT;

    describe('bilateralFilter', () => {
      const d = 3;
      const sigmaColor = 0.5;
      const sigmaSpace = 0.5;
      generateAPITests({
        getDut,
        methodName: 'bilateralFilter',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          d,
          sigmaColor,
          sigmaSpace
        ]),
        getOptionalArg: () => borderType,
        expectOutput: (res) => {
          assertMetaData(res)(100, 100, cv.CV_8U);
        }
      });
    });

    describe('boxFilters', () => {
      const normalize = false;
      const kSize = new cv.Size(3, 3);
      const getRequiredArgs = () => ([
        ddepth,
        kSize
      ]);
      const getOptionalArgsMap = () => ([
        ['anchor', anchor],
        ['normalize', normalize],
        ['borderType', cv.BORDER_CONSTANT]
      ]);

      describe('boxFilter', () => {
        generateAPITests({
          getDut,
          methodName: 'boxFilter',
          methodNameSpace: 'Mat',
          getRequiredArgs,
          getOptionalArgsMap,
          expectOutput
        });
      });

      describe('sqrBoxFilter', () => {
        generateAPITests({
          getDut,
          methodName: 'sqrBoxFilter',
          methodNameSpace: 'Mat',
          getRequiredArgs,
          getOptionalArgsMap,
          expectOutput
        });
      });
    });

    describe('filter2D', () => {
      const getOptionalArgsMap = () => ([
        ['anchor', anchor],
        ['delta', 0.5],
        ['borderType', cv.BORDER_CONSTANT]
      ]);

      describe('filter2D', () => {
        const kernel = cv.Mat.eye(3, 3, cv.CV_8U);
        generateAPITests({
          getDut,
          methodName: 'filter2D',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            ddepth,
            kernel
          ]),
          getOptionalArgsMap,
          expectOutput
        });
      });

      describe('sepFilter2D', () => {
        const kernelX = new cv.Mat(3, 1, cv.CV_8U, 255);
        const kernelY = new cv.Mat(3, 1, cv.CV_8U, 255);
        generateAPITests({
          getDut,
          methodName: 'sepFilter2D',
          methodNameSpace: 'Mat',
          getRequiredArgs: () => ([
            ddepth,
            kernelX,
            kernelY
          ]),
          getOptionalArgsMap,
          expectOutput
        });
      });
    });
  });

  describe('corner detection', () => {
    const getDut = () => getTestImg().bgrToGray();
    const makeExpectOutput = expectedType => (out) => {
      expect(out).to.be.instanceOf(cv.Mat);
      const { cols, rows } = getTestImg();
      assertMetaData(out)(cols, rows, expectedType);
    };

    const blockSize = 4;
    const borderType = cv.BORDER_CONSTANT;

    describe('cornerHarris', () => {
      const ksize = 3;
      const k = 0.04;
      generateAPITests({
        getDut,
        methodName: 'cornerHarris',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          blockSize,
          ksize,
          k
        ]),
        getOptionalArg: () => borderType,
        expectOutput: makeExpectOutput(cv.CV_32F)
      });
    });

    describe('cornerSubPix', () => {
      const corners = [new cv.Point(10, 10), new cv.Point(100, 100), new cv.Point(50, 50)];
      const winSize = new cv.Size(5, 5);
      const zeroZone = new cv.Size(-1, -1);
      const criteria = new cv.TermCriteria(cv.termCriteria.EPS + cv.termCriteria.MAX_ITER, 40, 0.001);
      generateAPITests({
        getDut,
        methodName: 'cornerSubPix',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          corners,
          winSize,
          zeroZone,
          criteria
        ]),
        expectOutput: (adjustedCorners) => {
          expect(adjustedCorners).to.be.an('array').lengthOf(corners.length);
        }
      });
    });

    describe('cornerMinEigenVal', () => {
      generateAPITests({
        getDut,
        methodName: 'cornerMinEigenVal',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          blockSize
        ]),
        getOptionalArgsMap: () => ([
          ['ksize', 5],
          ['borderType', borderType]
        ]),
        expectOutput: makeExpectOutput(cv.CV_32F)
      });
    });

    describe('cornerEigenValsAndVecs', () => {
      const cv32fc6 = 45;
      generateAPITests({
        getDut,
        methodName: 'cornerEigenValsAndVecs',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          blockSize
        ]),
        getOptionalArgsMap: () => ([
          ['ksize', 5],
          ['borderType', borderType]
        ]),
        expectOutput: makeExpectOutput(cv32fc6)
      });
    });

    describe('integral', () => {
      generateAPITests({
        getDut: () => new cv.Mat(20, 20, cv.CV_32F, 0.5),
        methodName: 'integral',
        methodNameSpace: 'Mat',
        getOptionalArgsMap: () => ([
          ['sdepth', cv.CV_64F],
          ['sqdepth', cv.CV_64F]
        ]),
        expectOutput: (res) => {
          expect(res).to.have.property('sum').to.be.instanceOf(cv.Mat);
          expect(res).to.have.property('sqsum').to.be.instanceOf(cv.Mat);
          expect(res).to.have.property('tilted').to.be.instanceOf(cv.Mat);
        }
      });
    });
  });

  describe('inRange', () => {
    const expectOutput = (inRangeMat) => {
      assertMetaData(inRangeMat)(2, 3, cv.CV_8U);
      assertDataDeepEquals(
        [
          [255, 255, 255],
          [0, 0, 255]
        ],
        inRangeMat.getDataAsArray()
      );
    };

    describe('C1', () => {
      const mat = new cv.Mat([
        [255, 255, 255],
        [0, 100, 101]
      ], cv.CV_8U);

      const lower = 101;
      const upper = 255;

      generateAPITests({
        getDut: () => mat,
        methodName: 'inRange',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          lower,
          upper
        ]),
        expectOutput
      });
    });

    describe('C3', () => {
      const mat = new cv.Mat([
        [[255, 255, 255], [255, 255, 255], [255, 255, 255]],
        [[0, 0, 0], [100, 100, 100], [101, 101, 101]]
      ], cv.CV_8UC3);

      const lower = new cv.Vec(101, 101, 101);
      const upper = new cv.Vec(255, 255, 255);

      generateAPITests({
        getDut: () => mat,
        methodName: 'inRange',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          lower,
          upper
        ]),
        expectOutput
      });
    });
  });

  if (!cvVersionGreaterEqual(4, 0, 0)) {
    describe('undistort', () => {
      const cameraMatrix = new cv.Mat([[1, 0, 10],[0, 1, 10],[0, 0, 1]], cv.CV_32F);
      const distCoeffs = new cv.Mat([[0.1, 0.1, 1, 1]], cv.CV_32F);
      generateAPITests({
        getDut: () => new cv.Mat(20, 20, cv.CV_8U, 0.5),
        methodName: 'undistort',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([cameraMatrix, distCoeffs]),
        expectOutput: (res, _, args) => {
          expect(res).to.be.instanceOf(cv.Mat);
        }
      });
    });
  }
};
