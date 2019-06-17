const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    readTestImage,
    generateAPITests,
    assertMetaData,
    cvVersionGreaterEqual
  } = utils;

  describe('blobFromImage', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
      assertMetaData(res)(-1, -1, cv.CV_32F);
    };

    const getOptionalArgsMap = () => ([
      ['scalefactor', 0.8],
      ['size', new cv.Size(3, 3)],
      ['mean', new cv.Vec(0.5, 0.5, 0.5)],
      ['swapRB', true]
    ]);

    describe('blobFromImage', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'blobFromImage',
        getRequiredArgs: () => ([
          getTestImg().resizeToMax(250)
        ]),
        getOptionalArgsMap: () => ([
          ['scalefactor', 0.8],
          ['size', new cv.Size(3, 3)],
          ['mean', new cv.Vec(0.5, 0.5, 0.5)],
          ['swapRB', true]
        ]),
        expectOutput
      });
    });

    describe('blobFromImages', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'blobFromImages',
        getRequiredArgs: () => ([
          [getTestImg().resizeToMax(250), getTestImg().resizeToMax(250)]
        ]),
        getOptionalArgsMap,
        expectOutput
      });
    });

    describe('blobFromImage', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'blobFromImage',
        getRequiredArgs: () => ([
          getTestImg().resizeToMax(250)
        ]),
        getOptionalArgsMap: () => ([
          ['scalefactor', 0.8],
          ['size', new cv.Size(3, 3)],
          ['mean', new cv.Vec(0.5, 0.5, 0.5)],
          ['swapRB', true],
          ['crop', false],
          ['ddepth', cv.CV_32F]
        ]),
        expectOutput
      });
    });
  });

  if (cvVersionGreaterEqual(3, 4, 0)) {
    describe('NMSBoxes', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'NMSBoxes',
        hasAsync: false,
        getRequiredArgs: () => ([
          [new cv.Rect(0, 0, 1, 1)],
          [1],
          0.5,
          0.4,
        ]),
        expectOutput: (res) => {
          expect(res).to.be.instanceOf(Array);
          expect(res[0]).to.be.equal(0);
        },
      });
    });
  }

};
