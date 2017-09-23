const opencv = global.dut;
const { assert, expect } = require('chai');

const { assertError, assertPropsWithValue, readTestImage } = global.utils;

var Test = class {
  constructor(a, b, c) {
    console.log('a', a)
    console.log('b', b)
    console.log('c', c)
  }
};

exports.detectorTests = (defaults, customProps, Detector, implementsCompute = true) => {
  let testImg;
  let keyPoints;

  before(async () => {
    testImg = readTestImage().resizeToMax(250);
    keyPoints = (new Detector()).detect(testImg);
  });

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

  describe('detect', () => {
    it('should throw if no args', () => {
      assertError(() => (new Detector()).detect(), 'expected arg 0 to be instance of: Mat');
    });

    it('should return an array of KeyPoints', () => {
      expect(keyPoints).to.be.a('array');
      assert(keyPoints.length > 0, 'no KeyPoints detected');
      keyPoints.forEach(kp => assert(kp instanceof opencv.KeyPoint));
    });
  });

  if (implementsCompute) {
    describe('compute', () => {
      it('should throw if no args', () => {
        assertError(() => (new Detector()).compute(), 'expected arg 0 to be instance of: Mat');
      });

      it('should return a Mat with descriptors for each KeyPoint', () => {
        const desc = (new Detector(defaults)).compute(testImg, keyPoints);
        assertPropsWithValue(desc)({ rows: keyPoints.length });
      });
    });
  }
};
