const cv = global.dut;
const {
  assertError,
  assertPropsWithValue,
  assertMetaData,
  funcShouldRequireArgs,
  readTestImage,
  generateAPITests
} = global.utils;
const { expect } = require('chai');

describe('photo', () => {

  describe('inpaint', () => {

    it('should have constants', () => {
      expect(isNaN(cv.INPAINT_TELEA)).to.be.equal(false);
      expect(isNaN(cv.INPAINT_NS)).to.be.equal(false);
    });


    it('should perform inpainting', () => {

      // construct a black image with a white dot in the middle
      const imgData = new Array(7*7).fill(0);
      imgData[7 * 3 + 3] = 255;
      const image = new cv.Mat(new Buffer(imgData), 7,7,cv.CV_8U);
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
      const image = new cv.Mat(new Buffer(imgData), 7,7,cv.CV_8U);
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
  })
});
