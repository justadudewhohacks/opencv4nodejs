import { Mat } from '../../lib/typings/openCV';
import { cv } from '../utils';
import { runVideoFaceDetection } from './commons';

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

const webcamPort = 0;

function detectFaces(img: Mat) {
  // restrict minSize and scaleFactor for faster processing
  const options = {
    minSize: new cv.Size(100, 100),
    scaleFactor: 1.2,
    minNeighbors: 10
  };
  return classifier.detectMultiScaleGpu(img.bgrToGray(), options); // .objects
}

runVideoFaceDetection(webcamPort, detectFaces);
