const cv = global.dut;
const { generateAPITests } = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('applyColorMap', () => {
    it('should have all colormap types in the "cv" object', () => {
      const COLORMAP_TYPE_NAMES = [
        'COLORMAP_AUTUMN',
        'COLORMAP_BONE',
        'COLORMAP_JET',
        'COLORMAP_WINTER',
        'COLORMAP_RAINBOW',
        'COLORMAP_OCEAN',
        'COLORMAP_SUMMER',
        'COLORMAP_SPRING',
        'COLORMAP_COOL',
        'COLORMAP_HSV',
        'COLORMAP_PINK',
        'COLORMAP_HOT',
        'COLORMAP_PARULA',
      ];

      COLORMAP_TYPE_NAMES.forEach((name) => {
        expect(typeof cv[name]).to.be.equal('number');
      });
    });

    it('should process an image with a type of colormap integer', () => {
      generateAPITests({
        getDut: () => cv,
        methodName: 'applyColorMap',
        getRequiredArgs: () => ([
          new cv.Mat([[0, 1, 100]], cv.CV_8UC1),
          cv.COLORMAP_HOT,
        ]),
        hasAsync: true,
        usesMacroInferno: false,
        expectOutput: res => {
          return expect(res).to.be.instanceOf(cv.Mat)
        },
      });
    });

    if (global.utils.cvVersionGreaterEqual(3, 3, 0)) {
      it('should process an image with a customized colormap', () => {
        generateAPITests({
          getDut: () => cv,
          methodName: 'applyColorMap',
          getRequiredArgs: () => ([
            new cv.Mat([[0, 1, 100]], cv.CV_8UC1),
            new cv.Mat(256, 1, cv.CV_8UC3),
          ]),
          hasAsync: true,
          usesMacroInferno: false,
          expectOutput: res => {
            return expect(res).to.be.instanceOf(cv.Mat)
          },
        });
      });
    }
  });
};
