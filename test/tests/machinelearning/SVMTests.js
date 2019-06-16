const { expect } = require('chai');

module.exports = ({ cv, utils }) => {

  const {
    generateAPITests,
    assertPropsWithValue,
    getTmpDataFilePath,
    clearTmpData,
    cvVersionLowerThan
  } = utils;

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
    const expectOutput = (ret, svm) => {
      expect(ret).to.be.a('boolean');
      expect(svm).to.have.property('isTrained').to.be.true;
      expect(svm).to.have.property('varCount').to.equal(samples.cols);
    };

    describe('train', () => {
      describe('with trainData', () => {
        generateAPITests({
          getDut: () => new cv.SVM(),
          methodName: 'train',
          methodNameSpace: 'SVM',
          getRequiredArgs: () => ([
            trainData
          ]),
          getOptionalArg: () => cv.statModel.RAW_OUTPUT,
          expectOutput
        });
      });

      describe('with samples, layout and responses', () => {
        generateAPITests({
          getDut: () => new cv.SVM(),
          methodName: 'train',
          methodNameSpace: 'SVM',
          getRequiredArgs: () => ([
            samples,
            cv.ml.ROW_SAMPLE,
            labels
          ]),
          expectOutput
        });
      });
    });

    describe('trainAuto', () => {
      generateAPITests({
        getDut: () => new cv.SVM(),
        methodName: 'trainAuto',
        methodNameSpace: 'SVM',
        getRequiredArgs: () => ([
          trainData
        ]),
        getOptionalArgsMap: () => ([
          ['kFold', 20],
          ['cGrid', new cv.ParamGrid(cv.ml.SVM.C)],
          ['gammaGrid', new cv.ParamGrid(cv.ml.SVM.GAMMA)],
          ['pGrid', new cv.ParamGrid(cv.ml.SVM.P)],
          ['nuGrid', new cv.ParamGrid(cv.ml.SVM.NU)],
          ['coeffGrid', new cv.ParamGrid(cv.ml.SVM.COEF)],
          ['degreeGrid', new cv.ParamGrid(cv.ml.SVM.DEGREE)],
          ['balanced', true]
        ]),
        expectOutput
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
      (cvVersionLowerThan(3, 2, 0) ? it.skip : it)('should return support vectors', () => {
        expect(svm.getUncompressedSupportVectors()).to.be.instanceOf(cv.Mat);
      });
    });

    describe('getDecisionFunction', () => {
      it('should return decision function', () => {
        const ret = svm.getDecisionFunction(0);
        expect(ret).to.have.property('rho').to.be.a('number');
        expect(ret).to.have.property('alpha').to.be.instanceOf(cv.Mat);
        expect(ret).to.have.property('svidx').to.be.instanceOf(cv.Mat);
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

};
