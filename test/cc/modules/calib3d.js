import { cvTypes, calib3d } from 'dut';
import { assertPropsWithValue, funcRequiresArgsObject } from 'utils';
import { assert } from 'chai';

describe('calib3d', () => {
  describe('findHomography', () => {
    funcRequiresArgsObject(calib3d.findHomography);

    it('should throw if point validation fails', () => {
      let errMsg = '';
      try {
        calib3d.findHomography({ srcPoints: [{ x: 100 }], dstPoints: [{ x: 100 }] });
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'has no property: y');
    });

    it('should calculate a valid homography', () => {
      const srcPoints = [{ x: 100, y: 100 }, { x: 100, y: -100 }, { x: -100, y: 100 }, { x: -100, y: -100 }];
      const dstPoints = srcPoints.map(srcPt => ({ x: srcPt.x * 2, y: srcPt.y * 2 }));
      const homography = calib3d.findHomography({ srcPoints, dstPoints });
      assertPropsWithValue(homography)({ type: cvTypes.CV_64F, rows: 3, cols: 3 });
    });

    /*
    it('should catch cv exception if set of points is empty', () => {
      let errMsg = '';
      try {
        calib3d.findHomography({ srcPoints: [], dstPoints: [] });
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'findHomography');
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
      assert.include(errMsg, 'findHomography');
    });
    */
  });
});
