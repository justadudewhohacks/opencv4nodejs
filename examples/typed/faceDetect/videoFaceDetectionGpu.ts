import {
  getDataFilePath
} from '../utils';
import * as cv from '../../../';

if (cv.version.minor === 4) {
  console.log('Warning: It seems like opencv 3.4 does not run the opencl version of detectMultiScale.');
}

const { runVideoFaceDetection } = require('./commons');

const videoFile = getDataFilePath('people.mp4');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

function detectFaces(img: cv.Mat) {
  return classifier.detectMultiScaleGpu(img.bgrToGray(), 1.1, 10);
}

runVideoFaceDetection(videoFile, detectFaces);
