const { assert, expect } = require('chai');

module.exports = ({ cv, utils }) => {

  const {
    assertPropsWithValue,
    assertMetaData,
    funcShouldRequireArgs,
    generateAPITests,
    expectToBeVec3,
    cvVersionGreaterEqual
  } = utils;

  const objectPoints = [
    new cv.Point(0, 0, 0),
    new cv.Point(0.5, 0.5, 0.5),
    new cv.Point(1.0, 1.0, 1.0),
    new cv.Point(1.0, 0.5, 0),
    new cv.Point(100, 100, 100),
    new cv.Point(100.5, 100.5, 100.5),
    new cv.Point(101.0, 101.0, 101.0),
    new cv.Point(101.0, 100.5, 100)
  ];
  const imagePoints = [
    new cv.Point(0, 0),
    new cv.Point(0.5, 0.5),
    new cv.Point(1.0, 1.0),
    new cv.Point(1.0, 0.5),
    new cv.Point(100, 100),
    new cv.Point(100.5, 100.5),
    new cv.Point(101.0, 101.0),
    new cv.Point(101.0, 100.5)
  ];
  const distCoefficients = [0, 0.5, 1.0, 1.0];

  describe('findHomography', () => {
    const srcPointsJson = [{ x: 100, y: 100 }, { x: 100, y: -100 }, { x: -100, y: 100 }, { x: -100, y: -100 }];
    const srcPoints = srcPointsJson.map(pt => new cv.Point(pt.x, pt.y))
    const dstPoints = srcPointsJson.map(srcPt => new cv.Point(srcPt.x * 2, srcPt.y * 2));
    const method = cv.RANSAC;
    const ransacReprojThreshold = 2.5;
		const maxIters = 1000;
    const confidence = 0.9;


    const expectOutput = (res) => {
      assertPropsWithValue(res.homography)({ type: cv.CV_64F, rows: 3, cols: 3 });
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'findHomography',
      getRequiredArgs: () => ([
        srcPoints,
        dstPoints
      ]),
      getOptionalParamsMap: () => ([
        ['method', method],
        ['ransacReprojThreshold', ransacReprojThreshold],
        ['maxIters', maxIters],
        ['confidence', confidence]
      ]),
      expectOutput
    });
  });

  describe('composeRT', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('rvec3');
      expectToBeVec3(res.rvec3);
      expect(res).to.have.property('tvec3');
      expectToBeVec3(res.tvec3);
      ['dr3dr1', 'dr3dt1', 'dr3dr2', 'dr3dt2', 'dt3dr1', 'dt3dt1', 'dt3dr2', 'dt3dt2']
        .forEach((prop) => {
          expect(res).to.have.property(prop);
          expect(res[prop]).to.be.instanceOf(cv.Mat);
          assertMetaData(res[prop])(3, 3, cv.CV_64F);
        });
    };

    const rvec1 = new cv.Vec(0.5, 0, 0);
    const tvec1 = new cv.Vec(0.5, 0.5, 0.5);
    const rvec2 = new cv.Vec(0, 0.5, 0);
    const tvec2 = new cv.Vec(0.5, 0.5, 0.5);

    generateAPITests({
      getDut: () => cv,
      methodName: 'composeRT',
      getRequiredArgs: () => ([
        rvec1,
        tvec1,
        rvec2,
        tvec2
      ]),
      expectOutput
    });
  });

  describe('solvePxP', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('Boolean');
      expect(res).to.have.property('rvec');
      expectToBeVec3(res.rvec);
      expect(res).to.have.property('tvec');
      expectToBeVec3(res.tvec);
    };

    const getRequiredArgs = () => ([
      objectPoints,
      imagePoints,
      cv.Mat.eye(3, 3, cv.CV_64F),
      distCoefficients
    ]);

    describe('solvePnP', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'solvePnP',
        getRequiredArgs,
        getOptionalParamsMap: () => ([
          ['useExtrinsicGuess', true],
          ['flags', cv.SOLVEPNP_DLS]
        ]),
        expectOutput
      });
    });

    describe('solvePnPRansac', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'solvePnPRansac',
        getRequiredArgs,
        getOptionalParamsMap: () => ([
          ['useExtrinsicGuess', true],
          ['iterationsCount', 200],
          ['reprojectionError', 16.0],
          ['confidence', 0.9],
          ['flags', cv.SOLVEPNP_DLS]
        ]),
        expectOutput: (res) => {
          expectOutput(res);
          expect(res).to.have.property('inliers').to.be.an('array');
        }
      });
    });

    (cvVersionGreaterEqual(3, 3, 0) ? describe : describe.skip)('solveP3P', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'solveP3P',
        getRequiredArgs: () => ([
          objectPoints.slice(0, 3),
          imagePoints.slice(0, 3),
          cv.Mat.eye(3, 3, cv.CV_64F),
          distCoefficients
        ]),
        getOptionalParams: () => ([
          cv.SOLVEPNP_DLS
        ]),
        expectOutput: (res) => {
          expect(res).to.have.property('returnValue').to.be.a('Boolean');
          expect(res).to.have.property('rvecs').to.be.an('array');
          expect(res.rvecs.length).to.be.above(0);
          res.rvecs.forEach((vec) => {
            expect(vec).to.be.instanceOf(cv.Mat);
            assertMetaData(vec)(3, 1, cv.CV_64F);
          });
          expect(res).to.have.property('tvecs').to.be.an('array');
          expect(res.tvecs.length).to.be.above(0);
          res.tvecs.forEach((vec) => {
            expect(vec).to.be.instanceOf(cv.Mat);
            assertMetaData(vec)(3, 1, cv.CV_64F);
          });
        }
      });
    });
  });

  describe('projectPoints', () => {
    const rvec = new cv.Vec(1, 0, 0);
    const tvec = new cv.Vec(1, 1, 1);
    const aspectRatio = 1;
    generateAPITests({
      getDut: () => cv,
      methodName: 'projectPoints',
      getRequiredArgs: () => [
        objectPoints,
        rvec,
        tvec,
        cv.Mat.eye(3, 3, cv.CV_64F),
        distCoefficients
      ],
      getOptionalParams: () => ([
        aspectRatio
      ]),
      expectOutput: (res) => {
        expect(res).to.have.property('imagePoints').to.be.an('array').lengthOf(imagePoints.length);
        expect(res).to.have.property('jacobian').to.be.instanceOf(cv.Mat);
        assertMetaData(res.jacobian)(16, 14, cv.CV_64F);
      }
    });
  });

  describe('initCameraMatrix2D', () => {
    const imageSize = new cv.Size(200, 200);
    const aspectRatio = 1;
    generateAPITests({
      getDut: () => cv,
      methodName: 'initCameraMatrix2D',
      getRequiredArgs: () => [
        [objectPoints, objectPoints],
        [imagePoints, imagePoints],
        imageSize
      ],
      getOptionalParams: () => ([
        aspectRatio
      ]),
      expectOutput: (res) => {
        expect(res).to.be.instanceOf(cv.Mat);
        assertMetaData(res)(3, 3, cv.CV_64F);
      }
    });
  });

  describe('calibrateCamera', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('Number');
      expect(res).to.have.property('rvecs').to.be.an('array').lengthOf(2);
      res.rvecs.forEach(vec => expectToBeVec3(vec));
      expect(res).to.have.property('tvecs').to.be.an('array').lengthOf(2);
      res.tvecs.forEach(vec => expectToBeVec3(vec));
      expect(res).to.have.property('distCoeffs').to.be.an('array');
    };
    const _cameraMatrix = new cv.Mat([
      [800, 0, 100],
      [0, 800, 100],
      [0, 0, 1]
    ], cv.CV_64F);
    const imageSize = new cv.Size(200, 200);
    // non-planar calibration expects z coordinates to be 0
    const _objectPoints = objectPoints.map(pt => new cv.Point(pt.x, pt.y, 0));

    const getRequiredArgs = () => [
      [_objectPoints, _objectPoints],
      [imagePoints, imagePoints],
      imageSize,
      _cameraMatrix,
      distCoefficients
    ];
    const getOptionalParamsMap = () => ([
      ['flags', cv.CV_CALIB_USE_INTRINSIC_GUESS],
      ['termCriteria', new cv.TermCriteria()]
    ]);

    (cvVersionGreaterEqual(3, 1, 0) ? describe : describe.skip)('calibrateCamera', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'calibrateCamera',
        getRequiredArgs,
        getOptionalParamsMap,
        expectOutput
      });
    });

    (cvVersionGreaterEqual(3, 2, 0) ? describe : describe.skip)('calibrateCameraExtended', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'calibrateCameraExtended',
        getRequiredArgs,
        getOptionalParamsMap,
        expectOutput: (res) => {
          expectOutput(res);
          expect(res).to.have.property('stdDeviationsIntrinsics').to.be.instanceOf(cv.Mat);
          assertMetaData(res.stdDeviationsIntrinsics)(18, 1, cv.CV_64F);
          expect(res).to.have.property('stdDeviationsExtrinsics').to.be.instanceOf(cv.Mat);
          assertMetaData(res.stdDeviationsExtrinsics)(12, 1, cv.CV_64F);
          expect(res).to.have.property('perViewErrors').to.be.an('array').lengthOf(2);
        }
      });
    });
  });

  describe('stereoCalibrate', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('Number');
      expect(res).to.have.property('R').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R)(3, 3, cv.CV_64F);
      expect(res).to.have.property('T');
      expectToBeVec3(res.T);
      expect(res).to.have.property('E').to.be.instanceOf(cv.Mat);
      assertMetaData(res.E)(3, 3, cv.CV_64F);
      expect(res).to.have.property('F').to.be.instanceOf(cv.Mat);
      assertMetaData(res.F)(3, 3, cv.CV_64F);
      expect(res).to.have.property('distCoeffs1').to.be.an('array');
      expect(res).to.have.property('distCoeffs2').to.be.an('array');
    };

    const imageSize = new cv.Size(200, 200);

    generateAPITests({
      getDut: () => cv,
      methodName: 'stereoCalibrate',
      getRequiredArgs: () => [
        [objectPoints, objectPoints],
        [imagePoints, imagePoints],
        [imagePoints, imagePoints],
        cv.Mat.eye(3, 3, cv.CV_64F),
        distCoefficients,
        cv.Mat.eye(3, 3, cv.CV_64F),
        distCoefficients,
        imageSize
      ],
      getOptionalParamsMap: () => ([
        ['flags', cv.CV_CALIB_USE_INTRINSIC_GUESS],
        ['termCriteria', new cv.TermCriteria()]
      ]),
      expectOutput
    });
  });

  describe('stereoRectifyUncalibrated', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('Boolean');
      expect(res).to.have.property('H1').to.be.instanceOf(cv.Mat);
      assertMetaData(res.H1)(3, 3, cv.CV_64F);
      expect(res).to.have.property('H2').to.be.instanceOf(cv.Mat);
      assertMetaData(res.H2)(3, 3, cv.CV_64F);
    };

    const F = cv.Mat.eye(3, 3, cv.CV_64F);
    const imageSize = new cv.Size(200, 200);
    const threshold = 10;

    generateAPITests({
      getDut: () => cv,
      methodName: 'stereoRectifyUncalibrated',
      getRequiredArgs: () => [
        imagePoints,
        imagePoints,
        F,
        imageSize
      ],
      getOptionalParams: () => ([
        threshold
      ]),
      expectOutput
    });
  });

  describe('findFundamentalMat', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('F').to.be.instanceOf(cv.Mat);
      assertMetaData(res.F)(3, 3, cv.CV_64F);
      expect(res).to.have.property('mask').to.be.instanceOf(cv.Mat);
      assertMetaData(res.mask)(8, 1, cv.CV_8U);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'findFundamentalMat',
      getRequiredArgs: () => [
        imagePoints,
        imagePoints
      ],
      getOptionalParamsMap: () => ([
        ['method', cv.FM_LMEDS],
        ['param1', 1.0],
        ['param2', 0.9]
      ]),
      expectOutput
    });
  });

  describe('findEssentialMat', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('E').to.be.instanceOf(cv.Mat);
      assertMetaData(res.E)(3, 3, cv.CV_64F);
      expect(res).to.have.property('mask').to.be.instanceOf(cv.Mat);
      assertMetaData(res.mask)(8, 1, cv.CV_8U);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'findEssentialMat',
      getRequiredArgs: () => [
        imagePoints,
        imagePoints
      ],
      getOptionalParamsMap: () => ([
        ['focal', 800.0],
        ['pp', new cv.Point(100, 100)],
        ['method', cv.LMEDS],
        ['prob', 0.9],
        ['threshold', 2.0]
      ]),
      expectOutput
    });
  });

  describe('recoverPose', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('Number');
      expect(res).to.have.property('R').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R)(3, 3, cv.CV_64F);
      expect(res).to.have.property('T');
      expectToBeVec3(res.T);
    };

    const E = cv.Mat.eye(3, 3, cv.CV_64F);
    const mask = new cv.Mat(imagePoints.length, 1, cv.CV_8U, 255);

    generateAPITests({
      getDut: () => cv,
      methodName: 'recoverPose',
      getRequiredArgs: () => [
        E,
        imagePoints,
        imagePoints
      ],
      getOptionalParamsMap: () => ([
        ['focal', 800.0],
        ['pp', new cv.Point(100, 100)],
        ['mask', mask]
      ]),
      expectOutput
    });
  });

  describe('computeCorrespondEpilines', () => {
    const expectOutput = (res) => {
      expect(res).to.be.an('array').lengthOf(imagePoints.length);
      res.forEach(vec => expectToBeVec3(vec));
    };

    const whichImg = 0;
    const F = cv.Mat.eye(3, 3, cv.CV_64F);

    generateAPITests({
      getDut: () => cv,
      methodName: 'computeCorrespondEpilines',
      getRequiredArgs: () => [
        imagePoints,
        whichImg,
        F
      ],
      expectOutput
    });
  });

  describe('getValidDisparityROI', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Rect);
      expect(res.height).to.not.equals(0);
      expect(res.width).to.not.equals(0);
      expect(res.x).to.not.equals(0);
      expect(res.y).to.not.equals(0);
    };

    const roi1 = new cv.Rect(0, 0, 200, 200);
    const roi2 = new cv.Rect(0, 0, 200, 200);
    const minDisparity = 0;
    const numberOfDisparities = 10;
    const SADWindowSize = 5;

    generateAPITests({
      getDut: () => cv,
      methodName: 'getValidDisparityROI',
      getRequiredArgs: () => [
        roi1,
        roi2,
        minDisparity,
        numberOfDisparities,
        SADWindowSize
      ],
      expectOutput
    });
  });

  describe('estimateAffine3D', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('number');
      expect(res).to.have.property('out').to.be.instanceOf(cv.Mat);
      assertMetaData(res.out)(3, 4, cv.CV_64F);
      expect(res).to.have.property('inliers').to.be.instanceOf(cv.Mat);
      assertMetaData(res.inliers)(objectPoints.length, 1, cv.CV_8U);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'estimateAffine3D',
      getRequiredArgs: () => [
        objectPoints,
        objectPoints
      ],
      getOptionalParamsMap: () => ([
        ['ransacThreshold', 1.0],
        ['param2', 0.9]
      ]),
      expectOutput
    });
  });

  (cvVersionGreaterEqual(3, 1, 0) ? describe : describe.skip)('sampsonDistance', () => {
    const pt1 = new cv.Vec(0.5, 0.5);
    const pt2 = new cv.Vec(100.5, 100.5);
    const F = cv.Mat.eye(3, 3, cv.CV_64F);

    generateAPITests({
      getDut: () => cv,
      methodName: 'sampsonDistance',
      getRequiredArgs: () => [
        pt1,
        pt2,
        F
      ],
      expectOutput: res => expect(res).to.be.a('number').to.be.above(0)
    });
  });

  (cvVersionGreaterEqual(3, 2, 0) ? describe : describe.skip)('estimateAffine2D', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('out').to.be.instanceOf(cv.Mat);
      assertMetaData(res.out)(2, 3, cv.CV_64F);
      expect(res).to.have.property('inliers').to.be.instanceOf(cv.Mat);
      assertMetaData(res.inliers)(objectPoints.length, 1, cv.CV_8U);
    };

    const getRequiredArgs = () => ([
      imagePoints,
      imagePoints
    ]);
    const getOptionalParamsMap = () => ([
        ['method', cv.LMEDS],
        ['ransacReprojThreshold', 1.0],
        ['maxIters', 1000],
        ['confidence', 0.9],
        ['refineIters', 20]
    ]);

    describe('estimateAffine2D', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'estimateAffine2D',
        getRequiredArgs,
        getOptionalParamsMap,
        expectOutput
      });
    });

    describe('estimateAffinePartial2D', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'estimateAffinePartial2D',
        getRequiredArgs,
        getOptionalParamsMap,
        expectOutput
      });
    });
  });


  if (cvVersionGreaterEqual(4, 0, 0)) {
    describe('undistortPoints', () => {
      const cameraMatrix = new cv.Mat([[1, 0, 10],[0, 1, 10],[0, 0, 1]], cv.CV_32F);
      //const newCameraMatrix = new cv.Mat([[0.5, 0, 10],[0, 0.5, 10],[0, 0, 1]], cv.CV_32F);
      const distCoeffs = new cv.Mat([[0.1, 0.1, 1, 1]], cv.CV_32F);
      const srcPoints = [
        [5,5], [5, 10], [5, 15]
      ].map(p => new cv.Point(p[0], p[1]));
      const expectedDestPoints = [
        [9.522233963012695, 9.522233963012695],
        [9.128815650939941, 9.661333084106445],
        [9.76507568359375, 9.841306686401367]
      ].map(p => new cv.Point(p[0], p[1]));

      generateAPITests({
        getDut: () => cv,
        methodName: 'undistortPoints',
        getRequiredArgs: () => ([
          srcPoints,
          cameraMatrix,
          distCoeffs
        ]),
        expectOutput: destPoints => {
          expect(destPoints.length).to.equal(expectedDestPoints.length);
          for(var i = 0; i < destPoints.length; i++){
            expect(destPoints[i].x).to.be.closeTo(expectedDestPoints[i].x, 0.001)
            expect(destPoints[i].y).to.be.closeTo(expectedDestPoints[i].y, 0.001)
          }
        }
      });
    });
  };

};
