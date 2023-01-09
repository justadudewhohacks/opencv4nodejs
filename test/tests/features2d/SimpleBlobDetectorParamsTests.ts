import { SimpleBlobDetectorParams } from '../../../typings';
import { assertPropsWithValue } from '../../utils/testUtils';
import { TestContext } from '../model';

export default function (args: TestContext) {
  const { cv } = args;

  describe('accessors', () => {
    it('properties are set correctly', () => {
      const params: SimpleBlobDetectorParams = {
        blobColor: 255,
        minThreshold: 20.5,
        maxThreshold: 400.5,
        thresholdStep: 40.5,
        minDistBetweenBlobs: 500.5,
        minRepeatability: 20,
        filterByArea: true,
        maxArea: 8000,
        minArea: 1000,
        filterByCircularity: true,
        maxCircularity: 5.5,
        minCircularity: 4.5,
        filterByColor: true,
        filterByConvexity: true,
        maxConvexity: 3.5,
        minConvexity: 2.5,
        filterByInertia: true,
        maxInertiaRatio: 1.5,
        minInertiaRatio: 0.5,
      };

      const detectorParams = new cv.SimpleBlobDetectorParams();
      Object.keys(params).forEach((param: keyof SimpleBlobDetectorParams) => { (detectorParams as any)[param] = params[param]; });
      assertPropsWithValue(detectorParams, params);
    });
  });
}
