import {
  getDataFilePath,
  drawBlueRect,
  drawGreenRect
} from '../utils';
import * as cv from '../../../';


const image = cv.imread(getDataFilePath('Lenna.png'));

const faceClassifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_DEFAULT);
const eyeClassifier = new cv.CascadeClassifier(cv.HAAR_EYE);

// detect faces
const faceResult = faceClassifier.detectMultiScale(image.bgrToGray());

if (!faceResult.objects.length) {
  throw new Error('No faces detected!');
}

const sortByNumDetections = (result: { numDetections: number[] }): number[] => result.numDetections
  .map((num, idx) => ({ num, idx }))
  .sort(((n0, n1) => n1.num - n0.num))
  .map(({ idx }) => idx);

// get best result
const faceRect = faceResult.objects[sortByNumDetections(faceResult)[0]];
console.log('faceRects:', faceResult.objects);
console.log('confidences:', faceResult.numDetections);

// detect eyes
const faceRegion = image.getRegion(faceRect);
const eyeResult = eyeClassifier.detectMultiScale(faceRegion);
console.log('eyeRects:', eyeResult.objects);
console.log('confidences:', eyeResult.numDetections);

// get best result
const eyeRects = sortByNumDetections(eyeResult)
  .slice(0, 2)
  .map(idx => eyeResult.objects[idx]);

// draw face detection
drawBlueRect(image, faceRect);

// draw eyes detection in face region
eyeRects.forEach(eyeRect => drawGreenRect(faceRegion, eyeRect));

cv.imshowWait('face detection', image);
