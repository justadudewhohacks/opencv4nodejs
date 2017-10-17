const { expect } = require('chai');

const cv = global.dut;
const {
  assertError,
  assertPropsWithValue,
  _funcShouldRequireArgs,
  getTmpDataFilePath,
  clearTmpData
} = global.utils;

module.exports = () => {
  describe('SVM', () => {
    const samples = new cv.Mat([
      [100, 200, 200],
      [200, 100, 200],
      [150, 150, 150],
      [150, 150, 200],
      [100, 100, 200],
      [100, 100, 100],
      [10, 20, 20],
      [20, 10, 20],
      [15, 15, 15],
      [15, 15, 20],
      [10, 10, 20],
      [10, 10, 10]
    ], cv.CV_32F);
    const labels = new cv.Mat([[0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]], cv.CV_32S);
    const trainData = new cv.TrainData(
      samples,
      cv.ml.ROW_SAMPLE,
      labels
    );
    const someArgs = {
      c: 0.1,
      coef0: 1.1,
      degree: Math.PI,
      nu: 0.4,
      p: 0.5,
      kernelType: cv.ml.SVM.SIGMOID
    };

    describe('constructor', () => {
      it('should be constructable without args', () => {
        expect(new cv.SVM()).to.be.instanceOf(cv.SVM);
      });

      it('should throw if arg0 is not an obj', () => {
        expect(() => new cv.SVM(undefined)).to.throw();
      });

      it('should not throw if arg0 is an obj', () => {
        expect(() => new cv.SVM({})).not.to.throw();
      });

      it('should be constructable from args', () => {
        const svm = new cv.SVM(someArgs);
        assertPropsWithValue(svm)(someArgs);
      });

      it('should not be trained', () => {
        expect(new cv.SVM()).to.have.property('isTrained').to.be.false;
      });
    });

    describe('setParams', () => {
      it('should set params', () => {
        const svm = new cv.SVM();
        svm.setParams(someArgs);
        assertPropsWithValue(svm)(someArgs);
      });

      it('should set only specified params', () => {
        const args = {
          c: 0.2,
          coef0: 0.1
        };
        const svm = new cv.SVM(someArgs);
        svm.setParams(args);
        assertPropsWithValue(svm)(
          Object.assign(
            {},
            someArgs,
            args
          )
        );
      });
    });


    describe('training', () => {
      const expectOutput = (svm, ret) => {
        expect(ret).to.be.a('boolean');
        expect(svm).to.have.property('isTrained').to.be.true;
        expect(svm).to.have.property('varCount').to.equal(samples.cols);
      };

      const expectOutputAsync = (done, svm) => (err, ret) => {
        expectOutput(svm, ret);
        done();
      };

      describe('train', () => {
        describe('sync', () => {
          _funcShouldRequireArgs(() => new cv.SVM().train());

          it('should be trainable with trainData', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.train(trainData)
            );
          });

          it('should be trainable with trainData and flag', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.train(
                trainData,
                cv.statModel.RAW_OUTPUT
              )
            );
          });

          it('should be trainable with samples, layout and responses', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.train(
                samples,
                cv.ml.ROW_SAMPLE,
                labels
              )
            );
          });
        });

        describe('async', () => {
          _funcShouldRequireArgs(() => new cv.SVM().trainAsync());

          it('should be trainable with trainData', (done) => {
            const svm = new cv.SVM();
            svm.trainAsync(
              trainData,
              expectOutputAsync(done, svm)
            );
          });

          it('should be trainable with trainData and flag', (done) => {
            const svm = new cv.SVM();
            svm.trainAsync(
              trainData,
              cv.statModel.RAW_OUTPUT,
              expectOutputAsync(done, svm)
            );
          });

          it('should be trainable with samples, layout and responses', (done) => {
            const svm = new cv.SVM();
            svm.trainAsync(
              samples,
              cv.ml.ROW_SAMPLE,
              labels,
              expectOutputAsync(done, svm)
            );
          });
        });
      });

      describe('trainAuto', () => {
        const kFold = 20;
        const cGrid = new cv.ParamGrid(cv.ml.SVM.C);
        const gammaGrid = new cv.ParamGrid(cv.ml.SVM.GAMMA);
        const pGrid = new cv.ParamGrid(cv.ml.SVM.P);
        const nuGrid = new cv.ParamGrid(cv.ml.SVM.NU);
        const coeffGrid = new cv.ParamGrid(cv.ml.SVM.COEF);
        const degreeGrid = new cv.ParamGrid(cv.ml.SVM.DEGREE);
        const balanced = true;

        describe('sync', () => {
          _funcShouldRequireArgs(() => new cv.SVM().trainAuto());

          it('should be trainable with trainData', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.trainAuto(trainData)
            );
          });

          it('should be trainable with trainData and all optional args', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.trainAuto(
                trainData,
                kFold,
                cGrid,
                gammaGrid,
                pGrid,
                nuGrid,
                coeffGrid,
                degreeGrid,
                balanced
              )
            );
          });

          it('should be trainable with trainData and first optional args', () => {
            const svm = new cv.SVM();
            expectOutput(
              svm,
              svm.trainAuto(
                trainData,
                kFold
              )
            );
          });

          it('should throw if optional arg is invalid', () => {
            assertError(
              () => new cv.SVM().trainAuto(
                trainData,
                undefined
              ),
              'argument 1'
            );
          });

          it('should be trainable with trainData and optional args object', () => {
            const svm = new cv.SVM();
            const opts = {
              kFold,
              cGrid,
              gammaGrid,
              pGrid,
              nuGrid,
              coeffGrid,
              degreeGrid,
              balanced
            };
            expectOutput(
              svm,
              svm.trainAuto(
                trainData,
                opts
              )
            );
          });

          it('should be trainable with trainData and some optional args', () => {
            const svm = new cv.SVM();
            const opts = {
              degreeGrid,
              balanced
            };
            expectOutput(
              svm,
              svm.trainAuto(
                trainData,
                opts
              )
            );
          });

          it('should throw if optional arg property is invalid', () => {
            assertError(
              () => new cv.SVM().trainAuto(
                trainData,
                { degreeGrid: undefined }
              ),
              'property degreeGrid'
            );
          });
        });

        describe('async', () => {
          _funcShouldRequireArgs(() => new cv.SVM().trainAutoAsync());

          it('should be trainable with trainData', (done) => {
            const svm = new cv.SVM();
            svm.trainAutoAsync(
              trainData,
              expectOutputAsync(done, svm)
            );
          });

          it('should be trainable with trainData and all optional args', (done) => {
            const svm = new cv.SVM();
            svm.trainAutoAsync(
              trainData,
              kFold,
              cGrid,
              gammaGrid,
              pGrid,
              nuGrid,
              coeffGrid,
              degreeGrid,
              balanced,
              expectOutputAsync(done, svm)
            );
          });

          it('should be trainable with trainData and first optional args', (done) => {
            const svm = new cv.SVM();
            svm.trainAutoAsync(
              trainData,
              kFold,
              expectOutputAsync(done, svm)
            );
          });

          it('should throw if optional arg is invalid', () => {
            assertError(
              () => new cv.SVM().trainAuto(
                trainData,
                undefined,
                () => {}
              ),
              'argument 1'
            );
          });

          it('should be trainable with trainData and optional args object', (done) => {
            const svm = new cv.SVM();
            const opts = {
              kFold,
              cGrid,
              gammaGrid,
              pGrid,
              nuGrid,
              coeffGrid,
              degreeGrid,
              balanced
            };
            svm.trainAutoAsync(
              trainData,
              opts,
              expectOutputAsync(done, svm)
            );
          });

          it('should be trainable with trainData and some optional args', (done) => {
            const svm = new cv.SVM();
            const opts = {
              degreeGrid,
              balanced
            };
            svm.trainAutoAsync(
              trainData,
              opts,
              expectOutputAsync(done, svm)
            );
          });

          it('should throw if optional arg property is invalid', () => {
            assertError(
              () => new cv.SVM().trainAutoAsync(
                trainData,
                { degreeGrid: undefined },
                () => {}
              ),
              'property degreeGrid'
            );
          });
        });
      });
    });

    describe('trained model tests', () => {
      let svm;
      const predictSample = [10, 10.5, 10.5];
      const predictSamplesMat = new cv.Mat([[10, 20, 15], [100, 200, 200]], cv.CV_32F);

      before(() => {
        svm = new cv.SVM();
        svm.trainAuto(trainData);
      });

      describe('predict', () => {
        it('should be callable with sample array', () => {
          expect(() => svm.predict(predictSample)).to.not.throw();
        });

        it('should be callable with samples mat', () => {
          expect(() => svm.predict(predictSamplesMat)).to.not.throw();
        });

        it('should return classification result of predicted sample', () => {
          expect(svm.predict(predictSample)).to.equal(1);
        });

        it('should return classification results of predicted samples', () => {
          const predictions = svm.predict(predictSamplesMat);
          expect(predictions).to.be.an('array').lengthOf(2);
          expect(predictions).to.have.ordered.members([1, 0]);
        });
      });

      describe('getSupportVectors', () => {
        it('should return support vectors', () => {
          expect(svm.getSupportVectors()).to.be.instanceOf(cv.Mat);
        });
      });

      describe('getUncompressedSupportVectors', () => {
        (cv.version.minor < 2 ? it.skip : it)('should return support vectors', () => {
          expect(svm.getUncompressedSupportVectors()).to.be.instanceOf(cv.Mat);
        });
      });

      describe('calcError', () => {
        it.skip('calcError', () => {});
      });

      describe('save and load', () => {
        beforeEach(() => { clearTmpData(); });
        afterEach(() => { clearTmpData(); });

        it('should save and load from xml', () => {
          const file = getTmpDataFilePath('testSVM.xml');
          svm.save(file);
          const svmNew = new cv.SVM();
          svmNew.load(file);

          const svm1 = Object.assign({}, svm);
          const svm2 = Object.assign({}, svmNew);
          svm1.classWeights = null;
          svm2.classWeights = null;
          assertPropsWithValue(svm1)(svm2);
        });
      });
    });
  });
};
