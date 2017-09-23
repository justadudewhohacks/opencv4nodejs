const cv = require('../');

const image = cv.imread('../data/Lenna.png');
const faceClassifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_DEFAULT);
const eyeClassifier = new cv.CascadeClassifier(cv.HAAR_EYE);

// detect faces
const faceResult = faceClassifier.detectMultiScale(image.bgrToGray());

if (!faceResult.objects.length) {
  throw new Error('No faces detected!');
}

const sortByNumDetections = result => result.numDetections
  .map((num, idx) => ({ num, idx }))
  .sort(((n0, n1) => n1.num - n0.num))
  .map(({ idx }) => idx);

// get best result
const faceRect = faceResult.objects[sortByNumDetections(faceResult)[0]];

// detect eyes
const faceRegion = image.getRegion(faceRect);
const eyeResult = eyeClassifier.detectMultiScale(faceRegion);

// draw face detection
const blue = new cv.Vec(255, 0, 0);
const thickness = 2;
image.drawRectangle(
  new cv.Point(faceRect.x, faceRect.y),
  new cv.Point(faceRect.x + faceRect.width, faceRect.y + faceRect.height),
  blue,
  cv.LINE_8,
  thickness
);

// get best result
const eyeRects = sortByNumDetections(eyeResult).slice(0, 2).map(idx => eyeResult.objects[idx]);

// draw eyes detection in face region
const green = new cv.Vec(0, 255, 0);
eyeRects.forEach((rect) => {
  faceRegion.drawRectangle(
    new cv.Point(rect.x, rect.y),
    new cv.Point(rect.x + rect.width, rect.y + rect.height),
    green,
    { thickness }
  );
});

cv.imshowWait('face detection', image);
