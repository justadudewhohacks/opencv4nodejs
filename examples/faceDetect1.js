const cv = require('../');

const { haarCascades } = cv.cvTypes;

const image = cv.imread('../data/Lenna.png');
const faceClassifier = new cv.CascadeClassifier(haarCascades.HAAR_FRONTALFACE_DEFAULT);
const eyeClassifier = new cv.CascadeClassifier(haarCascades.HAAR_EYE);

// detect faces
const faceResult = faceClassifier.detectMultiScale({ image: image.bgrToGray() });

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
const eyeResult = eyeClassifier.detectMultiScale({ image: faceRegion });

// draw face detection
image.drawRectangle({
  pt1: new cv.Point(faceRect.x, faceRect.y),
  pt2: new cv.Point(faceRect.x + faceRect.width, faceRect.y + faceRect.height),
  color: new cv.Vec(255, 0, 0),
  thickness: 2
});

// get best result
const eyeRects = sortByNumDetections(eyeResult).slice(0, 2).map(idx => eyeResult.objects[idx]);

// draw eyes detection in face region
eyeRects.forEach((rect) => {
  faceRegion.drawRectangle({
    pt1: new cv.Point(rect.x, rect.y),
    pt2: new cv.Point(rect.x + rect.width, rect.y + rect.height),
    color: new cv.Vec(0, 255, 0),
    thickness: 2
  });
});

cv.imshowWait('face detection', image);
