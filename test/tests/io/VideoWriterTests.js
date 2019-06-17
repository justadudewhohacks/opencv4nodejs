const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const {
    clearTmpData,
    fileExists,
    getTmpDataFilePath
  } = utils;

  describe('constructor', () => {
    beforeEach(() => { clearTmpData(); });
    afterEach(() => { clearTmpData(); });

    it('can be opened from valid video file and codec', () => {
      const code = cv.VideoWriter.fourcc('MJPG');
      const file = getTmpDataFilePath('video.avi');
      const fps = 24;
      const writer = new cv.VideoWriter(file, code, fps, new cv.Size(800, 600));
      writer.release();
      expect(fileExists(file)).to.be.true;
    });
  });

  describe('write', () => {
    let writer;
    before(() => {
      clearTmpData();
      writer = new cv.VideoWriter(
        getTmpDataFilePath('video.avi'),
        cv.VideoWriter.fourcc('MJPG'),
        24,
        new cv.Size(800, 600)
      );
    });

    after(() => {
      writer.release();
      clearTmpData();
    });

    describe('sync', () => {
      it('should read a frame', () => {
        expect(writer.write(new cv.Mat(600, 800, cv.CV_8UC3))).to.not.throw();
      });
    });

    describe('async', () => {
      it('should read a frame', (done) => {
        expect(writer.writeAsync(new cv.Mat(600, 800, cv.CV_8UC3), () => {
          done();
        })).to.not.throw();
      });
    });
  });
};
