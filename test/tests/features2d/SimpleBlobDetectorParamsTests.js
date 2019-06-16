module.exports = ({ cv, utils, getTestImg }) => {

  const {
    assertPropsWithValue
  } = utils;

  describe('accessors', () => {
    it('properties are set correctly', () => {
      const params = {
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
        minInertiaRatio: 0.5
      };

      const detectorParams = new cv.SimpleBlobDetectorParams();
      Object.keys(params).forEach((param) => { detectorParams[param] = params[param]; });
      assertPropsWithValue(detectorParams)(params);
    });
  });

};

