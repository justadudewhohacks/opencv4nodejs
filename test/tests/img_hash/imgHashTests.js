const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => (ImgHash) => {

  const {
    generateAPITests,
    clearTmpData,
    getTmpDataFilePath,
    cvVersionLowerThan
  } = utils;

  describe('constructor', () => {
    it('is constructable without args', () => {
      expect(() => new ImgHash()).to.not.throw();
    });
  });


  describe('api tests', () => {
    let imgHash;

    before(() => {
      imgHash = new ImgHash();
    });

    describe('compute', () => {
      const expectOutput = (res) => {
        expect(res).to.be.an('array');
      };

      generateAPITests({
        getDut: () => imgHash,
        methodName: 'compute',
        methodNameSpace: 'ImgHashBase',
        getRequiredArgs: () => [getTestImg().bgrToGray()],
        expectOutput
      });
    });

  });
};
