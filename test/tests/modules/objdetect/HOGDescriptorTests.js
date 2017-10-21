const cv = global.dut;
const {
  assertError,
  asyncFuncShouldRequireArgs,
  _funcShouldRequireArgs
} = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('HOGDescriptor', () => {
    describe('constructor', () => {
      it('should be constructable with default args', () => {
        const hog = new cv.HOGDescriptor();
        ['winSize', 'blockSize', 'blockStride', 'cellSize'].forEach(
          prop => expect(hog).to.have.property(prop).instanceOf(cv.Size)
        );
      });

      it('should be constructable with custom args', () => {
        const hog = new cv.HOGDescriptor(
          new cv.Size(40, 40),
          new cv.Size(20, 20),
          new cv.Size(10, 10),
          new cv.Size(30, 30),
          18,
          2,
          1.8,
          0,
          0.4,
          true,
          64,
          true
        );
        [{ p: 'winSize', dim: 40 }, { p: 'blockSize', dim: 20 }, { p: 'blockStride', dim: 10 }, { p: 'cellSize', dim: 30 }].forEach(
          (pv) => {
            expect(hog).to.have.property(pv.p).instanceOf(cv.Size);
            const { width, height } = hog[pv.p];
            expect(width).to.equal(pv.dim);
            expect(height).to.equal(pv.dim);
          }
        );
        expect(hog).to.have.property('nbins').to.equal(18);
        expect(hog).to.have.property('derivAperture').to.equal(2);
        expect(hog).to.have.property('winSigma').to.equal(1.8);
        expect(hog).to.have.property('L2HysThreshold').to.equal(0.4);
        expect(hog).to.have.property('gammaCorrection').to.be.true;
        expect(hog).to.have.property('signedGradient').to.be.true;
      });

      it('should be constructable with custom args object', () => {
        const hog = new cv.HOGDescriptor({
          winSize: new cv.Size(40, 40),
          blockSize: new cv.Size(20, 20),
          blockStride: new cv.Size(10, 10),
          cellSize: new cv.Size(30, 30),
          nbins: 18,
          derivAperture: 2,
          winSigma: 1.8,
          histogramNormType: 0,
          L2HysThreshold: 0.4,
          gammaCorrection: true,
          numLevels: 64,
          signedGradient: true
        });
        [{ p: 'winSize', dim: 40 }, { p: 'blockSize', dim: 20 }, { p: 'blockStride', dim: 10 }, { p: 'cellSize', dim: 30 }].forEach(
          (pv) => {
            expect(hog).to.have.property(pv.p).instanceOf(cv.Size);
            const { width, height } = hog[pv.p];
            expect(width).to.equal(pv.dim);
            expect(height).to.equal(pv.dim);
          }
        );
        expect(hog).to.have.property('nbins').to.equal(18);
        expect(hog).to.have.property('derivAperture').to.equal(2);
        expect(hog).to.have.property('winSigma').to.equal(1.8);
        expect(hog).to.have.property('L2HysThreshold').to.equal(0.4);
        expect(hog).to.have.property('gammaCorrection').to.be.true;
        expect(hog).to.have.property('signedGradient').to.be.true;
      });

      it('should implement compute', () => {
        const hog = new cv.HOGDescriptor();
        expect(hog).to.have.property('compute').to.be.a('function');
      });

      it('should implement computeAsync', () => {
        const hog = new cv.HOGDescriptor();
        expect(hog).to.have.property('computeAsync').to.be.a('function');
      });
    });

    describe('compute', () => {
      const expectOutput = (desc) => {
        expect(desc).to.be.an('array');
      };

      const winStride = new cv.Size(3, 3);
      const padding = new cv.Size(3, 3);
      const locations = [new cv.Point(50, 50), new cv.Point(150, 50), new cv.Point(50, 150)];
      const invalidLocations = [new cv.Point(50, 50), undefined, new cv.Point(50, 150)];

      describe('sync', () => {
        _funcShouldRequireArgs(() => new cv.HOGDescriptor().compute());

        it('should be callable with single channel img', () => {
          expectOutput(new cv.HOGDescriptor().compute(
            new cv.Mat(200, 200, cv.CV_8U)
          ));
        });

        it('should be callable with triple channel img', () => {
          expectOutput(new cv.HOGDescriptor().compute(
            new cv.Mat(200, 200, cv.CV_8UC3)
          ));
        });

        it('should be callable with optional args', () => {
          expectOutput(new cv.HOGDescriptor().compute(
            new cv.Mat(200, 200, cv.CV_8UC3),
            winStride,
            padding,
            locations
          ));
        });

        it('should be callable with optional args object', () => {
          expectOutput(new cv.HOGDescriptor().compute(
            new cv.Mat(200, 200, cv.CV_8UC3),
            {
              winStride,
              padding,
              locations
            }
          ));
        });

        it('should throw if locations invalid', () => {
          assertError(
            () => new cv.HOGDescriptor().compute(
              new cv.Mat(200, 200, cv.CV_8UC3),
              winStride,
              padding,
              invalidLocations
            ),
            'expected array element at index 1 to be of type Point2'
          );
        });

        it('should throw if locations invalid for opt arg object', () => {
          assertError(
            () => new cv.HOGDescriptor().compute(
              new cv.Mat(200, 200, cv.CV_8UC3),
              { locations: invalidLocations }
            ),
            'expected array element at index 1 to be of type Point2'
          );
        });
      });

      describe('async', () => {
        const expectOutputCallbacked = done => (err, desc) => {
          expectOutput(desc);
          done();
        };

        const expectOutputPromisified = done => (desc) => {
          expectOutput(desc);
          done();
        };

        asyncFuncShouldRequireArgs(() => new cv.HOGDescriptor().computeAsync());

        describe('callbacked', () => {
          it('should be callable with single channel img', (done) => {
            new cv.HOGDescriptor().computeAsync(
              new cv.Mat(200, 200, cv.CV_8U),
              expectOutputCallbacked(done)
            );
          });

          it('should be callable with triple channel img', (done) => {
            new cv.HOGDescriptor().computeAsync(
              new cv.Mat(200, 200, cv.CV_8UC3),
              expectOutputCallbacked(done)
            );
          });

          it('should be callable with optional args', (done) => {
            new cv.HOGDescriptor().computeAsync(
              new cv.Mat(200, 200, cv.CV_8UC3),
              winStride,
              padding,
              locations,
              expectOutputCallbacked(done)
            );
          });

          it('should be callable with optional args object', (done) => {
            new cv.HOGDescriptor().computeAsync(
              new cv.Mat(200, 200, cv.CV_8UC3),
              {
                winStride,
                padding,
                locations
              },
              expectOutputCallbacked(done)
            );
          });

          it('should throw if locations invalid', () => {
            assertError(
              () => new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8UC3),
                winStride,
                padding,
                invalidLocations,
                () => {}
              ),
              'expected array element at index 1 to be of type Point2'
            );
          });

          it('should throw if locations invalid for opt arg object', () => {
            assertError(
              () => new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8UC3),
                { locations: invalidLocations },
                () => {}
              ),
              'expected array element at index 1 to be of type Point2'
            );
          });

          describe('promisified', () => {
            it('should be callable with single channel img', (done) => {
              new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8U)
              ).then(expectOutputPromisified(done));
            });

            it('should be callable with triple channel img', (done) => {
              new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8UC3)
              ).then(expectOutputPromisified(done));
            });

            it('should be callable with optional args', (done) => {
              new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8UC3),
                winStride,
                padding,
                locations
              ).then(expectOutputPromisified(done));
            });

            it('should be callable with optional args object', (done) => {
              new cv.HOGDescriptor().computeAsync(
                new cv.Mat(200, 200, cv.CV_8UC3),
                {
                  winStride,
                  padding,
                  locations
                }
              ).then(expectOutputPromisified(done));
            });
          });
        });
      });
    });
  });
};
