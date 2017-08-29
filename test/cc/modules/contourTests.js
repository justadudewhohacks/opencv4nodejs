import cv from 'dut';
import { expect } from 'chai';

module.exports = () => {
  describe('contour', () => {
    const contoursData = [
      [1, 1, 1, 0, 0, 1, 0],
      [1, 0, 1, 0, 1, 0, 1],
      [1, 0, 1, 0, 0, 1, 0],
      [1, 0, 1, 0, 0, 0, 0],
      [1, 0, 1, 0, 1, 1, 1],
      [1, 0, 1, 0, 1, 0, 1],
      [1, 1, 1, 0, 1, 1, 1]
    ];
    const convexityDefectsData = [
      [1, 1, 1, 0, 1, 1, 1],
      [1, 0, 1, 0, 1, 0, 1],
      [1, 0, 1, 1, 1, 0, 1],
      [1, 0, 0, 0, 0, 0, 1],
      [1, 0, 1, 1, 1, 0, 1],
      [1, 0, 1, 0, 1, 0, 1],
      [1, 1, 1, 0, 1, 1, 1]
    ];
    const contoursImg = new cv.Mat(contoursData, cv.cvTypes.CV_8U);
    const convexityDefectsImg = new cv.Mat(convexityDefectsData, cv.cvTypes.CV_8U);

    let contours;
    let convexityDefectsContours;

    before(() => {
      const opts = {
        mode: cv.cvTypes.retrievalModes.RETR_EXTERNAL,
        method: cv.cvTypes.contourApproximationModes.CHAIN_APPROX_NONE
      };
      contours = contoursImg.findContours(opts);
      convexityDefectsContours = convexityDefectsImg.findContours(opts);
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
        expect(contours[0].area).to.equal(4);
        expect(contours[1].area).to.equal(2);
        expect(contours[2].area).to.equal(12);
      });

      it('should contain correct number of points', () => {
        expect(contours[0].numPoints).to.equal(8);
        expect(contours[1].numPoints).to.equal(4);
        expect(contours[2].numPoints).to.equal(16);
      });
    });

    describe('approxPolyDP', () => {
      it('should approximate polygon', () => {
        const aprox = contours[2].approxPolyDP({
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
        expect(contours[0].arcLength(true)).to.equal(8);
        expect(contours[1].arcLength(true)).to.be.within(5.6, 5.7);
        expect(contours[2].arcLength(true)).to.equal(16);
      });
    });

    describe('convexHull', () => {
      it('should return convexHull points', () => {
        const hullPoints = contours[0].convexHull();
        expect(hullPoints).to.be.an('array').lengthOf(4);
        hullPoints.forEach((pt2) => {
          expect(pt2).to.have.property('x');
          expect(pt2).to.have.property('y');
        });
      });

      it('should return convexHull indices', () => {
        const hullIndices = contours[0].convexHull({
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
        expect(defects).to.be.an('array').lengthOf(2);
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
        const rect = contours[0].boundingRect();
        expect(rect).to.have.instanceOf(cv.Rect);
        expect(rect.height).to.equal(3);
        expect(rect.width).to.equal(3);
        expect(rect.x).to.equal(4);
        expect(rect.y).to.equal(4);
      });
    });

    describe('minEnclosingCircle', () => {
      it('should return minEnclosingCircle', () => {
        const circle = contours[0].minEnclosingCircle();
        expect(circle).to.have.property('center');
        expect(circle).to.have.property('radius');
        expect(circle.center.x).to.equal(5);
        expect(circle.center.y).to.equal(5);
        expect(circle.radius).to.be.within(1.4, 1.5);
      });
    });

    describe('minAreaRect', () => {
      it('should return minAreaRect', () => {
        expect(contours[0].minAreaRect()).to.be.instanceOf(cv.RotatedRect);
      });
    });

    describe('fitEllipse', () => {
      it('should return fitEllipse', () => {
        expect(contours[0].fitEllipse()).to.be.instanceOf(cv.RotatedRect);
      });
    });

    describe('pointPolygonTest', () => {
      it('distance should be positive if point inside', () => {
        expect(contours[2].pointPolygonTest(new cv.Point(1, 1))).to.be.above(0);
      });

      it('distance should be negative if point outside', () => {
        expect(contours[2].pointPolygonTest(new cv.Point(4, 4))).to.be.below(0);
      });

      it('distance should be 0 if point on border', () => {
        expect(contours[2].pointPolygonTest(new cv.Point(0, 0))).to.equal(0);
      });
    });

    describe('matchShapes', () => {
      it('should return zero for same shapes', () => {
        const similarity = contours[2].matchShapes({
          contour2: contours[2],
          method: cv.cvTypes.shapeMatchModes.CV_CONTOURS_MATCH_I1
        });
        expect(similarity).to.equal(0);
      });

      it('should return shape similariy', () => {
        const similarity = contours[2].matchShapes({
          contour2: contours[0],
          method: cv.cvTypes.shapeMatchModes.CV_CONTOURS_MATCH_I1
        });
        expect(similarity).not.to.equal(0);
      });
    });

    describe.only('moments', () => {
      let moments;

      before(() => {
        moments = contours[2].moments();
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
