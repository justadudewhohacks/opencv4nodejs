import { matTypes, calib3d } from 'dut';
import { assertPropsWithValue } from 'utils';
import { assert } from 'chai';

describe.only('calib3d', () => {
  describe('findHomography', () => {
    it('should throw if args empty', () => {
      let errMsg = '';
      try {
        calib3d.findHomography();
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'empty args');
    });

    it('should calculate a valid homography', () => {
      const srcPoints = [{ x: 0, y: 0 }, { x: 1000, y: 0 }, { x: 0, y: 1000 }, { x: 1000, y: 1000 }];
      const dstPoints = srcPoints.map(srcPt => ({ x: srcPt.x * 2, y: srcPt.y * 2 }));
      const homography = calib3d.findHomography({ srcPoints, dstPoints });
      assertPropsWithValue(homography)({ type: matTypes.CV_64F, rows: 3, cols: 3 });
    });

    it('should catch cv exception if set of points is empty', () => {
      let errMsg = '';
      try {
        calib3d.findHomography({ srcPoints: [], dstPoints: [] });
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'cv::findHomography');
    });

    it('should catch cv exception if number of points mismatch', () => {
      const srcPoints = [{ x: 0, y: 0 }, { x: 1000, y: 0 }];
      const dstPoints = [{ x: 0, y: 0 }];
      let errMsg = '';
      try {
        calib3d.findHomography({ srcPoints, dstPoints });
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'cv::findHomography');
    });

  });
});
