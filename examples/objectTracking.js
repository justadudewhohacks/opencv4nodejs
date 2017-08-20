const cv = require('../');

const cap = new cv.VideoCapture('../data/horses.mp4');

// TO BE DONE

let isDone = false;
while (!isDone) {
  let frame = cap.read();
  if (frame.empty) {
    cap.reset();
    frame = cap.read();
  }
  cv.imshowWait('frame', frame);
};