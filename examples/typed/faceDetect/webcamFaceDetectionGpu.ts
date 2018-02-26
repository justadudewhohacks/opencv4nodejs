import * as cv from '../../../';

const { runVideoFaceDetection } = require('./commons');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

const webcamPort = 0;

function detectFaces(img: cv.Mat) {
  return classifier.detectMultiScale(img.bgrToGray(), 1.2, 10, 0, new cv.Size(100, 100)).objects;
}

runVideoFaceDetection(webcamPort, detectFaces);
