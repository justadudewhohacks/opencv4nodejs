const cv = global.dut;
const {
  asyncFuncShouldRequireArgs,
  funcShouldRequireArgs,
  _funcShouldRequireArgs,
  readTestImage
} = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('CascadeClassifier', () => {
    const xmlHaarFile = cv.HAAR_FRONTALFACE_DEFAULT;

    describe('constructor', () => {
      funcShouldRequireArgs(() => new cv.CascadeClassifier());

      it('should be constructable with xmlFilePath', () => {
        expect(() => new cv.CascadeClassifier(xmlHaarFile)).to.not.throw();
      });

      it('should implement detectMultiScale', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScale').to.be.a('function');
      });

      it('should implement detectMultiScaleWithRejectLevels', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleWithRejectLevels').to.be.a('function');
      });

      it('should implement detectMultiScaleAsync', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleAsync').to.be.a('function');
      });

      it('should implement detectMultiScaleWithRejectLevelsAsync', () => {
        const cc = new cv.CascadeClassifier(xmlHaarFile);
        expect(cc).to.have.property('detectMultiScaleWithRejectLevelsAsync').to.be.a('function');
      });
    });

    describe('detect', () => {
      let cc;
      let testImg;

      before(() => {
        cc = new cv.CascadeClassifier(xmlHaarFile);
        testImg = readTestImage();
      });

      const scaleFactor = 1.2;
      const minNeighbors = 5;
      const flags = 0;
      const minSize = new cv.Size(50, 50);
      const maxSize = new cv.Size(250, 250);

      describe('detectMultiScale', () => {
        const expectOutput = (ret) => {
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('numDetections').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.numDetections.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        };

        describe('sync', () => {
          _funcShouldRequireArgs(() => cc.detectMultiScale());

          it('can be called if required args passed', () => {
            expectOutput(cc.detectMultiScale(testImg));
          });

          it('can be called with optional args', () => {
            expectOutput(cc.detectMultiScale(
              testImg,
              scaleFactor,
              minNeighbors,
              flags,
              minSize,
              maxSize
            ));
          });

          it('can be called with optional args object', () => {
            expectOutput(cc.detectMultiScale(
              testImg,
              {
                scaleFactor,
                minNeighbors,
                minSize,
                maxSize
              }
            ));
          });
        });

        describe('async', () => {
          const expectOutputCallbacked = done => (err, ret) => {
            expectOutput(ret);
            done();
          };

          const expectOutputPromised = done => (ret) => {
            expectOutput(ret);
            done();
          };

          asyncFuncShouldRequireArgs(() => cc.detectMultiScaleAsync());

          describe('callbacked', () => {
            it('can be called if required args passed', (done) => {
              cc.detectMultiScaleAsync(
                testImg,
                expectOutputCallbacked(done)
              );
            });

            it('can be called with optional args', (done) => {
              cc.detectMultiScaleAsync(
                testImg,
                scaleFactor,
                minNeighbors,
                flags,
                minSize,
                maxSize,
                expectOutputCallbacked(done)
              );
            });

            it('can be called with optional args object', (done) => {
              cc.detectMultiScaleAsync(
                testImg,
                {
                  scaleFactor,
                  minNeighbors,
                  minSize,
                  maxSize
                },
                expectOutputCallbacked(done)
              );
            });
          });

          describe('promised', () => {
            it('can be called if required args passed', (done) => {
              cc.detectMultiScaleAsync(
                testImg
              ).then(expectOutputPromised(done));
            });

            it('can be called with optional args', (done) => {
              cc.detectMultiScaleAsync(
                testImg,
                scaleFactor,
                minNeighbors,
                flags,
                minSize,
                maxSize
              ).then(expectOutputPromised(done));
            });

            it('can be called with optional args object', (done) => {
              cc.detectMultiScaleAsync(
                testImg,
                {
                  scaleFactor,
                  minNeighbors,
                  minSize,
                  maxSize
                }
              ).then(expectOutputPromised(done));
            });
          });
        });
      });

      // TODO: figure out why it does not terminate on v3.1
      (cv.version.minor === 1 ? describe.skip : describe)('detectMultiScaleWithRejectLevels', () => {
        const expectOutput = (ret) => {
          expect(ret).to.have.property('objects').to.be.an('array');
          expect(ret).to.have.property('rejectLevels').to.be.an('array');
          expect(ret).to.have.property('levelWeights').to.be.an('array');
          expect(ret.objects.length).to.be.above(0);
          expect(ret.rejectLevels.length).to.be.above(0);
          expect(ret.levelWeights.length).to.be.above(0);
          ret.objects.forEach(obj => expect(obj).instanceOf(cv.Rect));
        };

        describe('sync', () => {
          _funcShouldRequireArgs(() => cc.detectMultiScaleWithRejectLevels());

          it('can be called if required args passed', () => {
            expectOutput(cc.detectMultiScaleWithRejectLevels(testImg));
          });

          it('can be called with optional args', () => {
            expectOutput(cc.detectMultiScaleWithRejectLevels(
              testImg,
              scaleFactor,
              minNeighbors,
              flags,
              minSize,
              maxSize
            ));
          });

          it('can be called with optional args object', () => {
            expectOutput(cc.detectMultiScaleWithRejectLevels(
              testImg,
              {
                scaleFactor,
                minNeighbors,
                minSize,
                maxSize
              }
            ));
          });
        });

        describe('async', () => {
          const expectOutputCallbacked = done => (err, ret) => {
            expectOutput(ret);
            done();
          };

          asyncFuncShouldRequireArgs(() => cc.detectMultiScaleWithRejectLevelsAsync());

          it('can be called if required args passed', (done) => {
            cc.detectMultiScaleWithRejectLevelsAsync(testImg, expectOutputCallbacked(done));
          });

          it('can be called with optional args', (done) => {
            cc.detectMultiScaleWithRejectLevelsAsync(
              testImg,
              scaleFactor,
              minNeighbors,
              flags,
              minSize,
              maxSize,
              expectOutputCallbacked(done)
            );
          });

          it('can be called with optional args object', (done) => {
            cc.detectMultiScaleWithRejectLevelsAsync(
              testImg,
              {
                scaleFactor,
                minNeighbors,
                minSize,
                maxSize
              },
              expectOutputCallbacked(done)
            );
          });
        });
      });
    });
  });
};
