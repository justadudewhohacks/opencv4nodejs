import { Mat, Rect } from '@u4/opencv4nodejs';
import { cv, getResourcePath } from '../utils';
import { runVideoFaceDetectionAsync } from './commons';

const videoFile = getResourcePath('people.mp4');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

async function detectFaces(img: Mat): Promise<Rect[]> {
  // restrict minSize and scaleFactor for faster processing
  const options = {
    // minSize: new cv.Size(40, 40),
    // scaleFactor: 1.2,
    scaleFactor: 1.1,
    minNeighbors: 10,
  };
  const detection = await classifier.detectMultiScaleAsync(img.bgrToGray(), options);
  return detection.objects;
}

runVideoFaceDetectionAsync(videoFile, detectFaces);
