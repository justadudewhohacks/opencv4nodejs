import { Point, Size, imgproc } from 'dut';
import { assertPropsWithValue, funcRequiresArgsObject } from 'utils';

const { morphShapes } = imgproc;

describe('imgproc', () => {
  describe('getStructuringElement', () => {
    const rows = 4;
    const cols = 3;
    const size = new Size(cols, rows);

    funcRequiresArgsObject(imgproc.getStructuringElement);

    it('should be constructable with required args', async () => {
      const kernel = imgproc.getStructuringElement({
        shape: morphShapes.MORPH_CROSS,
        size
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });

    it('should be constructable with anchor', async () => {
      const kernel = imgproc.getStructuringElement({
        shape: morphShapes.MORPH_CROSS,
        size,
        anchor: new Point(0, 1)
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });
  });
});
