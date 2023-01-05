import { cv, getResourcePath, drawBlueRect, wait4key } from '../utils';

export async function faceDetection() {
  const image = cv.imread(getResourcePath('got.jpg'));
  const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

  // detect faces
  const { objects, numDetections } = classifier.detectMultiScale(image.bgrToGray());
  console.log('faceRects:', objects);
  console.log('confidences:', numDetections);

  if (!objects.length) {
    throw new Error('No faces detected!');
  }

  // draw detection
  const numDetectionsTh = 10;
  objects.forEach((rect, i) => {
    const thickness = numDetections[i] < numDetectionsTh ? 1 : 2;
    drawBlueRect(image, rect, { thickness });
  });

  cv.imshow('face detection', image);
  await wait4key();
}

faceDetection();