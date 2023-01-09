import { expect } from 'chai';
import { generateAPITests } from '../../utils/generateAPITests';
import { TestContext } from '../model';

export default function (args: TestContext) {
  const { cv, getTestImg } = args;

  describe('setInput', () => {
    const expectOutput = () => {
      // expect to not throw
    };

    generateAPITests({
      getDut: () => new cv.Net(),
      methodName: 'setInput',
      methodNameSpace: 'Net',
      getRequiredArgs: () => ([
        cv.blobFromImage(getTestImg()),
      ]),
      expectOutput,
    });
  });

  // TODO: load an actual model in tests
  describe.skip('forward', () => {
    const expectOutput = (res) => {
      expect(res).to.be.instanceOf(cv.Mat);
    };

    generateAPITests({
      getDut: () => new cv.Net(),
      methodName: 'forward',
      methodNameSpace: 'Net',
      expectOutput,
    });
  });
}
