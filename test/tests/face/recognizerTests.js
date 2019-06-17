const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => (args, values, Recognizer) => {
  const {
    generateAPITests,
    clearTmpData,
    getTmpDataFilePath
  } = utils;

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
        [getTestImg().bgrToGray(), getTestImg().bgrToGray()],
        [1, 2]
      ]),
      expectOutput
    });
  });

  describe('trained model tests', () => {
    let recognizer;

    before(() => {
      recognizer = new Recognizer();
      recognizer.train([getTestImg().bgrToGray(), getTestImg().bgrToGray()], [1, 2]);
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
          getTestImg().bgrToGray()
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
