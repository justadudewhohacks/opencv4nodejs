const cv = global.dut;
const { assert, expect } = require('chai');

const {
  assertPropsWithValue,
  generateAPITests
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

  describe('detect', () => {
    generateAPITests({
      getDut,
      methodName: 'detect',
      methodNameSpace: 'FeatureDetector',
      getRequiredArgs: () => ([
        testImg
      ]),
      expectOutput: (keyPoints) => {
        expect(keyPoints).to.be.a('array');
        assert(keyPoints.length > 0, 'no KeyPoints detected');
        keyPoints.forEach(kp => assert(kp instanceof cv.KeyPoint));
      }
    });
  });

  if (implementsCompute) {
    describe('compute', () => {
      let dut;
      let keyPoints;
      before(() => {
        dut = getDut();
        keyPoints = dut.detect(testImg);
      });
      generateAPITests({
        getDut,
        methodName: 'compute',
        methodNameSpace: 'FeatureDetector',
        getRequiredArgs: () => ([
          testImg,
          keyPoints
        ]),
        expectOutput: (desc) => {
          assertPropsWithValue(desc)({ rows: keyPoints.length });
        }
      });
    });
  }
};
