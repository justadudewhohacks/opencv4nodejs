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

  const getDut = () => (typeof Detector === 'function' ? new Detector() : Detector);

  describe('constructor', () => {
    if (defaults) {
      it('should use default values if no args', () => {
        assertPropsWithValue(new Detector())(defaults);
      });

      it('should use default values if empty args', () => {
        assertPropsWithValue(new Detector({}))(defaults);
      });
    }

    if (customProps) {
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
    }

    it('should have function detect', () => {
      const detector = getDut();
      expect(detector).to.have.property('detect').to.be.a('function');
    });

    it('should have function compute', () => {
      const detector = getDut();
      expect(detector).to.have.property('compute').to.be.a('function');
    });
  });

  describe('detect and compute', () => {
    let dut;
    let keyPoints;
    before(() => {
      dut = getDut();
      keyPoints = dut.detect(testImg);
    });

    describe('detect', () => {
      describe('sync', () => {
        it('should throw if no args', () => {
          assertError(() => dut.detect(), 'expected arg 0 to be instance of: Mat');
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
          dut.detectAsync(testImg, (err, kps) => {
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
            assertError(() => dut.compute(), 'expected arg 0 to be instance of: Mat');
          });

          it('should return a Mat with descriptors for each KeyPoint', () => {
            const desc = dut.compute(testImg, keyPoints);
            assertPropsWithValue(desc)({ rows: keyPoints.length });
          });
        });

        describe('async', () => {
          it('should throw if no args', () => {
            asyncFuncShouldRequireArgs(() => new Detector().computeAsync());
          });

          it('should return a Mat with descriptors for each KeyPoint', (done) => {
            dut.computeAsync(testImg, keyPoints, (err, desc) => {
              assertPropsWithValue(desc)({ rows: keyPoints.length });
              done();
            });
          });
        });
      });
    }
  });
};
