import { expect } from 'chai';
import { TestContext } from '../model';

export default function (args: TestContext) {
  const { cv, utils } = args;

  const {
    assertMetaData,
    getTestVideoPath,
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

  describe('VideoCapture properties', () => {
    it('should get properties', () => {
      const cap = new cv.VideoCapture(getTestVideoPath());
      expect(cap.get(cv.CAP_PROP_FRAME_WIDTH)).to.equal(640);
      expect(cap.get(cv.CAP_PROP_FRAME_HEIGHT)).to.equal(360);
    });
  });

  describe('VideoCapture set', () => {
    it('should set properties', () => {
      const cap = new cv.VideoCapture(getTestVideoPath());
      const wasSet = cap.set(cv.CAP_PROP_POS_MSEC, 1000);
      const msec = cap.get(cv.CAP_PROP_POS_MSEC) | 0;
      // depending of openCV version, result can be 83 or 1001
      if (msec === 83) // openCV 3.4.6 and below
      { expect(msec).to.equal(83); } else // openCV 3.4.8 and over
      { expect(msec).to.equal(1001); }
      expect(wasSet).to.equal(true);
    });
  });

  describe('VideoCapture setAsync', () => {
    it('should set properties', async () => {
      const cap = new cv.VideoCapture(getTestVideoPath());
      const wasSet = await cap.setAsync(cv.CAP_PROP_POS_MSEC, 1000);
      // depending of openCV version, result can be 83 or 1001
      const msec = cap.get(cv.CAP_PROP_POS_MSEC) | 0;
      if (msec === 83) // openCV 3.4.6 and below
      { expect(msec).to.equal(83); } else // openCV 3.4.8 and over
      { expect(msec).to.equal(1001); }
      expect(wasSet).to.equal(true);
      return true;
    });
  });
}
