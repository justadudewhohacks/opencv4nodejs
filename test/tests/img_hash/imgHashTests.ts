import { expect } from 'chai';
import { PHash } from '../../../typings';
import { TestContext } from '../model';

export default (args: TestContext) => (ImgHash: typeof PHash) => {
  const { utils, getTestImg } = args;

  const {
    generateAPITests,
  } = utils;

  describe('constructor', () => {
    it('is constructable without args', () => {
      expect(() => new ImgHash()).to.not.throw();
    });
  });

  describe('api tests', () => {
    let imgHash: PHash;

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
        expectOutput,
      });
    });
  });
};
