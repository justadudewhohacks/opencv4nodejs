const cv = global.dut;
const {
  assertMetaData,
  getTestVideoPath
} = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('VideoCapture', () => {
    describe('constructor', () => {
      it('can be opened from valid video file', () => {
        expect(() => new cv.VideoCapture(getTestVideoPath())).to.not.throw();
      });
    });

    describe('read', () => {
      let cap;
      before(() => {
        cap = new cv.VideoCapture(getTestVideoPath());
      });

      describe('sync', () => {
        it('should read a frame', () => {
          const frame = cap.read();
          expect(frame).to.be.instanceOf(cv.Mat);
          assertMetaData(frame)(360, 640, cv.CV_8UC3);
        });
      });

      describe('async', () => {
        it('should read a frame', (done) => {
          cap.readAsync((err, frame) => {
            expect(frame).to.be.instanceOf(cv.Mat);
            assertMetaData(frame)(360, 640, cv.CV_8UC3);
            done();
          });
        });
      });
    });

    describe('properties', () => {
      it('should get properties', () => {
        const cap = new cv.VideoCapture(getTestVideoPath());
        expect(cap.get(cv.CAP_PROP_FRAME_WIDTH)).to.equal(640);
        expect(cap.get(cv.CAP_PROP_FRAME_HEIGHT)).to.equal(360);
      });
    });
  });
};
