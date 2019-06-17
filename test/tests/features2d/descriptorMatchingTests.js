const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    cvVersionLowerThan
  } = utils;

  let kazeKps;
  let kazeDesc;
  let orbKps;
  let orbDesc;
  before(() => {
    const kaze = new cv.KAZEDetector();
    kazeKps = kaze.detect(getTestImg());
    kazeDesc = kaze.compute(getTestImg(), kazeKps);

    const orb = new cv.ORBDetector();
    orbKps = orb.detect(getTestImg());
    orbDesc = orb.compute(getTestImg(), orbKps);
  });

  describe('matchFlannBased', () => {
    it('sync', () => {
      const matches = cv.matchFlannBased(kazeDesc, kazeDesc);
      expect(kazeKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(kazeKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('async', (done) => {
      cv.matchFlannBasedAsync(kazeDesc, kazeDesc, (err, matches) => {
        expect(kazeKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(kazeKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });

  describe('matchBruteForce', () => {
    it('sync', () => {
      const matches = cv.matchBruteForce(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('async', (done) => {
      cv.matchBruteForceAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });

  describe('matchBruteForceL1', () => {
    it('sync', () => {
      const matches = cv.matchBruteForceL1(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('async', (done) => {
      cv.matchBruteForceL1Async(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });

  describe('matchBruteForceHamming', () => {
    it('sync', () => {
      const matches = cv.matchBruteForceHamming(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('async', (done) => {
      cv.matchBruteForceHammingAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });

  (cvVersionLowerThan(3, 2, 0) ? describe.skip : describe)('matchBruteForceHammingLut', () => {
    it('matchBruteForceHammingLut', () => {
      const matches = cv.matchBruteForceHammingLut(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchBruteForceHammingLutAsync', (done) => {
      cv.matchBruteForceHammingAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });

  (cvVersionLowerThan(3, 2, 0) ? describe.skip : describe)('matchBruteForceSL2', () => {
    it('matchBruteForceSL2', () => {
      const matches = cv.matchBruteForceSL2(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchBruteForceSL2Async', (done) => {
      cv.matchBruteForceSL2Async(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });
};
