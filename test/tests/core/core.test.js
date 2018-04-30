const cv = global.dut;
const {
  funcShouldRequireArgs,
  generateAPITests,
  assertMetaData
} = global.utils;
const { expect } = require('chai');

const partitionTests = (createInstance) => {
  it('should return labels and numLabels', () => {
    const { labels, numLabels } = cv.partition([createInstance(), createInstance()], () => true);

    expect(labels).to.be.an('array').lengthOf(2);
    expect(numLabels).be.a('number');
  });

  it('should assign every point to same cluster', () => {
    const num = 5;
    const instances = Array(num).fill(0).map(() => createInstance());
    const { labels, numLabels } = cv.partition(instances, () => true);

    expect(numLabels).to.equal(1);
    expect(new Set(labels).size).to.equal(1);
  });

  it('should assign every point to different cluster', () => {
    const num = 5;
    const instances = Array(num).fill(0).map(() => createInstance());
    const { labels, numLabels } = cv.partition(instances, () => false);

    expect(numLabels).to.equal(num);
    expect(new Set(labels).size).to.equal(num);
  });
};

describe('core', () => {
  describe('getBuildInformation', () => {
    generateAPITests({
      getDut: () => cv,
      methodName: 'getBuildInformation',
      hasAsync: false,
      expectOutput: () => {}
    });
  });

  describe('partition', () => {
    funcShouldRequireArgs(() => cv.partition());

    describe('Point2 input', () => {
      partitionTests(() => new cv.Point(0, 0));
    });

    describe('Point3 input', () => {
      partitionTests(() => new cv.Point(0, 0, 0));
    });

    describe('Vec2 input', () => {
      partitionTests(() => new cv.Vec(0, 0));
    });

    describe('Vec3 input', () => {
      partitionTests(() => new cv.Vec(0, 0, 0));
    });

    describe('Vec4 input', () => {
      partitionTests(() => new cv.Vec(0, 0, 0, 0));
    });

    describe('Mat input', () => {
      partitionTests(() => new cv.Mat());
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

  describe('cartToPolar', () => {
    const x = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const y = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const angleInDegrees = true;

    const expectOutput = (res) => {
      expect(res).to.have.property('magnitude').to.be.instanceOf(cv.Mat);
      expect(res).to.have.property('angle').to.be.instanceOf(cv.Mat);
      assertMetaData(res.magnitude)(1, 3, cv.CV_32F);
      assertMetaData(res.angle)(1, 3, cv.CV_32F);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'cartToPolar',
      getRequiredArgs: () => ([
        x, y
      ]),
      getOptionalArgs: () => ([
        angleInDegrees
      ]),
      expectOutput
    });
  });

  describe('polarToCart', () => {
    const magnitude = new cv.Mat([[0, 1, 100]], cv.CV_32F);
    const angle = new cv.Mat([[0, Math.PI / 2, Math.PI]], cv.CV_32F);
    const angleInDegrees = true;

    const expectOutput = (res) => {
      expect(res).to.have.property('x').to.be.instanceOf(cv.Mat);
      expect(res).to.have.property('y').to.be.instanceOf(cv.Mat);
      assertMetaData(res.x)(1, 3, cv.CV_32F);
      assertMetaData(res.y)(1, 3, cv.CV_32F);
    };

    generateAPITests({
      getDut: () => cv,
      methodName: 'polarToCart',
      getRequiredArgs: () => ([
        magnitude, angle
      ]),
      getOptionalArgs: () => ([
        angleInDegrees
      ]),
      expectOutput
    });
  });
});
