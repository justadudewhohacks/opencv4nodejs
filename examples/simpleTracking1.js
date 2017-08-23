const cv = require('../');
const { grabFrames, drawRectAroundBlobs } = require('./utils');

const bgSubtractor = new cv.BackgroundSubtractorMOG2();

const delay = 50;
grabFrames('../data/traffic.mp4', delay, (frame) => {
  const foreGroundMask = bgSubtractor.apply(frame);

  const dilated = foreGroundMask.dilate({
    kernel: cv.getStructuringElement({
      shape: cv.cvTypes.morphShapes.MORPH_ELLIPSE,
      size: new cv.Size(4, 4)
    }),
    iterations: 2
  });
  const blurred = dilated.blur({
    ksize: new cv.Size(10, 10)
  });
  const thresholded = blurred.threshold({
    thresh: 200,
    maxVal: 255,
    type: cv.cvTypes.thresholdTypes.THRESH_BINARY
  });

  const minPxSize = 4000;
  drawRectAroundBlobs(thresholded, frame, minPxSize);

  cv.imshow('foreGroundMask', foreGroundMask);
  cv.imshow('thresholded', thresholded);
  cv.imshow('frame', frame);
});
