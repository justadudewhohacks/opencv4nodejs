const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const {
    assertMetaData,
    getTestVideoPath
  } = utils;

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

  describe('set', () => {
    it('should set properties', () => {
      const cap = new cv.VideoCapture(getTestVideoPath());
      const wasSet = cap.set(cv.CAP_PROP_POS_MSEC, 1000)
      expect(cap.get(cv.CAP_PROP_POS_MSEC)|0).to.equal(1001);
      expect(wasSet).to.equal(true);
    });
  });

  describe('setAsync', () => {
    it('should set properties', (done) => {
      const cap = new cv.VideoCapture(getTestVideoPath());
      cap.setAsync(cv.CAP_PROP_POS_MSEC, 1000, (err, wasSet) => {
        expect(cap.get(cv.CAP_PROP_POS_MSEC)|0).to.equal(1001);
        expect(wasSet).to.equal(true);
        done();
      });
    });
  });

};
