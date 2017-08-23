const cv = require('../');

exports.grabFrames = (videoFile, delay, onFrame) => {
  const cap = new cv.VideoCapture(videoFile);
  let done = false;
  while (!done) {
    let frame = cap.read();
    if (frame.empty) {
      cap.reset();
      frame = cap.read();
    }
    onFrame(frame);

    const key = cv.waitKey(delay);
    done = key !== 255;
  }
  console.log('Key pressed, exiting.');
};

exports.drawRectAroundBlobs = (binaryImg, dstImg, minPxSize, fixedRectWidth) => {
  const {
    CC_STAT_LEFT,
    CC_STAT_TOP,
    CC_STAT_WIDTH,
    CC_STAT_HEIGHT,
    CC_STAT_AREA
  } = cv.cvTypes.connectedComponentsTypes;

  const {
    centroids,
    stats
  } = binaryImg.connectedComponentsWithStats();

  // pretend label 0 is background
  for (let label = 1; label < centroids.rows; label += 1) {
    const [x1, y1] = [stats.at(label, CC_STAT_LEFT), stats.at(label, CC_STAT_TOP)];
    const [x2, y2] = [
      x1 + (fixedRectWidth || stats.at(label, CC_STAT_WIDTH)),
      y1 + (fixedRectWidth || stats.at(label, CC_STAT_HEIGHT))
    ];
    const size = stats.at(label, CC_STAT_AREA);
    if (minPxSize < size) {
      dstImg.drawRectangle({
        pt1: new cv.Point(x1, y1),
        pt2: new cv.Point(x2, y2),
        color: new cv.Vec(255, 0, 0),
        thickness: 2
      });
    }
  }
};
