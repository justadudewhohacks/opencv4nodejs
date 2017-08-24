const cv = require('../');

const { haarCascades } = cv.cvTypes;

const image = cv.imread('../data/got.jpg');
const classifier = new cv.CascadeClassifier(haarCascades.HAAR_FRONTALFACE_ALT2);
const { objects, numDetections } = classifier.detectMultiScale({ image: image.bgrToGray() });

const numDetectionsTh = 10;
objects.forEach((rect, i) => {
  let thickness = 2;
  if (numDetections[i] < numDetectionsTh) {
    thickness = 1;
  }
  image.drawRectangle({
    pt1: new cv.Point(rect.x, rect.y),
    pt2: new cv.Point(rect.x + rect.width, rect.y + rect.height),
    color: new cv.Vec(255, 0, 0),
    thickness
  });
});

cv.imshowWait('face detection', image);
