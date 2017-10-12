const cv = global.dut;
const { expect } = require('chai');

module.exports = (getTestImg) => {
  describe('orbDescriptorMatching', () => {
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

    it('matchFlannBased', () => {
      const matches = cv.matchFlannBased(kazeDesc, kazeDesc);
      expect(kazeKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(kazeKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchFlannBasedAsync', (done) => {
      cv.matchFlannBasedAsync(kazeDesc, kazeDesc, (err, matches) => {
        expect(kazeKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(kazeKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });

    it('matchBruteForce', () => {
      const matches = cv.matchBruteForce(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchBruteForceAsync', (done) => {
      cv.matchBruteForceAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });

    it('matchBruteForceL1', () => {
      const matches = cv.matchBruteForceL1(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchBruteForceL1Async', (done) => {
      cv.matchBruteForceL1Async(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });

    it('matchBruteForceHamming', () => {
      const matches = cv.matchBruteForceHamming(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    it('matchBruteForceHammingAsync', (done) => {
      cv.matchBruteForceHammingAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });

    (cv.version.minor < 2 ? it.skip : it)('matchBruteForceHammingLut', () => {
      const matches = cv.matchBruteForceHammingLut(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    (cv.version.minor < 2 ? it.skip : it)('matchBruteForceHammingLutAsync', (done) => {
      cv.matchBruteForceHammingAsync(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });

    (cv.version.minor < 2 ? it.skip : it)('matchBruteForceSL2', () => {
      const matches = cv.matchBruteForceSL2(orbDesc, orbDesc);
      expect(orbKps.length).to.be.above(0);
      expect(matches).to.be.an('array').lengthOf(orbKps.length);
      matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
    });

    (cv.version.minor < 2 ? it.skip : it)('matchBruteForceSL2Async', (done) => {
      cv.matchBruteForceSL2Async(orbDesc, orbDesc, (err, matches) => {
        expect(orbKps.length).to.be.above(0);
        expect(matches).to.be.an('array').lengthOf(orbKps.length);
        matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
        done();
      });
    });
  });
};
