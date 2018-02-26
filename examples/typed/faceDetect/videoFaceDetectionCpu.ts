import {
  getDataFilePath
} from '../utils';
import * as cv from '../../../';

const { runVideoFaceDetection } = require('./commons');

const videoFile = getDataFilePath('people.mp4');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

function detectFaces(img: cv.Mat) {
  return classifier.detectMultiScale(img.bgrToGray(), 1.1, 10).objects;
}

runVideoFaceDetection(videoFile, detectFaces);
