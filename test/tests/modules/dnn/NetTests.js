const cv = global.dut;
const { generateAPITests } = global.utils;
const { expect } = require('chai');

module.exports = (getTestImg) => {
  let blob;
  before(() => {
    blob = cv.blobFromImage(getTestImg());
  });

  describe('setInput', () => {
    const expectOutput = () => {
      // expect to not throw
    };

    generateAPITests({
      getDut: () => new cv.Net(),
      methodName: 'setInput',
      methodNameSpace: 'Net',
      getRequiredArgs: () => ([
        blob
      ]),
      expectOutput
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
      expectOutput
    });
  });
};
