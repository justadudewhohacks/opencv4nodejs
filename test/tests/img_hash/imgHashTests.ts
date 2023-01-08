import { expect } from 'chai';
import { PHash } from '../../../typings';
import { generateAPITests } from '../../utils/generateAPITests';
import { TestContext } from '../model';

export default (args: TestContext) => (ImgHash: typeof PHash) => {
  const { getTestImg } = args;

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
