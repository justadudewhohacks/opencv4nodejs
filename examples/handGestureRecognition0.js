const cv = require('../');
const { grabFrames } = require('./utils');

// segmenting by skin color (has to be adjusted)
const skinColorUpper = hue => new cv.Vec(hue, 0.8 * 255, 0.8 * 255);
const skinColorLower = hue => new cv.Vec(hue, 0.1 * 255, 0.1 * 255);

const makeHandMask = (img) => {
  // filter by skin color
  const imgHLS = img.cvtColor({ code: cv.cvTypes.colorConversionCodes.COLOR_BGR2HLS });
  const rangeMask = imgHLS.inRange(skinColorLower(170), skinColorUpper(180))
    .or(imgHLS.inRange(skinColorLower(0), skinColorUpper(20)));

  // remove noise
  const blurred = rangeMask.blur({
    ksize: new cv.Size(10, 10)
  });
  const thresholded = blurred.threshold({
    thresh: 200,
    maxVal: 255,
    type: cv.cvTypes.thresholdTypes.THRESH_BINARY
  });

  return thresholded;
};

const getHandContour = (handMask) => {
  const contours = handMask.findContours({
    mode: cv.cvTypes.retrievalModes.RETR_EXTERNAL,
    method: cv.cvTypes.contourApproximationModes.CHAIN_APPROX_SIMPLE
  });
  // largest contour
  return contours.sort((c0, c1) => c1.area - c0.area)[0];
};

// returns distance of two points
const ptDist = (pt1, pt2) => pt1.sub(pt2).norm();

// returns center of all points
const getCenterPt = pts => pts.reduce(
    (sum, pt) => sum.add(pt),
    new cv.Point(0, 0)
  ).div(pts.length);

// get the polygon from a contours hull such that there
// will be only a single hull point for a local neighborhood
const getRoughHull = (contour, maxDist) => {
  // get hull indices and hull points
  const hullIndices = contour.convexHull({
    returnPoints: false
  });
  const contourPoints = contour.getPoints();
  const hullPointsWithIdx = hullIndices.map(idx => ({
    pt: contourPoints[idx],
    contourIdx: idx
  }));
  const hullPoints = hullPointsWithIdx.map(ptWithIdx => ptWithIdx.pt);

  // group all points in local neighborhood
  const ptsBelongToSameCluster = (pt1, pt2) => ptDist(pt1, pt2) < maxDist;
  const { labels } = cv.partition(hullPoints, ptsBelongToSameCluster);
  const pointsByLabel = new Map();
  labels.forEach(l => pointsByLabel.set(l, []));
  hullPointsWithIdx.forEach((ptWithIdx, i) => {
    const label = labels[i];
    pointsByLabel.get(label).push(ptWithIdx);
  });

  // map points in local neighborhood to most central point
  const getMostCentralPoint = (pointGroup) => {
    // find center
    const center = getCenterPt(pointGroup.map(ptWithIdx => ptWithIdx.pt));
    // sort ascending by distance to center
    return pointGroup.sort(
      (ptWithIdx1, ptWithIdx2) => ptDist(ptWithIdx1.pt, center) - ptDist(ptWithIdx2.pt, center)
    )[0];
  };
  const pointGroups = Array.from(pointsByLabel.values());
  // return contour indeces of most central points
  return pointGroups.map(getMostCentralPoint).map(ptWithIdx => ptWithIdx.contourIdx);
};

const getHullDefectVertices = (handContour, hullIndices) => {
  const defects = handContour.convexityDefects(hullIndices);
  const handContourPoints = handContour.getPoints();
  const hullPoints = defects.map(defect => handContourPoints[defect.at(0)]);

  // get vertex points of hull point to its defect points
  const prevIdx = idx => (idx - 1 < 0 ? defects.length - 1 : idx - 1);
  const hullVertices = hullPoints.map((pt, i) => {
    const d1 = handContourPoints[defects[i].at(2)];
    const d2 = handContourPoints[defects[prevIdx(i)].at(2)];
    return { pt, d1, d2 };
  });
  return hullVertices;
};

const filterVerticesByAngle = (vertices, maxAngleDeg) =>
  vertices.filter((v) => {
    const sq = x => x * x;
    const a = v.d1.sub(v.d2).norm();
    const b = v.pt.sub(v.d1).norm();
    const c = v.pt.sub(v.d2).norm();
    const angleDeg = Math.acos(((sq(b) + sq(c)) - sq(a)) / (2 * b * c)) * (180 / Math.PI);
    return angleDeg < maxAngleDeg;
  });

// main
const delay = 20;
grabFrames('../data/hand-gesture.mp4', delay, (frame) => {
  const resizedImg = frame.resizeToMax(640);

  const handMask = makeHandMask(resizedImg);
  const handContour = getHandContour(handMask);
  if (!handContour) {
    return;
  }

  const maxPointDist = 25;
  const hullIndices = getRoughHull(handContour, maxPointDist);

  // get defect points of hull to contour and return vertices
  // of each hull point to its defect points
  const vertices = getHullDefectVertices(handContour, hullIndices);

  // fingertip points are those which have a sharp angle to its defect points
  const maxAngleDeg = 60;
  const verticesWithValidAngle = filterVerticesByAngle(vertices, maxAngleDeg);

  // get bounding box of contour to filter noisy points,
  // assume fingertips lie in upper half of the box
  const rect = handContour.boundingRect();
  const rectPt1 = new cv.Point(rect.x, rect.y);
  const rectPt2 = new cv.Point(rect.x + rect.width, rect.y + rect.height);
  const rectCenter = getCenterPt([rectPt1, rectPt2]);
  const verticesAtFingerTip = verticesWithValidAngle.filter(v => v.pt.y < rectCenter.y);

  const result = resizedImg.copy();
  // draw bounding box and center line
  resizedImg.drawContours({
    contours: [handContour],
    thickness: 2,
    color: new cv.Vec(255, 0, 0)
  });
  resizedImg.drawRectangle({
    pt1: rectPt1,
    pt2: rectPt2,
    thickness: 2,
    color: new cv.Vec(255, 0, 0)
  });
  resizedImg.drawLine({
    pt1: new cv.Point(rectPt1.x, rectCenter.y),
    pt2: new cv.Point(rectPt2.x, rectCenter.y),
    thickness: 2,
    color: new cv.Vec(255, 0, 0)
  });

  // draw points and vertices
  verticesAtFingerTip.forEach((v) => {
    if (rectCenter.y < v.pt.y) return;
    resizedImg.drawLine({
      pt1: v.pt,
      pt2: v.d1,
      thickness: 2,
      color: new cv.Vec(0, 255, 0)
    });
    resizedImg.drawLine({
      pt1: v.pt,
      pt2: v.d2,
      thickness: 2,
      color: new cv.Vec(0, 255, 0)
    });
    resizedImg.drawEllipse({
      box: new cv.RotatedRect(v.pt, new cv.Size(20, 20), 0),
      thickness: 2,
      color: new cv.Vec(0, 0, 255)
    });
    result.drawEllipse({
      box: new cv.RotatedRect(v.pt, new cv.Size(20, 20), 0),
      thickness: 2,
      color: new cv.Vec(0, 0, 255)
    });
  });

  // display detection result
  const numFingersUp = verticesAtFingerTip.length;
  result.drawRectangle({
    pt1: new cv.Point(10, 10),
    pt2: new cv.Point(70, 70),
    thickness: 2,
    color: new cv.Vec(0, 255, 0)
  });
  result.putText({
    text: numFingersUp,
    org: new cv.Point(20, 60),
    fontFace: cv.cvTypes.hersheyFonts.FONT_ITALIC,
    fontScale: 2,
    thickness: 2,
    color: new cv.Vec(0, 255, 0)
  });

  const { rows, cols } = result;
  const sideBySide = new cv.Mat(rows, cols * 2, cv.cvTypes.CV_8UC3);
  result.copyTo(sideBySide.getRegion(new cv.Rect(0, 0, cols, rows)));
  resizedImg.copyTo(sideBySide.getRegion(new cv.Rect(cols, 0, cols, rows)));

  cv.imshow('handMask', handMask);
  cv.imshow('result', sideBySide);
});
