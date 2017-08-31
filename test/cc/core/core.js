import cv from 'dut';
import { expect } from 'chai';

describe('core', () => {
  describe('partition', () => {
    describe('Point2 input', () => {
      it('should return labels and numLabels', () => {
        const { labels, numLabels } = cv.partition([new cv.Point(0, 0), new cv.Point(0, 0)], () => true);

        expect(labels).to.be.an('array').lengthOf(2);
        expect(numLabels).be.a('number');
      });

      it('should assign every point to same cluster', () => {
        const num = 5;
        const pts = Array(num).fill(0).map(() => new cv.Point(0, 0));
        const { labels, numLabels } = cv.partition(pts, () => true);

        expect(numLabels).to.equal(1);
        expect(new Set(labels).size).to.equal(1);
      });

      it('should assign every point to different cluster', () => {
        const num = 5;
        const pts = Array(num).fill(0).map(() => new cv.Point(0, 0));
        const { labels, numLabels } = cv.partition(pts, () => false);

        expect(numLabels).to.equal(num);
        expect(new Set(labels).size).to.equal(num);
      });
    });

  });
});
