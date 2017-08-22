const cv = require('../');

const cap = new cv.VideoCapture('../data/traffic.mp4');

const bgSubtractor = new cv.BackgroundSubtractorMOG2();
let done = false;
while (!done) {
  let frame = cap.read();
  if (frame.empty) {
    cap.reset();
    frame = cap.read();
  }


  const foreGroundMask = bgSubtractor.apply(frame);


  const eroded = foreGroundMask.erode({
    kernel: cv.getStructuringElement({
      shape: cv.cvTypes.morphShapes.MORPH_ELLIPSE,
      size: new cv.Size(3, 3)
    }),
    iterations: 2
  });
  const blurred = eroded.blur({
    ksize: new cv.Size(6, 6)
  });
  const dilated = blurred.dilate({
    kernel: cv.getStructuringElement({
      shape: cv.cvTypes.morphShapes.MORPH_ELLIPSE,
      size: new cv.Size(3, 3)
    }),
    iterations: 2
  });
  const thresholded2 = dilated.threshold({
    thresh: 0,
    maxVal: 255,
    type: cv.cvTypes.thresholdTypes.THRESH_BINARY
  });
  cv.imshow('foreGroundMask', foreGroundMask);
  //cv.imshow('thresholded', thresholded);
  cv.imshow('blurred', blurred);
  cv.imshow('eroded', eroded);
  cv.imshow('thresholded2', thresholded2);


  const { CC_STAT_AREA } = cv.cvTypes.connectedComponentsTypes;
  const {
    centroids,
    stats
  } = thresholded2.connectedComponentsWithStats();

  // pretend label 0 is background
  const sizeTh = 500;
  for (let label = 1; label < centroids.rows; label += 1) {
    const [cx, cy] = [centroids.at(label, 0), centroids.at(label, 1)];
    const size = stats.at(label, CC_STAT_AREA);
    if (sizeTh < size) {
      frame.drawCircle({
        center: new cv.Point(cx, cy),
        radius: 20,
        color: new cv.Vec(255, 0, 0),
        thickness: 2
      });
    }
  }

  cv.imshow('frame', frame);
  const key = cv.waitKey(250);
  done = key !== 255;
}

console.log('Key pressed, exiting.');
