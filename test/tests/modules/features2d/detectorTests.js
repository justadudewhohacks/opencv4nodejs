const cv = global.dut;
const { assert, expect } = require('chai');

const {
  assertError,
  assertPropsWithValue,
  asyncFuncShouldRequireArgs
} = global.utils;

module.exports = (getTestImg, defaults, customProps, Detector, implementsCompute = true) => {
  let testImg;

  before(() => {
    testImg = getTestImg();
  });

  describe('constructor', () => {
    it('should use default values if no args', () => {
      assertPropsWithValue(new Detector())(defaults);
    });

    it('should use default values if empty args', () => {
      assertPropsWithValue(new Detector({}))(defaults);
    });

    it('should be constructable with custom props', () => {
      const props = {};
      customProps.args.forEach((arg, i) => {
        props[arg] = customProps.values[i];
      });
      /* eslint-disable new-parens */
      const detector = new (Detector.bind.apply(Detector, [null].concat(customProps.values)));
      assertPropsWithValue(detector)(props);
    });

    it('should be constructable with custom props object', () => {
      const props = {};
      customProps.args.forEach((arg, i) => {
        props[arg] = customProps.values[i];
      });
      assertPropsWithValue(new Detector(props))(props);
    });

    it('should have function detect', () => {
      expect(new Detector()).to.have.property('detect').to.be.a('function');
    });

    it('should have function compute', () => {
      expect(new Detector()).to.have.property('compute').to.be.a('function');
    });
  });

  describe('detect and compute', () => {
    let keyPoints;
    before(() => {
      keyPoints = (new Detector()).detect(testImg);
    });

    describe('detect', () => {
      describe('sync', () => {
        it('should throw if no args', () => {
          assertError(() => (new Detector()).detect(), 'expected arg 0 to be instance of: Mat');
        });

        it('should return an array of KeyPoints', () => {
          expect(keyPoints).to.be.a('array');
          assert(keyPoints.length > 0, 'no KeyPoints detected');
          keyPoints.forEach(kp => assert(kp instanceof cv.KeyPoint));
        });
      });

      describe('async', () => {
        it('should throw if no args', () => {
          asyncFuncShouldRequireArgs(() => new Detector().detectAsync());
        });

        it('should return an array of KeyPoints', (done) => {
          (new Detector()).detectAsync(testImg, (err, kps) => {
            expect(kps).to.be.a('array');
            assert(kps.length > 0, 'no KeyPoints detected');
            kps.forEach(kp => assert(kp instanceof cv.KeyPoint));
            done();
          });
        });
      });
    });

    if (implementsCompute) {
      describe('compute', () => {
        describe('sync', () => {
          it('should throw if no args', () => {
            assertError(() => (new Detector()).compute(), 'expected arg 0 to be instance of: Mat');
          });

          it('should return a Mat with descriptors for each KeyPoint', () => {
            const desc = (new Detector(defaults)).compute(testImg, keyPoints);
            assertPropsWithValue(desc)({ rows: keyPoints.length });
          });
        });

        describe('async', () => {
          it('should throw if no args', () => {
            asyncFuncShouldRequireArgs(() => new Detector().computeAsync());
          });

          it('should return a Mat with descriptors for each KeyPoint', (done) => {
            (new Detector()).computeAsync(testImg, keyPoints, (err, desc) => {
              assertPropsWithValue(desc)({ rows: keyPoints.length });
              done();
            });
          });
        });
      });
    }
  });
};
