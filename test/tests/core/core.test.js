const cv = global.dut;
const {
  funcShouldRequireArgs,
  generateAPITests,
  assertMetaData
} = global.utils;
const { expect } = require('chai');

let asyncHooks = null

try {
  asyncHooks = require('async_hooks')
} catch (e) {
  //
}

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
    const points2 = [
      [0, 0], [1000, 900], [-1000, -900], [-1100, -1000], [1100, 1000], [10, 10]
    ].map(([x, y]) => new cv.Point(x, y));

    const k = 3;
    const termCriteria = new cv.TermCriteria(cv.termCriteria.COUNT, 100, 0.8);
    const attempts = 10;
    const flags = cv.KMEANS_RANDOM_CENTERS;

    it('should return labels and centers', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

      expect(ret).to.have.property('labels').to.be.an('array').lengthOf(6);
      expect(ret).to.have.property('centers').to.be.an('array').lengthOf(k);
    });

    it('should return correct labels', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[1];
      const l2 = ret.labels[2];
      expect(ret.labels).to.have.ordered.members([l0, l1, l2, l2, l1, l0]);
    });

    it('should return correct centers', () => {
      const ret = cv.kmeans(points2, k, termCriteria, attempts, flags);

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

    // related to https://github.com/justadudewhohacks/opencv4nodejs/issues/379
    const points3 = [
      [255, 0, 0], [255, 0, 0], [255, 0, 255], [255, 0, 255], [255, 255, 255]
    ].map(([x, y, z]) => new cv.Point(x, y, z));

    it('should return correct centers with Point3', () => {
      const ret = cv.kmeans(points3, k, termCriteria, attempts, flags);

      const l0 = ret.labels[0];
      const l1 = ret.labels[2];
      const l2 = ret.labels[4];
      expect(ret.centers[l0].x).to.equal(255);
      expect(ret.centers[l0].y).to.equal(0);
      expect(ret.centers[l0].z).to.equal(0);
      expect(ret.centers[l1].x).to.equal(255);
      expect(ret.centers[l1].y).to.equal(0);
      expect(ret.centers[l1].z).to.equal(255);
      expect(ret.centers[l2].x).to.equal(255);
      expect(ret.centers[l2].y).to.equal(255);
      expect(ret.centers[l2].y).to.equal(255);
    });
    it('should raise error for invalid type', () => {
      const points3 = [
        [255, 0, 0], [255, 0, 0], [255, 0, 255], [255, 0, 255], [255, 255, 255]
      ].map(([x, y, z]) => new cv.Vec(x, y, z));

      let err;

      try {
        cv.kmeans(points3, k, termCriteria, attempts, flags);
      } catch(e){
        err = e;
      }

      expect(err.message).to.equal("Core::Kmeans - expected arg0 to be an Array of Points");
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

  describe('getNumThreads', () => {
    it('should return the number of threads that used by OpenCV', () => {
      expect(cv.getNumThreads()).to.be.an('number');
    });
  });

  describe('setNumThreads', () => {
    it('should try to set the number of threads'
        + ' that used by OpenCV', () => {
      const number = 2;
      cv.setNumThreads(number);
      // OpenCV will **try** to set the number of threads for the
      // next parallel region so that `cv.getNumThreads()` don't react
      // to this immediately.
      // expect(cv.getNumThreads()).to.be.equal(number);
    });

    it('should throw when the argument is not integer', () => {
      let err;

      const expectError = (fn, msg) => {
        try {
          fn();
        } catch (e) {
          err = e;
        }

        expect(err.message).to.be
          .equal(msg);
      };

      expectError(() => cv.setNumThreads('hello'),
        'Core::SetNumThreads expected arg0 to an int');
      expectError(() => cv.setNumThreads(1.1),
        'Core::SetNumThreads expected arg0 to an int');
    });
  });

  describe('GetThreadNum', () => {
    it('should returns the index of the currently executed thread', () => {
      expect(cv.getThreadNum()).to.be.an('number');
    });
  });

  describe('class constructor call', () => {
    it('should throw errors if we call a constructor without "new"', () => {
      let err;

      try {
        cv.Mat();
      } catch (e) {
        err = e;
      }

      expect(err.message).to.be.equal(
        'Mat::New -  expect to be called with "new"');
    });
  });

  if (asyncHooks && global.utils.getNodeMajorVersion() > 8) {
    describe('async_hooks', () => {
      it('should trigger `init` callback in async_hooks', () => {
        let typeFound = false
        const hook = asyncHooks.createHook({
          init: (asyncId, type, triggerAsyncId, resource) => {
            if (type.indexOf('opencv4nodejs') === 0) {
              typeFound = true
              hook.disable()
            }
          },
        })
        hook.enable()

        const createInstance = () => new cv.Point(0, 0)
        const num = 5;
        const instances = Array(num).fill(0).map(() => createInstance());
        const { labels, numLabels } = cv.partition(instances, () => true);
        expect(typeFound).to.be.equal(true)
      })
    })
  }
});
