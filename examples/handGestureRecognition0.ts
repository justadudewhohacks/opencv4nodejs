import type { Contour, Mat } from '../lib/typings/openCV';
import { Point2 } from '../lib/typings/openCV';
import cv from './utils';
import { grabFrames } from './utils';

interface PtCount {pt: Point2; contourIdx: number;}

// segmenting by skin color (has to be adjusted)
const skinColorUpper = (hue: number) => new cv.Vec3(hue, 0.8 * 255, 0.6 * 255);
const skinColorLower = (hue: number) => new cv.Vec3(hue, 0.1 * 255, 0.05 * 255);

const makeHandMask = (img: Mat) => {
  // filter by skin color
  const imgHLS = img.cvtColor(cv.COLOR_BGR2HLS);
  const rangeMask = imgHLS.inRange(skinColorLower(0), skinColorUpper(15));

  // remove noise
  const blurred = rangeMask.blur(new cv.Size(10, 10));
  const thresholded = blurred.threshold(200, 255, cv.THRESH_BINARY);

  return thresholded;
};

const getHandContour = (handMask: Mat): Contour => {
  const mode = cv.RETR_EXTERNAL;
  const method = cv.CHAIN_APPROX_SIMPLE;
  const contours = handMask.findContours(mode, method);
  // largest contour
  return contours.sort((c0, c1) => c1.area - c0.area)[0];
};

// returns distance of two points
const ptDist = (pt1: Point2, pt2: Point2) => pt1.sub(pt2).norm();

// returns center of all points
const getCenterPt = (pts: Point2[]): Point2 => pts.reduce((sum: Point2, pt: Point2) => sum.add(pt), new Point2(0, 0)).div(pts.length);

// get the polygon from a contours hull such that there
// will be only a single hull point for a local neighborhood
const getRoughHull = (contour: Contour, maxDist: number) => {
  // get hull indices and hull points
  const hullIndices = contour.convexHullIndices();
  const contourPoints = contour.getPoints();
  const hullPointsWithIdx = hullIndices.map((idx: number) => ({
    pt: contourPoints[idx],
    contourIdx: idx
  }));
  const hullPoints: Point2[] = hullPointsWithIdx.map(ptWithIdx => ptWithIdx.pt);

  // group all points in local neighborhood
  const ptsBelongToSameCluster = (pt1: Point2, pt2: Point2): boolean => ptDist(pt1, pt2) < maxDist;
  const { labels } = cv.partition(hullPoints, ptsBelongToSameCluster);
  const pointsByLabel = new Map<number, Array<PtCount>>();
  labels.forEach(l => pointsByLabel.set(l, []));
  hullPointsWithIdx.forEach((ptWithIdx, i) => {
    const label = labels[i];
    pointsByLabel.get(label).push(ptWithIdx);
  });

  // map points in local neighborhood to most central point
  const getMostCentralPoint = (pointGroup: PtCount[]) => {
    // find center
    const center: Point2 = getCenterPt(pointGroup.map(ptWithIdx => ptWithIdx.pt));
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

  // get neighbor defect points of each hull point
  const hullPointDefectNeighbors: Map<number, Array<any>> = new Map(hullIndices.map((idx: number) => [idx, []]));
  defects.forEach((defect) => {
    const startPointIdx = defect.at(0);
    const endPointIdx = defect.at(1);
    const defectPointIdx = defect.at(2);
    hullPointDefectNeighbors.get(startPointIdx).push(defectPointIdx);
    hullPointDefectNeighbors.get(endPointIdx).push(defectPointIdx);
  });

  return Array.from(hullPointDefectNeighbors.keys())
    // only consider hull points that have 2 neighbor defects
    .filter(hullIndex => hullPointDefectNeighbors.get(hullIndex).length > 1)
    // return vertex points
    .map((hullIndex: number) => {
      const defectNeighborsIdx = hullPointDefectNeighbors.get(hullIndex);
      return ({
        pt: handContourPoints[hullIndex],
        d1: handContourPoints[defectNeighborsIdx[0]],
        d2: handContourPoints[defectNeighborsIdx[1]]
      });
    });
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

const blue = new cv.Vec3(255, 0, 0);
const green = new cv.Vec3(0, 255, 0);
const red = new cv.Vec3(0, 0, 255);

// main
const delay = 20;
grabFrames('../data/hand-gesture.mp4', delay, (frame) => {
  const resizedImg: Mat = frame.resizeToMax(640);

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

  const result = resizedImg.copy();
  // draw bounding box and center line
  resizedImg.drawContours(
    [handContour],
    blue,
    { thickness: 2 }
  );

  // draw points and vertices
  verticesWithValidAngle.forEach((v) => {
    resizedImg.drawLine(
      v.pt,
      v.d1,
      { color: green, thickness: 2 }
    );
    resizedImg.drawLine(
      v.pt,
      v.d2,
      { color: green, thickness: 2 }
    );
    resizedImg.drawEllipse(
      new cv.RotatedRect(v.pt, new cv.Size(20, 20), 0),
      { color: red, thickness: 2 }
    );
    result.drawEllipse(
      new cv.RotatedRect(v.pt, new cv.Size(20, 20), 0),
      { color: red, thickness: 2 }
    );
  });

  // display detection result
  const numFingersUp = verticesWithValidAngle.length;
  result.drawRectangle(
    new cv.Point2(10, 10),
    new cv.Point2(70, 70),
    { color: green, thickness: 2 }
  );

  const fontScale = 2;
  result.putText(
    String(numFingersUp),
    new cv.Point2(20, 60),
    cv.FONT_ITALIC,
    fontScale,
    { color: green, thickness: 2 }
  );

  const { rows, cols } = result;
  const sideBySide = new cv.Mat(rows, cols * 2, cv.CV_8UC3);
  result.copyTo(sideBySide.getRegion(new cv.Rect(0, 0, cols, rows)));
  resizedImg.copyTo(sideBySide.getRegion(new cv.Rect(cols, 0, cols, rows)));

  cv.imshow('handMask', handMask);
  cv.imshow('result', sideBySide);
});
