const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => (Facemark, FacemarkParams) => {

  const {
    generateAPITests,
    clearTmpData,
    getTmpDataFilePath,
    cvVersionLowerThan
  } = utils;

  describe('constructor', () => {
    it('is constructable without args', () => {
      expect(() => new Facemark()).to.not.throw();
    });

    it('is constructable from args', () => {
      const params = new FacemarkParams();
      expect(() => new Facemark(params).to.not.throw());
    });
  });

  (cvVersionLowerThan(3, 2, 0) ? describe : describe.skip)('face detection tests', () => {
    let facemark;
    before(() => {
      facemark = new Facemark();
    });

    describe('setFaceDetector', () => {
      const expectOutput = () => {};
      const callback = () => {};

      generateAPITests({
        getDut: () => facemark,
        methodName: 'setFaceDetector',
        methodNameSpace: 'Facemark',
        getRequiredArgs: () => [callback],
        hasAsync: false,
        expectOutput
      });
    });

    describe('getData', () => {
      const expectOutput = () => {};

      generateAPITests({
        getDut: () => facemark,
        methodName: 'getData',
        methodNameSpace: 'Facemark',
        hasAsync: true,
        expectOutput
      });
    });

    describe('getFaces', () => {
      const expectOutput = () => {};

      it('setFaceDetector', () => {
        facemark.setFaceDetector(() => []);
      });

      generateAPITests({
        getDut: () => facemark,
        methodName: 'getFaces',
        methodNameSpace: 'Facemark',
        getRequiredArgs: () => [getTestImg().bgrToGray()],
        hasAsync: false,
        expectOutput
      });
    });
  });

  (cvVersionLowerThan(3, 2, 0) ? describe : describe.skip)('train', () => {
    let facemark;

    const landmarks = [];
    for (let i = 0; i < 68; i++) {
      landmarks[i] = new cv.Point2(Math.random() * 250, Math.random() * 250);
    }

    before(() => {
      const params = new FacemarkParams();
      params.cascadeFace = '../lib/haarcascades/haarcascade_frontalcatface.xml';
      params.modelFilename = 'modelFilename.model';
      params.nLandmarks = 68;
      params.initShapeN = 10;
      params.stagesN = 5;
      params.treeN = 6;
      params.treeDepth = 5;

      facemark = new Facemark(params);
    });

    describe('addTrainingSample', () => {
      generateAPITests({
        getDut: () => facemark,
        methodName: 'addTrainingSample',
        methodNameSpace: 'Facemark',
        getRequiredArgs: () => [getTestImg().bgrToGray(), landmarks],
        expectOutput: () => {}
      });
    });
  });

  describe('trained model tests', () => {
    let facemark;

    before(() => {
      facemark = new Facemark();
    });

    describe('fit', () => {
      const expectOutput = (res) => {
        expect(res).to.be.an('array');
      };

      const faces = [];

      generateAPITests({
        getDut: () => facemark,
        methodName: 'fit',
        methodNameSpace: 'Facemark',
        getRequiredArgs: () => [getTestImg().bgrToGray(), faces],
        expectOutput
      });
    });

    describe('save and load', () => {
      beforeEach(() => {
        clearTmpData();
      });
      afterEach(() => {
        clearTmpData();
      });

      it('should save and load from xml', () => {
        const file = getTmpDataFilePath('testFacemark.xml');
        facemark.save(file);
        const facemarkNew = new Facemark();
        facemarkNew.load(file);
      });
    });
  });
};
