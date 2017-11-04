const { generateAPITests, clearTmpData, getTmpDataFilePath } = global.utils;
const { expect } = require('chai');

module.exports = (getTestImg, args, values, Recognizer) => {
  let testImg;

  before(() => {
    testImg = getTestImg().bgrToGray();
  });

  describe('constructor', () => {
    const props = {};
    args.forEach((arg, i) => {
      props[arg] = values[i];
    });

    /* eslint-disable new-parens */
    it('is constructable from args', () => {
      expect(() => new (Recognizer.bind.apply(Recognizer, [null].concat(values)))).to.not.throw();
    });

    it('is constructable from args object', () => {
      expect(() => new Recognizer(props)).to.not.throw();
    });
  });

  describe('train', () => {
    const expectOutput = () => {
      // expect to not throw
    };

    generateAPITests({
      getDut: () => new Recognizer(),
      methodName: 'train',
      methodNameSpace: 'FaceRecognizer',
      getRequiredArgs: () => ([
        [testImg, testImg],
        [1, 2]
      ]),
      expectOutput
    });
  });

  describe('trained model tests', () => {
    let recognizer;

    before(() => {
      recognizer = new Recognizer();
      recognizer.train([testImg, testImg], [1, 2]);
    });

    describe('predict', () => {
      const expectOutput = (res) => {
        expect(res).to.have.property('label');
        expect(res).to.have.property('confidence');
      };

      generateAPITests({
        getDut: () => recognizer,
        methodName: 'predict',
        methodNameSpace: 'FaceRecognizer',
        getRequiredArgs: () => ([
          testImg
        ]),
        expectOutput
      });
    });

    describe('save and load', () => {
      beforeEach(() => { clearTmpData(); });
      afterEach(() => { clearTmpData(); });

      it('should save and load from xml', () => {
        const file = getTmpDataFilePath('testRecognizer.xml');
        recognizer.save(file);
        const recognizerNew = new Recognizer();
        recognizerNew.load(file);
      });
    });
  });
};
