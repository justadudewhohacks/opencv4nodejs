const { expect } = require('chai');

module.exports = ({ cv, utils }) => {

  const {
    assertMetaData,
    generateAPITests,
    expectToBeVec2,
    expectToBeVec3,
    expectToBeVec4,
    cvVersionLowerThan,
    cvVersionGreaterEqual
  } = utils;

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

  describe('rodrigues', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('dst').to.be.instanceOf(cv.Mat);
      assertMetaData(res.dst)(3, 1, cv.CV_64F);
      expect(res).to.have.property('jacobian').to.be.instanceOf(cv.Mat);
      assertMetaData(res.jacobian)(9, 3, cv.CV_64F);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'rodrigues',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('rqDecomp3x3', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue');
      expectToBeVec3(res.returnValue);
      expect(res).to.have.property('mtxR').to.be.instanceOf(cv.Mat);
      assertMetaData(res.mtxR)(3, 3, cv.CV_64F);
      expect(res).to.have.property('mtxQ').to.be.instanceOf(cv.Mat);
      assertMetaData(res.mtxQ)(3, 3, cv.CV_64F);
      expect(res).to.have.property('Qx').to.be.instanceOf(cv.Mat);
      assertMetaData(res.Qx)(3, 3, cv.CV_64F);
      expect(res).to.have.property('Qy').to.be.instanceOf(cv.Mat);
      assertMetaData(res.Qy)(3, 3, cv.CV_64F);
      expect(res).to.have.property('Qz').to.be.instanceOf(cv.Mat);
      assertMetaData(res.Qz)(3, 3, cv.CV_64F);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'rqDecomp3x3',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('decomposeProjectionMatrix', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('cameraMatrix').to.be.instanceOf(cv.Mat);
      assertMetaData(res.cameraMatrix)(3, 3, cv.CV_64F);
      expect(res).to.have.property('rotMatrix').to.be.instanceOf(cv.Mat);
      assertMetaData(res.rotMatrix)(3, 3, cv.CV_64F);
      expect(res).to.have.property('transVect');
      expectToBeVec4(res.transVect);
      expect(res).to.have.property('rotMatrixX').to.be.instanceOf(cv.Mat);
      assertMetaData(res.rotMatrixX)(3, 3, cv.CV_64F);
      expect(res).to.have.property('rotMatrixY').to.be.instanceOf(cv.Mat);
      assertMetaData(res.rotMatrixY)(3, 3, cv.CV_64F);
      expect(res).to.have.property('rotMatrixZ').to.be.instanceOf(cv.Mat);
      assertMetaData(res.rotMatrixZ)(3, 3, cv.CV_64F);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 4, cv.CV_64F),
      methodName: 'decomposeProjectionMatrix',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('matMulDeriv', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('dABdA').to.be.instanceOf(cv.Mat);
      assertMetaData(res.dABdA)(9, 9, cv.CV_64F);
      expect(res).to.have.property('dABdB').to.be.instanceOf(cv.Mat);
      assertMetaData(res.dABdB)(9, 9, cv.CV_64F);
    };

    const B = cv.Mat.eye(3, 3, cv.CV_64F);

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'matMulDeriv',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        B
      ]),
      expectOutput
    });
  });

  describe('findChessboardCorners', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('boolean');
      expect(res).to.have.property('corners').to.be.an('array');
    };

    const patternSize = new cv.Size(100, 100);
    const flags = cv.CALIB_CB_ADAPTIVE_THRESH + cv.CALIB_CB_NORMALIZE_IMAGE;
    generateAPITests({
      getDut: () => new cv.Mat(200, 200, cv.CV_8UC3),
      methodName: 'findChessboardCorners',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        patternSize
      ]),
      getOptionalArg: () => flags,
      expectOutput
    });
  });

  describe('drawChessboardCorners', () => {
    const expectOutput = () => {
      // expect not to throw
    };

    const patternSize = new cv.Size(2, 2);
    const corners = [
      new cv.Point(50, 50),
      new cv.Point(50, 100),
      new cv.Point(100, 50),
      new cv.Point(100, 100)
    ];
    const patternWasFound = true;

    generateAPITests({
      getDut: () => new cv.Mat(200, 200, cv.CV_8U, 0),
      methodName: 'drawChessboardCorners',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        patternSize,
        corners,
        patternWasFound
      ]),
      expectOutput
    });
  });

  describe('find4QuadCornerSubpix', () => {
    const img = new cv.Mat(200, 200, cv.CV_8U, 0);
    const expectOutput = () => {
      // expect not to throw
    };

    const regionSize = new cv.Size(2, 2);
    const corners = [
      new cv.Point(50, 50),
      new cv.Point(50, 100),
      new cv.Point(100, 50),
      new cv.Point(100, 100)
    ];

    generateAPITests({
      getDut: () => img,
      methodName: 'find4QuadCornerSubpix',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        corners,
        regionSize
      ]),
      expectOutput
    });
  });

  describe('calibrationMatrixValues', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('fovx').to.be.a('number').above(0);
      expect(res).to.have.property('fovy').to.be.a('number').above(0);
      expect(res).to.have.property('focalLength').to.be.a('number').above(0);
      expect(res).to.have.property('principalPoint');
      expectToBeVec2(res.principalPoint);
      expect(res).to.have.property('aspectRatio').to.be.a('number').above(0);
    };

    const imageSize = new cv.Size(200, 200);
    const apertureWidth = 10;
    const apertureHeight = 10;

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'calibrationMatrixValues',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        imageSize,
        apertureWidth,
        apertureHeight
      ]),
      expectOutput
    });
  });

  describe('rectify', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('R1').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R1)(3, 3, cv.CV_64F);
      expect(res).to.have.property('R2').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R2)(3, 3, cv.CV_64F);
      expect(res).to.have.property('P1').to.be.instanceOf(cv.Mat);
      assertMetaData(res.P1)(3, 4, cv.CV_64F);
      expect(res).to.have.property('P2').to.be.instanceOf(cv.Mat);
      assertMetaData(res.P2)(3, 4, cv.CV_64F);
      expect(res).to.have.property('Q').to.be.instanceOf(cv.Mat);
      assertMetaData(res.Q)(4, 4, cv.CV_64F);
      expect(res).to.have.property('roi1').to.be.instanceOf(cv.Rect);
      expect(res).to.have.property('roi2').to.be.instanceOf(cv.Rect);
    };

    const imageSize = new cv.Size(200, 200);
    const R = cv.Mat.eye(3, 3, cv.CV_64F);
    const T = new cv.Vec(1, 1, 1);

    describe('stereoRectify', () => {
      generateAPITests({
        getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
        methodName: 'stereoRectify',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distCoefficients,
          cv.Mat.eye(3, 3, cv.CV_64F),
          distCoefficients,
          imageSize,
          R,
          T
        ]),
        getOptionalParamsMap: () => ([
          ['flags', cv.CALIB_ZERO_DISPARITY],
          ['alpha', 0],
          ['newImageSize', imageSize]
        ]),
        expectOutput
      });
    });

    // TODO: figure out why rectify3Collinear is failing with docker and 3.4.3+
    ((!process.env.DOCKER_BUILD && !process.env.BINDINGS_DEBUG && cvVersionLowerThan(3, 3, 0)) ? describe : describe.skip)('rectify3Collinear', () => {
      const alpha = 0;
      const flags = cv.CALIB_ZERO_DISPARITY;

      generateAPITests({
        getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
        methodName: 'rectify3Collinear',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distCoefficients,
          cv.Mat.eye(3, 3, cv.CV_64F),
          distCoefficients,
          cv.Mat.eye(3, 3, cv.CV_64F),
          distCoefficients,
          imagePoints,
          imagePoints,
          imageSize,
          R,
          T,
          R,
          T,
          alpha,
          imageSize,
          flags
        ]),
        expectOutput: (res) => {
          expectOutput(res);
          expect(res).to.have.property('returnValue').to.be.a('number');
          expect(res).to.have.property('R3').to.be.instanceOf(cv.Mat);
          assertMetaData(res.R3)(3, 3, cv.CV_64F);
          expect(res).to.have.property('P3').to.be.instanceOf(cv.Mat);
          assertMetaData(res.P3)(3, 4, cv.CV_64F);
        }
      });
    });
  });

  describe('getOptimalNewCameraMatrix', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('out').to.be.instanceOf(cv.Mat);
      assertMetaData(res.out)(3, 3, cv.CV_64F);
      expect(res).to.have.property('validPixROI').to.be.instanceOf(cv.Rect);
    };

    const imageSize = new cv.Size(200, 200);
    const alpha = 0;
    const centerPrincipalPoint = true;

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'getOptimalNewCameraMatrix',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        distCoefficients,
        imageSize,
        alpha,
        imageSize,
        centerPrincipalPoint
      ]),
      getOptionalParamsMap: () => ([
        ['flags', cv.CALIB_ZERO_DISPARITY],
        ['alpha', 0],
        ['newImageSize', imageSize]
      ]),
      expectOutput
    });
  });

  describe('decomposeEssentialMat', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('R1').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R1)(3, 3, cv.CV_64F);
      expect(res).to.have.property('R2').to.be.instanceOf(cv.Mat);
      assertMetaData(res.R2)(3, 3, cv.CV_64F);
      expect(res).to.have.property('T');
      expectToBeVec3(res.T);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'decomposeEssentialMat',
      methodNameSpace: 'Mat',
      expectOutput
    });
  });

  describe('triangulatePoints', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(res)(4, imagePoints.length, cv.CV_64F);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 4, cv.CV_64F),
      methodName: 'triangulatePoints',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        cv.Mat.eye(3, 4, cv.CV_64F),
        imagePoints,
        imagePoints
      ]),
      expectOutput
    });
  });

  describe('correctMatches', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('newPoints1').to.be.an('array').lengthOf(imagePoints.length);
      expect(res).to.have.property('newPoints2').to.be.an('array').lengthOf(imagePoints.length);
      res.newPoints1.forEach(pt => expectToBeVec2(pt));
      res.newPoints2.forEach(pt => expectToBeVec2(pt));
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'correctMatches',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        imagePoints,
        imagePoints
      ]),
      expectOutput
    });
  });

  describe('filterSpeckles', () => {
    const expectOutput = () => {
      // expect not to throw
    };
    const newVal = 1.0;
    const maxSpeckleSize = 10;
    const maxDiff = 0.8;

    generateAPITests({
      getDut: () => new cv.Mat(200, 200, cv.CV_8U, 0),
      methodName: 'filterSpeckles',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        newVal,
        maxSpeckleSize,
        maxDiff
      ]),
      expectOutput
    });
  });

  describe('validateDisparity', () => {
    const expectOutput = () => {
      // expect not to throw
    };
    const cost = new cv.Mat(10, 10, cv.CV_16S, 0);
    const minDisparity = 1;
    const numberOfDisparities = 2;
    const disp12MaxDisp = 2;

    generateAPITests({
      getDut: () => new cv.Mat(10, 10, cv.CV_16S, 0),
      methodName: 'validateDisparity',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        cost,
        minDisparity,
        numberOfDisparities
      ]),
      getOptionalArg: () => disp12MaxDisp,
      expectOutput
    });
  });

  describe('reprojectImageTo3D', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(res)(200, 200, cv.CV_32FC3);
    };

    const Q = cv.Mat.eye(4, 4, cv.CV_64F);

    generateAPITests({
      getDut: () => new cv.Mat(200, 200, cv.CV_8U, 0),
      methodName: 'reprojectImageTo3D',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        Q
      ]),
      getOptionalParamsMap: () => ([
        ['handleMissingValues', true],
        ['ddepth', -1]
      ]),
      expectOutput
    });
  });

  describe('decomposeHomographyMat', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('returnValue').to.be.a('number');
      expect(res).to.have.property('rotations').to.be.an('array');
      expect(res.rotations.length).to.be.above(0);
      res.rotations.forEach(mat => assertMetaData(mat)(3, 3, cv.CV_64F));
      expect(res).to.have.property('translations').to.be.an('array');
      expect(res.translations.length).to.be.above(0);
      res.translations.forEach(mat => assertMetaData(mat)(3, 1, cv.CV_64F));
      expect(res).to.have.property('normals').to.be.an('array');
      expect(res.normals.length).to.be.above(0);
      res.normals.forEach(mat => assertMetaData(mat)(3, 1, cv.CV_64F));
    };

    const K = cv.Mat.eye(3, 3, cv.CV_64F);

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'decomposeHomographyMat',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        K
      ]),
      expectOutput
    });
  });

  (cvVersionLowerThan(3, 1, 0) ? describe.skip : describe)('findEssentialMat', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('E').to.be.instanceOf(cv.Mat);
      assertMetaData(res.E)(3, 3, cv.CV_64F);
      expect(res).to.have.property('mask').to.be.instanceOf(cv.Mat);
      assertMetaData(res.mask)(8, 1, cv.CV_8U);
    };

    generateAPITests({
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'findEssentialMat',
      getRequiredArgs: () => [
        imagePoints,
        imagePoints
      ],
      getOptionalParamsMap: () => ([
        ['method', cv.LMEDS],
        ['prob', 0.9],
        ['threshold', 2.0]
      ]),
      expectOutput
    });
  });

  (cvVersionLowerThan(3, 1, 0) ? describe.skip : describe)('recoverPose', () => {
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
      getDut: () => cv.Mat.eye(3, 3, cv.CV_64F),
      methodName: 'recoverPose',
      getRequiredArgs: () => [
        E,
        imagePoints,
        imagePoints
      ],
      getOptionalParamsMap: () => ([
        ['mask', mask]
      ]),
      expectOutput
    });
  });

  if (cvVersionGreaterEqual(4, 0, 0)) {
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
