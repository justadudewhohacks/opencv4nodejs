const cv = global.dut;
const fs = require('fs');
const path = require('path');

const { readTestImage } = global.utils;
const {
  assertDataDeepEquals,
  funcShouldRequireArgs
} = global.utils;
const { expect } = require('chai');

describe('io', () => {
  let lenna;
  let got;
  let lennaBase64;
  let gotBase64;

  before(() => {
    lenna = readTestImage();
    got = readTestImage(false);
    lennaBase64 = JSON.parse(fs.readFileSync(path.join(__dirname, 'data/lennaBase64.json'))).data;
    gotBase64 = JSON.parse(fs.readFileSync(path.join(__dirname, 'data/gotBase64.json'))).data;
  });

  describe('imencode', () => {
    const pngPrefixLength = 18;
    const jpgPrefixLength = 12;
    funcShouldRequireArgs(cv.imencode);

    it('should encode png img', () => {
      const enc = cv.imencode('.png', lenna);
      const buf = Buffer.from(lennaBase64, 'base64');
      expect(enc.slice(0, pngPrefixLength)).to.deep.equal(buf.slice(0, pngPrefixLength));
    });

    it('should encode jpg img', () => {
      const enc = cv.imencode('.jpg', got);
      const buf = Buffer.from(gotBase64, 'base64');
      expect(enc.slice(0, jpgPrefixLength)).to.deep.equal(buf.slice(0, jpgPrefixLength));
    });
  });

  describe('imdecode', () => {
    funcShouldRequireArgs(cv.imdecode);

    it('should decode png', () => {
      const dec = cv.imdecode(Buffer.from(lennaBase64, 'base64'));
      assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
    });

    it('should decode jpeg', () => {
      const dec = cv.imdecode(Buffer.from(gotBase64, 'base64'));
      assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
    });
  });
});
