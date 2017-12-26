const {
  cv
} = require('../utils');

const { runVideoFaceDetection } = require('./commons');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

function detectFaces(img) {
  // restrict minSize and scaleFactor for faster processing
  const options = {
    // minSize: new cv.Size(40, 40),
    // scaleFactor: 1.2,
    scaleFactor: 1.1,
    minNeighbors: 10
  };
  return classifier.detectMultiScale(img.bgrToGray(), options).objects;
}

runVideoFaceDetection(detectFaces);
