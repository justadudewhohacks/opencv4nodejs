import { expect } from 'chai';
import { assertPropsWithValue } from './testUtils';

// TODO test return values of compute, detect

const detectorTests = (defaults, customProps, Detector) => {
  it('should use default values for empty args', () => {
    assertPropsWithValue(new Detector())(defaults);
  });

  it('should use default values for empty object', () => {
    assertPropsWithValue(new Detector({}))(defaults);
  });

  it('should be constructable with custom props', () => {
    assertPropsWithValue(new Detector(customProps))(customProps);
  });

  it('should have function detect', () => {
    expect(new Detector()).to.have.property('detect').to.be.a('function');
  });

  it('should have function compute', () => {
    expect(new Detector()).to.have.property('compute').to.be.a('function');
  });
};

module.exports = {
  detectorTests
};
