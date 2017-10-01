const cv = global.dut;
const { funcShouldRequireArgs } = global.utils;
const { expect } = require('chai');

describe('core', () => {
  describe('partition', () => {
    describe('Point2 input', () => {
      funcShouldRequireArgs(() => cv.partition());

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

  describe('kmeans', () => {
    funcShouldRequireArgs(() => cv.kmeans());
    const points = [
      [0, 0], [1000, 900], [-1000, -900], [-1100, -1000], [1100, 1000], [10, 10]
    ].map(([x, y]) => new cv.Point(x, y));
    const k = 3;
    const termCriteria = new cv.TermCriteria(cv.termCriteria.COUNT, 100, 0.8);
    const attempts = 10;
    const flags = cv.KMEANS_RANDOM_CENTERS;

    it('should return labels and centers', () => {
      const ret = cv.kmeans(points, k, termCriteria, attempts, flags);

      expect(ret).to.have.property('labels').to.be.an('array').lengthOf(6);
      expect(ret).to.have.property('centers').to.be.an('array').lengthOf(k);
    });

    it('should return correct labels', () => {
      const ret = cv.kmeans(points, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[1];
      const l2 = ret.labels[2];
      expect(ret.labels).to.have.ordered.members([l0, l1, l2, l2, l1, l0]);
    });

    it('should return correct centers', () => {
      const ret = cv.kmeans(points, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[1];
      const l2 = ret.labels[2];
      expect(ret.centers[l0].x).to.equal(5);
      expect(ret.centers[l0].y).to.equal(5);
      expect(ret.centers[l1].x).to.equal(1050);
      expect(ret.centers[l1].y).to.equal(950);
      expect(ret.centers[l2].x).to.equal(-1050);
      expect(ret.centers[l2].y).to.equal(-950);
    });
  });
});
