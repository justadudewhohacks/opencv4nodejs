const cv = global.dut;
const fs = require('fs');
const path = require('path');

const {
  getTestImagePath,
  clearTmpData,
  getTmpDataFilePath,
  fileExists,
  readTestImage
} = global.utils;
const {
  assertDataDeepEquals,
  assertError,
  assertMetaData,
  funcShouldRequireArgs
} = global.utils;

const { assert, expect } = require('chai');

const videoCaptureTests = require('./videoCaptureTests');

describe('io', () => {
  let lenna;
  let got;
  let lennaBase64Buf;
  let gotBase64Buf;

  before(() => {
    lenna = readTestImage();
    got = readTestImage(false);
    lennaBase64Buf = Buffer.from(JSON.parse(fs.readFileSync(path.join(__dirname, 'data/lennaBase64.json'))).data, 'base64');
    gotBase64Buf = Buffer.from(JSON.parse(fs.readFileSync(path.join(__dirname, 'data/gotBase64.json'))).data, 'base64');
  });

  // TODO: setup opencv on travis with codecs correctly
  if (!process.env.DOCKER_BUILD && !process.env.BINDINGS_DEBUG) {
    videoCaptureTests();
  }

  describe('imread', () => {
    describe('sync', () => {
      funcShouldRequireArgs(cv.imread);

      it('should throw empty Mat if path invalid', () => {
        assertError(() => cv.imread('foo.png'), 'empty Mat');
      });
    });

    describe('async', () => {
      funcShouldRequireArgs(cv.imreadAsync);

      it('should require a callback', () => {
        assertError(() => cv.imreadAsync('foo.png'), 'expected arg 1 to be of type: FUNC');
      });

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
    });

    describe('async', () => {
      const file = getTmpDataFilePath('written_async.png');
      funcShouldRequireArgs(cv.imwriteAsync);

      it('should require a callback', () => {
        assertError(() => cv.imwriteAsync(file, lenna), 'expected arg 2 to be of type: FUNC');
      });

      it('should write image', (done) => {
        cv.imwriteAsync(file, lenna, () => {
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
        const buf = lennaBase64Buf;
        expect(enc.slice(0, pngPrefixLength)).to.deep.equal(buf.slice(0, pngPrefixLength));
      });

      it('should encode jpg img', () => {
        const enc = cv.imencode('.jpg', got);
        const buf = gotBase64Buf;
        expect(enc.slice(0, jpgPrefixLength)).to.deep.equal(buf.slice(0, jpgPrefixLength));
      });
    });

    describe('async', () => {
      const pngPrefixLength = 18;
      const jpgPrefixLength = 12;
      funcShouldRequireArgs(cv.imencodeAsync);

      it('should require a callback', () => {
        assertError(() => cv.imencodeAsync('.png', lenna), 'expected arg 2 to be of type: FUNC');
      });

      it('should encode png img', (done) => {
        cv.imencodeAsync('.png', lenna, (err, enc) => {
          const buf = lennaBase64Buf;
          expect(enc.slice(0, pngPrefixLength)).to.deep.equal(buf.slice(0, pngPrefixLength));
          done();
        });
      });

      it('should encode jpg img', (done) => {
        cv.imencodeAsync('.jpg', got, (err, enc) => {
          const buf = gotBase64Buf;
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
        const dec = cv.imdecode(lennaBase64Buf);
        assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
      });

      it('should decode jpeg', () => {
        const dec = cv.imdecode(gotBase64Buf);
        assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
      });
    });

    describe('async', () => {
      funcShouldRequireArgs(cv.imdecodeAsync);

      it('should require a callback', () => {
        assertError(() => cv.imdecodeAsync(lennaBase64Buf), 'expected arg 1 to be of type: FUNC');
      });

      it('should decode png', (done) => {
        cv.imdecodeAsync(lennaBase64Buf, (err, dec) => {
          assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
          done();
        });
      });

      it('should decode jpeg', (done) => {
        cv.imdecodeAsync(gotBase64Buf, (err, dec) => {
          assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
          done();
        });
      });
    });
  });
});
