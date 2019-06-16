const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

    const {
        assertPropsWithValue,
        generateAPITests
    } = utils;

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

    describe('crossCheck match', () => {
        let BFMatcher;
        let crossCheck = true;

        let kazeKps;
        let kazeDesc;

        before(() => {
            BFMatcher = new cv.BFMatcher(cv.NORM_L2, crossCheck);

            const kaze = new cv.KAZEDetector();
            kazeKps = kaze.detect(getTestImg());
            kazeDesc = kaze.compute(getTestImg(), kazeKps);
        });

        describe('match', () => {
            it('sync', () => {
                const matches = BFMatcher.match(kazeDesc, kazeDesc);
                expect(kazeKps.length).to.be.above(0);
                expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
            });

            it('async', (done) => {
                BFMatcher.matchAsync(kazeDesc, kazeDesc, (err, matches) => {
                    expect(kazeKps.length).to.be.above(0);
                    expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                    matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
                    done();
                });
            });
        });

        describe('knnMatch', () => {
            let k = 1; //k can only be 1 if crossCheck is true

            it('sync', () => {
                const matches = BFMatcher.knnMatch(kazeDesc, kazeDesc, k);
                expect(kazeKps.length).to.be.above(0);
                expect(matches).to.be.an('array').lengthOf(kazeKps.length);

                // if crossCheck is true, there can be points with no matches (empty arrays)
                const matchesKnn = matches.filter(el => el.length);
                matchesKnn.forEach(
                    match => (
                        expect(match).to.be.an('array').lengthOf(k)
                        &&
                        expect(match[0]).instanceOf(cv.DescriptorMatch)
                    )
                );
            });

            it('async', (done) => {
                BFMatcher.knnMatchAsync(kazeDesc, kazeDesc, k, (err, matches) => {
                    expect(kazeKps.length).to.be.above(0);
                    expect(matches).to.be.an('array').lengthOf(kazeKps.length);

                    // if crossCheck is true, there can be points with no matches (empty arrays)
                    const matchesKnn = matches.filter(el => el.length);
                    matchesKnn.forEach(
                        match => (
                            expect(match).to.be.an('array').lengthOf(k)
                            &&
                            expect(match[0]).instanceOf(cv.DescriptorMatch)
                        )
                    );
                    done();
                });
            });
        });
    });

    describe('no crossCheck match', () => {
        let BFMatcher;
        let crossCheck = false;

        let kazeKps;
        let kazeDesc;

        before(() => {
            BFMatcher = new cv.BFMatcher(cv.NORM_L2, crossCheck);

            const kaze = new cv.KAZEDetector();
            kazeKps = kaze.detect(getTestImg());
            kazeDesc = kaze.compute(getTestImg(), kazeKps);
        });

        describe('match', () => {
            it('sync', () => {
                const matches = BFMatcher.match(kazeDesc, kazeDesc);
                expect(kazeKps.length).to.be.above(0);
                expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
            });

            it('async', (done) => {
                BFMatcher.matchAsync(kazeDesc, kazeDesc, (err, matches) => {
                    expect(kazeKps.length).to.be.above(0);
                    expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                    matches.forEach(match => expect(match).instanceOf(cv.DescriptorMatch));
                    done();
                });
            });
        });

        describe('knnMatch', () => {
            let k = 5; //crossCheck off so k can be larger.

            it('sync', () => {
                const matches = BFMatcher.knnMatch(kazeDesc, kazeDesc, k);
                expect(kazeKps.length).to.be.above(0);
                expect(matches).to.be.an('array').lengthOf(kazeKps.length);

                matches.forEach(
                    match => (
                        expect(match).to.be.an('array').lengthOf(k)
                        &&
                        expect(match[0]).instanceOf(cv.DescriptorMatch)
                    )
                );
            });

            it('async', (done) => {
                BFMatcher.knnMatchAsync(kazeDesc, kazeDesc, k, (err, matches) => {
                    expect(kazeKps.length).to.be.above(0);
                    expect(matches).to.be.an('array').lengthOf(kazeKps.length);
                    matches.forEach(
                        match => (
                            expect(match).to.be.an('array').lengthOf(k)
                            &&
                            expect(match[0]).instanceOf(cv.DescriptorMatch)
                        )
                    );
                    done();
                });
            });
        });
    });
};
