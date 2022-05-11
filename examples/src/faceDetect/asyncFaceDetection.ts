import { cv, getResourcePath, drawBlueRect, wait4key } from '../utils';

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);
cv.imreadAsync(getResourcePath('got.jpg'))
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
            const thickness = numDetections[i] < numDetectionsTh ? 1 : 2;
            drawBlueRect(facesImg, rect, { thickness });
          });

          return facesImg;
        }
      )
      .then((facesImg) => {
        cv.imshow('face detection', facesImg);
        wait4key();
      })
    )
    .catch(err => console.error(err));

