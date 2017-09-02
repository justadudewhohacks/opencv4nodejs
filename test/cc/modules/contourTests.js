import cv from 'dut';
import { expect } from 'chai';

module.exports = () => {
  describe('contour', () => {
    // apparently minor < 2 does not consider image borders
    const contoursData = [
      [0, 0, 0, 0, 0, 0, 0, 0, 0],
      [0, 1, 1, 1, 0, 0, 1, 0, 0],
      [0, 1, 0, 1, 0, 1, 0, 1, 0],
      [0, 1, 0, 1, 0, 0, 1, 0, 0],
      [0, 1, 0, 1, 0, 0, 0, 0, 0],
      [0, 1, 0, 1, 0, 1, 1, 1, 0],
      [0, 1, 0, 1, 0, 1, 0, 1, 0],
      [0, 1, 1, 1, 0, 1, 1, 1, 0],
      [0, 0, 0, 0, 0, 0, 0, 0, 0]
    ];
    const convexityDefectsData = [
      [0, 0, 0, 0, 0, 0, 0, 0, 0],
      [0, 1, 1, 1, 0, 1, 1, 1, 0],
      [0, 1, 0, 1, 0, 1, 0, 1, 0],
      [0, 1, 0, 1, 1, 1, 0, 1, 0],
      [0, 1, 0, 0, 0, 0, 0, 1, 0],
      [0, 1, 0, 1, 1, 1, 0, 1, 0],
      [0, 1, 0, 1, 0, 1, 0, 1, 0],
      [0, 1, 1, 1, 0, 1, 1, 1, 0],
      [0, 0, 0, 0, 0, 0, 0, 0, 0]
    ];
    const contoursImg = new cv.Mat(contoursData, cv.cvTypes.CV_8U);
    const convexityDefectsImg = new cv.Mat(convexityDefectsData, cv.cvTypes.CV_8U);

    let contours;
    let convexityDefectsContours;
    let leftmostContour;
    let rightBottomContour;

    before(() => {
      const opts = {
        mode: cv.cvTypes.retrievalModes.RETR_EXTERNAL,
        method: cv.cvTypes.contourApproximationModes.CHAIN_APPROX_NONE
      };
      contours = contoursImg.findContours(opts);
      convexityDefectsContours = convexityDefectsImg.findContours(opts);
      const sortedByArea = contours.sort((c0, c1) => c1.area - c0.area);
      leftmostContour = sortedByArea[0];
      rightBottomContour = sortedByArea[1];
    });

    describe('findContours', () => {
      it('should find contours', () => {
        expect(contours).to.be.an('array').lengthOf(3);
      });

      it('should have contour properties', () => {
        contours.forEach((contour) => {
          expect(contour).to.have.property('hierarchy');
          expect(contour).to.have.property('numPoints');
          expect(contour).to.have.property('area');
          expect(contour).to.have.property('isConvex');
        });
      });

      it('should calculate correct area', () => {
        expect(contours.some(c => c.area === 2)).to.be.true;
        expect(contours.some(c => c.area === 4)).to.be.true;
        expect(contours.some(c => c.area === 12)).to.be.true;
      });

      it('should contain correct number of points', () => {
        expect(contours.some(c => c.numPoints === 4)).to.be.true;
        expect(contours.some(c => c.numPoints === 8)).to.be.true;
        expect(contours.some(c => c.numPoints === 16)).to.be.true;
      });
    });

    describe('approxPolyDP', () => {
      it('should approximate polygon', () => {
        const aprox = leftmostContour.approxPolyDP({
          epsilon: 0.5,
          closed: true
        });
        expect(aprox).to.be.an('array').lengthOf(4);
        aprox.forEach((pt2) => {
          expect(pt2).to.have.property('x');
          expect(pt2).to.have.property('y');
        });
      });
    });

    describe('arcLength', () => {
      it('arcLength', () => {
        const arcLengths = contours.map(c => c.arcLength(true));
        expect(arcLengths.some(arc => arc < 5.7 && arc > 5.6)).to.be.true;
        expect(arcLengths.some(arc => arc === 8)).to.be.true;
        expect(arcLengths.some(arc => arc === 16)).to.be.true;
      });
    });

    describe('convexHull', () => {
      it('should return convexHull points', () => {
        const hull = rightBottomContour.convexHull();
        expect(hull).to.have.property('getPoints').to.be.a('function');
        const hullPoints = hull.getPoints();
        expect(hullPoints).to.be.an('array').lengthOf(4);
        hullPoints.forEach((pt2) => {
          expect(pt2).to.have.property('x');
          expect(pt2).to.have.property('y');
        });
      });

      it('should return convexHull indices', () => {
        const hullIndices = rightBottomContour.convexHull({
          returnPoints: false
        });
        expect(hullIndices).to.be.an('array').lengthOf(4);
        hullIndices.forEach(ind => expect(ind).to.be.a('number'));
      });
    });

    describe('convexityDefects', () => {
      it('should return convexityDefects', () => {
        const hullIndices = convexityDefectsContours[0].convexHull({
          returnPoints: false
        });
        const defects = convexityDefectsContours[0].convexityDefects(hullIndices);
        // TODO figure out whats wrong with defects in 3.0, 3.1
        if (cv.version.minor > 1) {
          expect(defects).to.be.an('array').lengthOf(2);
        }
        defects.forEach((vec4) => {
          expect(vec4).to.have.property('w');
          expect(vec4).to.have.property('x');
          expect(vec4).to.have.property('y');
          expect(vec4).to.have.property('z');
        });
      });
    });

    describe('boundingRect', () => {
      it('should return boundingRect', () => {
        const rect = rightBottomContour.boundingRect();
        expect(rect).to.have.instanceOf(cv.Rect);
        expect(rect.height).to.equal(3);
        expect(rect.width).to.equal(3);
        expect(rect.x).to.equal(5);
        expect(rect.y).to.equal(5);
      });
    });

    describe('minEnclosingCircle', () => {
      it('should return minEnclosingCircle', () => {
        const circle = rightBottomContour.minEnclosingCircle();
        expect(circle).to.have.property('center');
        expect(circle).to.have.property('radius');
        expect(circle.center.x).to.equal(6);
        expect(circle.center.y).to.equal(6);
        expect(circle.radius).to.be.within(1.4, 1.5);
      });
    });

    describe('minAreaRect', () => {
      it('should return minAreaRect', () => {
        expect(rightBottomContour.minAreaRect()).to.be.instanceOf(cv.RotatedRect);
      });
    });

    // TODO min 5 points inputs cv exception
    describe('fitEllipse', () => {
      (cv.version.minor < 2 ? it.skip : it)('should return fitEllipse', () => {
        expect(rightBottomContour.fitEllipse()).to.be.instanceOf(cv.RotatedRect);
      });
    });

    describe('pointPolygonTest', () => {
      it('distance should be positive if point inside', () => {
        expect(leftmostContour.pointPolygonTest(new cv.Point(2, 2))).to.be.above(0);
      });

      it('distance should be negative if point outside', () => {
        expect(leftmostContour.pointPolygonTest(new cv.Point(5, 5))).to.be.below(0);
      });

      it('distance should be 0 if point on border', () => {
        expect(leftmostContour.pointPolygonTest(new cv.Point(1, 1))).to.equal(0);
      });
    });

    describe('matchShapes', () => {
      it('should return zero for same shapes', () => {
        const similarity = leftmostContour.matchShapes({
          contour2: leftmostContour,
          method: cv.cvTypes.shapeMatchModes.CV_CONTOURS_MATCH_I1
        });
        expect(similarity).to.equal(0);
      });

      it('should return shape similariy', () => {
        const similarity = leftmostContour.matchShapes({
          contour2: rightBottomContour,
          method: cv.cvTypes.shapeMatchModes.CV_CONTOURS_MATCH_I1
        });
        expect(similarity).not.to.equal(0);
      });
    });

    describe('moments', () => {
      let moments;

      before(() => {
        moments = leftmostContour.moments();
      });

      it('should return moments', () => {
        expect(moments).to.be.instanceOf(cv.Moments);
      });

      it('should return hu moments', () => {
        const huMoments = moments.huMoments();
        expect(huMoments).to.be.an('array').lengthOf(7);
      });
    });
  });
};
