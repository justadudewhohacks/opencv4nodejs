const cv = require('../');
const { grabFrames, drawRectAroundBlobs } = require('./utils');

const bgSubtractor = new cv.BackgroundSubtractorMOG2();

const delay = 50;
grabFrames('../data/traffic.mp4', delay, (frame) => {
  const foreGroundMask = bgSubtractor.apply(frame);

  const iterations = 2;
  const dilated = foreGroundMask.dilate(
    cv.getStructuringElement(cv.MORPH_ELLIPSE, new cv.Size(4, 4)),
    new cv.Point(-1, -1),
    iterations
  );
  const blurred = dilated.blur(new cv.Size(10, 10));
  const thresholded = blurred.threshold(200, 255, cv.THRESH_BINARY);

  const minPxSize = 4000;
  drawRectAroundBlobs(thresholded, frame, minPxSize);

  cv.imshow('foreGroundMask', foreGroundMask);
  cv.imshow('thresholded', thresholded);
  cv.imshow('frame', frame);
});
