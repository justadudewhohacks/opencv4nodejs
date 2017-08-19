import opencv from 'dut';
import { assertError, assertPropsWithValue, funcRequiresArgsObject, readTestImage } from 'utils';

const { Mat, Vec, Point, Size, cvTypes, plot1DHist } = opencv;

describe('imgproc', () => {
  let testImg;

  before(async () => {
    testImg = (await readTestImage()).resizeToMax(250);
  });

  describe('getStructuringElement', () => {
    const rows = 4;
    const cols = 3;
    const size = new Size(cols, rows);

    funcRequiresArgsObject(opencv.getStructuringElement);

    it('should throw if type invalid', () => {
      assertError(() => new Mat().convertTo({ type: undefined }), 'Invalid type for type');
      assertError(() => new Mat().convertTo({ type: null }), 'Invalid type for type');
    });

    it('should be constructable with required args', () => {
      const kernel = opencv.getStructuringElement({
        shape: cvTypes.morphShapes.MORPH_CROSS,
        size
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });

    it('should be constructable with anchor', () => {
      const kernel = opencv.getStructuringElement({
        shape: cvTypes.morphShapes.MORPH_CROSS,
        size,
        anchor: new Point(0, 1)
      });
      assertPropsWithValue(kernel)({ rows, cols });
    });
  });

  describe('calcHist', () => {
    it('should return 1 dimensional hist', () => {
      const hist = opencv.calcHist({
        img: testImg,
        histAxes: [
          {
            channel: 0,
            bins: 8,
            ranges: [0, 256]
          }
        ]
      });
      assertPropsWithValue(hist)({ rows: 8, cols: 1, dims: 2 });
    });

    it('should return 2 dimensional hist', () => {
      const hist = opencv.calcHist({
        img: testImg,
        histAxes: [
          {
            channel: 0,
            bins: 8,
            ranges: [0, 256]
          },
          {
            channel: 1,
            bins: 32,
            ranges: [0, 256]
          }
        ]
      });
      assertPropsWithValue(hist)({ rows: 8, cols: 32, dims: 2 });
    });

    it('should return 3 dimensional hist', () => {
      const hist = opencv.calcHist({
        img: testImg,
        histAxes: [
          {
            channel: 0,
            bins: 8,
            ranges: [0, 256]
          },
          {
            channel: 1,
            bins: 8,
            ranges: [0, 256]
          },
          {
            channel: 2,
            bins: 8,
            ranges: [0, 256]
          }
        ]
      });
      assertPropsWithValue(hist)({ dims: 3 });
    });
  });
});
