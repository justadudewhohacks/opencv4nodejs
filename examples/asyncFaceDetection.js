const cv = require('../');

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

cv.imreadAsync('../data/got.jpg')
  .then(img =>
    img.bgrToGrayAsync()
      .then(grayImg => classifier.detectMultiScaleAsync(grayImg))
      .then(
        (res) => {
          const { objects, numDetections } = res;
          if (!objects.length) {
            return Promise.reject('No faces detected!');
          }

          // draw detection
          const facesImg = img.copy();
          const numDetectionsTh = 10;
          objects.forEach((rect, i) => {
            const color = new cv.Vec(255, 0, 0);
            let thickness = 2;
            if (numDetections[i] < numDetectionsTh) {
              thickness = 1;
            }

            facesImg.drawRectangle(
              new cv.Point(rect.x, rect.y),
              new cv.Point(rect.x + rect.width, rect.y + rect.height),
              color,
              { thickness }
            );
          });

          return facesImg;
        }
      )
      .then((facesImg) => {
        cv.imshowWait('face detection', facesImg);
      })
    )
    .catch(err => console.error(err));

