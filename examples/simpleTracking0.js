const cv = require('../');

const cap = new cv.VideoCapture('../data/horses.mp4');

let done = false;
while (!done) {
  let frame = cap.read();
  if (frame.empty) {
    cap.reset();
    frame = cap.read();
  }
  const frameHLS = frame.cvtColor({ code: cv.cvTypes.colorConversionCodes.COLOR_BGR2HLS });
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
      size: new cv.Size(5, 5)
    }),
    iterations: 4
  });
  const { CC_STAT_AREA } = cv.cvTypes.connectedComponentsTypes;
  const {
    centroids,
    stats
  } = dilated.connectedComponentsWithStats();

  // pretend label 0 is background
  const sizeTh = 500;
  for (let label = 1; label < centroids.rows; label += 1) {
    const [cx, cy] = [centroids.at(label, 0), centroids.at(label, 1)];
    const size = stats.at(label, CC_STAT_AREA);
    if (size > sizeTh) {
      frame.drawCircle({
        center: new cv.Point(cx, cy),
        radius: 20,
        color: new cv.Vec(255, 0, 0),
        thickness: 2
      });
    }
  }

  cv.imshow('rangeMask', rangeMask);
  cv.imshow('frame', frame);
  const key = cv.waitKey(100);
  done = key !== 255;
}

console.log('Key pressed, exiting.');
