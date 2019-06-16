const ioTests = require('./ioTests');
const VideoCaptureTests = require('./VideoCaptureTests');
const VideoWriterTests = require('./VideoWriterTests');

module.exports = function (args) {
  describe('io', () => ioTests(args));
  if (!process.env.DOCKER_BUILD && !process.env.BINDINGS_DEBUG) {
    describe('VideoCapture', () => VideoCaptureTests(args));
    // TODO: fix unlink EBUSY
    describe.skip('VideoWriter', () => VideoWriterTests(args));
  }
};