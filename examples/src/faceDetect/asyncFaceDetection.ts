import { cv, getResourcePath, drawBlueRect, wait4key } from '../utils';

export async function asyncFaceDetection() {
  const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);
  try {
    const img = await cv.imreadAsync(getResourcePath('got.jpg'))
    const grayImg = await img.bgrToGrayAsync()
    const res = await classifier.detectMultiScaleAsync(grayImg)
    const { objects, numDetections } = res;
    if (!objects.length) {
      return Promise.reject('No faces detected!');
    }
    // draw detection
    const facesImg = img.copy();
    const numDetectionsTh = 10;
    console.log(`detectMultiScale Found ${objects.length} objects`);
    objects.forEach((rect, i) => {
      const thickness = numDetections[i] < numDetectionsTh ? 1 : 2;
      drawBlueRect(facesImg, rect, { thickness });
    });
    cv.imshow('face detection', facesImg);
    await wait4key();
  } catch (err) { 
    console.error(err);
  }
}

asyncFaceDetection();
