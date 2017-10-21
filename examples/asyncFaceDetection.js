const cv = require('../');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

cv.imreadAsync('../data/got.jpg')
  .then(img => classifier.detectMultiScaleAsync(img.bgrToGray()).then(res => ({ res, img })))
  .then(({ res, img }) => {
    const { objects, numDetections } = res;
    if (!objects.length) {
      throw new Error('No faces detected!');
    }

    // draw detection
    const numDetectionsTh = 10;
    objects.forEach((rect, i) => {
      const color = new cv.Vec(255, 0, 0);
      let thickness = 2;
      if (numDetections[i] < numDetectionsTh) {
        thickness = 1;
      }

      img.drawRectangle(
        new cv.Point(rect.x, rect.y),
        new cv.Point(rect.x + rect.width, rect.y + rect.height),
        color,
        { thickness }
      );
    });

    cv.imshowWait('face detection', img);
  });

