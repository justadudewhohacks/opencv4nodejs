const cv = global.dut;
const fs = require('fs');
const path = require('path');

const {
  assertDataDeepEquals,
  assertError,
  assertMetaData,
  _asyncFuncShouldRequireArgs,
  funcShouldRequireArgs,
  getTestImagePath,
  clearTmpData,
  getTmpDataFilePath,
  fileExists,
  readTestImage
} = global.utils;

const { assert, expect } = require('chai');

const videoCaptureTests = require('./videoCaptureTests');
const videoWriterTests = require('./videoWriterTests');

describe('io', () => {
  let lenna;
  let got;
  let lennaBase64Buf;
  let gotBase64Buf;

  const getLennaBase64Buf = () => lennaBase64Buf;
  const getGotBase64Buf = () => gotBase64Buf;

  before(() => {
    lenna = readTestImage();
    got = readTestImage(false);
    lennaBase64Buf = Buffer.from(JSON.parse(fs.readFileSync(path.join(__dirname, 'data/lennaBase64.json'))).data, 'base64');
    gotBase64Buf = Buffer.from(JSON.parse(fs.readFileSync(path.join(__dirname, 'data/gotBase64.json'))).data, 'base64');
  });

  // TODO: setup opencv on travis with codecs correctly
  if (!process.env.DOCKER_BUILD && !process.env.BINDINGS_DEBUG) {
    videoCaptureTests();
    videoWriterTests();
  }

  describe('imread', () => {
    describe('sync', () => {
      funcShouldRequireArgs(cv.imread);

      it('should throw empty Mat if path invalid', () => {
        assertError(() => cv.imread('foo.png'), 'empty Mat');
      });

      it('should read image with flags', () => {
        const flags = cv.IMREAD_UNCHANGED;
        const img = cv.imread(getTestImagePath(), flags);
        expect(img).to.be.instanceOf(cv.Mat);
        assertMetaData(img)(512, 512, cv.CV_8UC3);
      });
    });

    describe('async', () => {
      _asyncFuncShouldRequireArgs(cv.imreadAsync);

      it('should throw empty Mat if path invalid', (done) => {
        cv.imreadAsync('foo.png', (err) => {
          assert.include(err.toString(), 'empty Mat');
          done();
        });
      });

      it('should read image', (done) => {
        cv.imreadAsync(getTestImagePath(), (err, img) => {
          expect(img).to.be.instanceOf(cv.Mat);
          assertMetaData(img)(512, 512, cv.CV_8UC3);
          done();
        });
      });

      it('should read image with flags', (done) => {
        const flags = cv.IMREAD_UNCHANGED;
        cv.imreadAsync(getTestImagePath(), flags, (err, img) => {
          expect(img).to.be.instanceOf(cv.Mat);
          assertMetaData(img)(512, 512, cv.CV_8UC3);
          done();
        });
      });
    });
  });

  describe('imwrite', () => {
    beforeEach(() => { clearTmpData(); });
    afterEach(() => { clearTmpData(); });

    describe('sync', () => {
      funcShouldRequireArgs(cv.imwrite);

      it('should write image', () => {
        const file = getTmpDataFilePath('written_sync.png');
        cv.imwrite(file, lenna);
        expect(fileExists(file)).to.be.true;
      });

      it('should write image with flags', () => {
        const flags = [cv.IMWRITE_PNG_COMPRESSION];
        const file = getTmpDataFilePath('written_sync.png');
        cv.imwrite(file, lenna, flags);
        expect(fileExists(file)).to.be.true;
      });
    });

    describe('async', () => {
      const file = getTmpDataFilePath('written_async.png');
      _asyncFuncShouldRequireArgs(cv.imwriteAsync);

      it('should write image', (done) => {
        cv.imwriteAsync(file, lenna, () => {
          expect(fileExists(file)).to.be.true;
          done();
        });
      });

      it('should write image with flags', (done) => {
        const flags = [cv.IMWRITE_PNG_COMPRESSION];
        cv.imwriteAsync(file, lenna, flags, () => {
          expect(fileExists(file)).to.be.true;
          done();
        });
      });
    });
  });

  describe('imencode', () => {
    describe('sync', () => {
      const pngPrefixLength = 18;
      const jpgPrefixLength = 12;
      funcShouldRequireArgs(cv.imencode);

      it('should encode png img', () => {
        const enc = cv.imencode('.png', lenna);
        const buf = getLennaBase64Buf();
        expect(enc.slice(0, pngPrefixLength)).to.deep.equal(buf.slice(0, pngPrefixLength));
      });

      it('should encode jpg img', () => {
        const enc = cv.imencode('.jpg', got);
        const buf = getGotBase64Buf();
        expect(enc.slice(0, jpgPrefixLength)).to.deep.equal(buf.slice(0, jpgPrefixLength));
      });
    });

    describe('async', () => {
      const pngPrefixLength = 18;
      const jpgPrefixLength = 12;
      _asyncFuncShouldRequireArgs(cv.imencodeAsync);

      it('should encode png img', (done) => {
        cv.imencodeAsync('.png', lenna, (err, enc) => {
          const buf = getLennaBase64Buf();
          expect(enc.slice(0, pngPrefixLength)).to.deep.equal(buf.slice(0, pngPrefixLength));
          done();
        });
      });

      it('should encode jpg img', (done) => {
        cv.imencodeAsync('.jpg', got, (err, enc) => {
          const buf = getGotBase64Buf();
          expect(enc.slice(0, jpgPrefixLength)).to.deep.equal(buf.slice(0, jpgPrefixLength));
          done();
        });
      });
    });
  });

  describe('imdecode', () => {
    describe('sync', () => {
      funcShouldRequireArgs(cv.imdecode);

      it('should decode png', () => {
        const dec = cv.imdecode(getLennaBase64Buf());
        assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
      });

      it('should decode jpeg', () => {
        const dec = cv.imdecode(getGotBase64Buf());
        assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
      });
    });

    describe('async', () => {
      _asyncFuncShouldRequireArgs(cv.imdecodeAsync);

      it('should decode png', (done) => {
        cv.imdecodeAsync(getLennaBase64Buf(), (err, dec) => {
          assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
          done();
        });
      });

      it('should decode jpeg', (done) => {
        cv.imdecodeAsync(getGotBase64Buf(), (err, dec) => {
          assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
          done();
        });
      });
    });
  });
});
