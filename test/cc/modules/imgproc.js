import { Mat, Point, Size, imgproc, cvTypes } from 'dut';
import { assertError, assertPropsWithValue, funcRequiresArgsObject } from 'utils';

describe('imgproc', () => {
  describe('getStructuringElement', () => {
    const rows = 4;
    const cols = 3;
    const size = new Size(cols, rows);

    funcRequiresArgsObject(imgproc.getStructuringElement);

    it('should throw if type invalid', () => {
      assertError(() => new Mat().convertTo({ type: undefined }), 'Invalid type for type');
      assertError(() => new Mat().convertTo({ type: null }), 'Invalid type for type');
    });

    it('should be constructable with required args', () => {
      const kernel = imgproc.getStructuringElement({
        shape: cvTypes.morphShapes.MORPH_CROSS,
        size
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });

    it('should be constructable with anchor', () => {
      const kernel = imgproc.getStructuringElement({
        shape: cvTypes.morphShapes.MORPH_CROSS,
        size,
        anchor: new Point(0, 1)
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });
  });
});
