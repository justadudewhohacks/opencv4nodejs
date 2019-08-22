const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const {
    assertError,
    assertPropsWithValue,
    assertMetaData,
    funcShouldRequireArgs,
    readTestImage,
    generateClassMethodTests
  } = utils;

  describe('inpaint', () => {

    it('should have constants', () => {
      expect(isNaN(cv.INPAINT_TELEA)).to.be.equal(false);
      expect(isNaN(cv.INPAINT_NS)).to.be.equal(false);
    });


    it('should perform inpainting', () => {

      // construct a black image with a white dot in the middle
      const imgData = new Array(7*7).fill(0);
      imgData[7 * 3 + 3] = 255;
      const image = new cv.Mat(Buffer.from(imgData), 7,7,cv.CV_8U);
      // construct the mask from the same image (since we want to inpaint the white dot)
      const mask = image.copy();

      // perform inpainting
      const inpainted = cv.inpaint(image, mask, 3, cv.INPAINT_TELEA);

      // now the result should be all black
      const sum = inpainted.sum();

      // so sum should be 0
      expect(sum).to.be.equal(0);
    });

    it('should perform inpainting async', (done) => {

      // construct a black image with a white dot in the middle
      const imgData = new Array(7*7).fill(0);
      imgData[7 * 3 + 3] = 255;
      const image = new cv.Mat(Buffer.from(imgData), 7,7,cv.CV_8U);
      // construct the mask from the same image (since we want to inpaint the white dot)
      const mask = image.copy();

      // perform inpainting
      cv.inpaintAsync(image, mask, 3, cv.INPAINT_TELEA)
        .then(inpainted => {
          // now the result should be all black
          const sum = inpainted.sum();

          // so sum should be 0
          expect(sum).to.be.equal(0);

          done();
        }).catch(done);
    });
  });

  describe('seamlessClone', () => {

    it('should have constants', () => {
      expect(isNaN(cv.NORMAL_CLONE)).to.be.equal(false);
      expect(isNaN(cv.MIXED_CLONE)).to.be.equal(false);
      expect(isNaN(cv.MONOCHROME_TRANSFER)).to.be.equal(false);
    });

    const src = new cv.Mat(5, 5, cv.CV_8UC3, [128, 128, 128]);
    const dest = new cv.Mat(10, 10, cv.CV_8UC3, [32, 32, 32]);
    const mask = new cv.Mat(5, 5, cv.CV_8UC3, [255, 255, 255]);
    const center = new cv.Point2(5, 5);
    const cloneType = cv.NORMAL_CLONE;

    const expectOutput = (res) => {
      assertMetaData(res)(dest.rows, dest.cols, cv.CV_8UC3);
    };

    generateClassMethodTests({
      getClassInstance: () => src,
      methodName: 'seamlessClone',
      classNameSpace: 'Mat',
      methodNameSpace: 'Photo',
      getRequiredArgs: () => ([
        dest,
        mask,
        center,
        cloneType
      ]),
      expectOutput
    });
  });

};
