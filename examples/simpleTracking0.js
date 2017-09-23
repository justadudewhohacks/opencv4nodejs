const cv = require('../');
const { grabFrames, drawRectAroundBlobs } = require('./utils');

const delay = 100;
grabFrames('../data/horses.mp4', delay, (frame) => {
  const frameHLS = frame.cvtColor(cv.COLOR_BGR2HLS);

  const brownUpper = new cv.Vec(10, 60, 165);
  const brownLower = new cv.Vec(5, 20, 100);
  const rangeMask = frameHLS.inRange(brownLower, brownUpper);

  const blurred = rangeMask.blur(new cv.Size(10, 10));
  const thresholded = blurred.threshold(100, 255, cv.THRESH_BINARY);

  const minPxSize = 200;
  const fixedRectWidth = 50;
  drawRectAroundBlobs(thresholded, frame, minPxSize, fixedRectWidth);

  cv.imshow('rangeMask', rangeMask);
  cv.imshow('thresholded', thresholded);
  cv.imshow('frame', frame);
});
