const cv = global.dut;
const { assertPropsWithValue, generateAPITests } = global.utils;

const { expect } = require('chai');

module.exports = (getTestImg) => {
  describe('BFMatcher', () => {
    describe('constructor', () => {
      const normType = cv.NORM_L2;
      const crossCheck = true;

      it('should throw if insufficient args passed', () => {
        expect(() => new cv.BFMatcher(undefined)).to.throw();
      });

      it('should throw if bag args are passed', () => {
        expect(() => new cv.BFMatcher(normType, undefined)).to.throw();
      });

      it('should be constructable with required args', () => {
        expect(() => new cv.BFMatcher(normType)).to.not.throw();
      });

      it('should initialize with correct values', () => {
        const match = new cv.BFMatcher(normType, crossCheck);
        assertPropsWithValue(match)({ normType, crossCheck });
      });
    });

    describe('match', () => {
        let BFMatcher;

        before(() => {
            BFMatcher = new cv.BFMatcher(cv.NORM_L2, true);

            const kaze = new cv.KAZEDetector();
            kazeKps = kaze.detect(getTestImg());
            kazeDesc = kaze.compute(getTestImg(), kazeKps);
        });

        describe('matchBruteForce', () => {
            it('sync', () => {
                const matches = BFMatcher.match(kazeDesc, kazeDesc);
                expect(kazeKps.length).to.be.above(0);
                expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
            });

            it('async', (done) => {
                cv.matchBruteForceAsync(kazeDesc, kazeDesc, (err, matches) => {
                    expect(kazeKps.length).to.be.above(0);
                    expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                    matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
                    done();
                });
            });
        });
    });
  });
};
