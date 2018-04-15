const {
  cv,
  getDataFilePath
} = require('../utils');

if (cv.version.minor === 4) {
  console.log('Warning: It seems like opencv 3.4 does not run the opencl version of detectMultiScale.');
}

const { runVideoFaceDetection } = require('./commons');

const videoFile = getDataFilePath('people.mp4');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

function detectFaces(img) {
  const options = {
    scaleFactor: 1.1,
    minNeighbors: 10
  };
  return classifier.detectMultiScaleGpu(img.bgrToGray(), options).objects;
}

runVideoFaceDetection(videoFile, detectFaces);
