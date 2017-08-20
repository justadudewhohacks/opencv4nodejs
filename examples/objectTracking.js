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
  const frameHLS = frame.cvtColor({ code: cv.cvTypes.colorConversionCodes.COLOR_BGR2HLS });
  cv.imshow('frameHLS', frameHLS);
  const rangeMask = frameHLS.inRange(new cv.Vec(5, 20, 100), new cv.Vec(10, 60, 165));

  const eroded = rangeMask.erode({
    kernel: cv.getStructuringElement({
      shape: cv.cvTypes.morphShapes.MORPH_ELLIPSE,
      size: new cv.Size(3, 3)
    }),
    iterations: 2
  });
  const dilated = eroded.dilate({
    kernel: cv.getStructuringElement({
      shape: cv.cvTypes.morphShapes.MORPH_ELLIPSE,
      size: new cv.Size(4, 4)
    }),
    iterations: 4
  });
  cv.imshow('rangeMask', rangeMask);
  cv.imshow('dilated', dilated);
  cv.imshowWait('frame', frame);
};