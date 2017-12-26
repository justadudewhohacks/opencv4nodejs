const {
  cv,
  getDataFilePath,
  grabFrames,
  drawBlueRect
} = require('../utils');

const videoFile = getDataFilePath('people.mp4');

exports.runVideoFaceDetection = detectFaces => grabFrames(videoFile, 1, (frame) => {
  console.time('detection time');
  const frameResized = frame.resizeToMax(800);

  // detect faces
  const faceRects = detectFaces(frameResized);
  if (faceRects.length) {
    // draw detection
    faceRects.forEach(faceRect => drawBlueRect(frameResized, faceRect));
  }

  cv.imshow('face detection', frameResized);
  console.timeEnd('detection time');
});
