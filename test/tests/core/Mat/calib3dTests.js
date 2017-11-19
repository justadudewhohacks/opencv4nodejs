const cv = global.dut;
const {
  assertMetaData,
  generateAPITests,
  expectToBeVec2,
  expectToBeVec3,
  expectToBeVec4
} = global.utils;
const { expect } = require('chai');

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
const cameraMatrix = cv.Mat.eye(3, 3, cv.CV_64F);
const projectionMatrix = cv.Mat.eye(3, 4, cv.CV_64F);
const distCoefficients = [0, 0.5, 1.0, 1.0];

module.exports = () => {
  describe('rodrigues', () => {
    const expectOutput = (res) => {
      expect(res).to.have.property('dst').to.be.instanceOf(cv.Mat);
      assertMetaData(res.dst)(3, 1, cv.CV_64F);
      expect(res).to.have.property('jacobian').to.be.instanceOf(cv.Mat);
      assertMetaData(res.jacobian)(9, 3, cv.CV_64F);
    };

    generateAPITests({
      getDut: () => cameraMatrix,
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
      getDut: () => cameraMatrix,
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
      getDut: () => projectionMatrix,
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

    const B = cameraMatrix;

    generateAPITests({
      getDut: () => cameraMatrix,
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

    const img = new cv.Mat(200, 200, cv.CV_8UC3);
    const patternSize = new cv.Size(100, 100);
    const flags = cv.CALIB_CB_ADAPTIVE_THRESH + cv.CALIB_CB_NORMALIZE_IMAGE;
    generateAPITests({
      getDut: () => img,
      methodName: 'findChessboardCorners',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        patternSize
      ]),
      getOptionalArgs: () => ([
        flags
      ]),
      expectOutput
    });
  });

  describe('drawChessboardCorners', () => {
    const img = new cv.Mat(200, 200, cv.CV_8U, 0);
    const expectOutput = () => {
      // expect not to throw
    };

    const patternSize = new cv.Size(50, 50);
    const corners = [
      new cv.Point(50, 50),
      new cv.Point(50, 100),
      new cv.Point(100, 50),
      new cv.Point(100, 100)
    ];
    const patternWasFound = true;

    generateAPITests({
      getDut: () => img,
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

    const regionSize = new cv.Size(50, 50);
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
      getDut: () => cameraMatrix,
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
    const T = new cv.Vec(0, 0, 0);

    describe('stereoRectify', () => {
      generateAPITests({
        getDut: () => cameraMatrix,
        methodName: 'stereoRectify',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distCoefficients,
          cameraMatrix,
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

    describe('rectify3Collinear', () => {
      const alpha = 0;
      const flags = cv.CALIB_ZERO_DISPARITY;

      generateAPITests({
        getDut: () => cameraMatrix,
        methodName: 'rectify3Collinear',
        methodNameSpace: 'Mat',
        getRequiredArgs: () => ([
          distCoefficients,
          cameraMatrix,
          distCoefficients,
          cameraMatrix,
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
      getDut: () => cameraMatrix,
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
      getDut: () => cameraMatrix,
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
      getDut: () => projectionMatrix,
      methodName: 'triangulatePoints',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        projectionMatrix,
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
      getDut: () => cameraMatrix,
      methodName: 'correctMatches',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        imagePoints,
        imagePoints
      ]),
      expectOutput
    });
  });
};
