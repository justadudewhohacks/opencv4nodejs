import { TestContext } from '../model';
import ioTests from './ioTests';
import VideoCaptureTests from './VideoCaptureTests';
import VideoWriterTests from './VideoWriterTests';

export default (args: TestContext) => {
  describe('io', () => ioTests(args));
  if (!process.env.DOCKER_BUILD && !process.env.BINDINGS_DEBUG) {
    describe('VideoCapture', () => VideoCaptureTests(args));
    // TODO: fix unlink EBUSY
    describe.skip('VideoWriter', () => VideoWriterTests(args));
  }
};
