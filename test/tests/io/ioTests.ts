import fs from 'fs';
import path from 'path';
import { expect } from 'chai';
import { Mat } from '@u4/opencv4nodejs';
import { TestContext } from '../model';
import { assertDataDeepEquals, assertMetaData } from '../../utils/matTestUtils';
import { clearTmpData, fileExists, getTmpDataFilePath, _asyncFuncShouldRequireArgs } from '../../utils/testUtils';

export default function (args: TestContext) {
  const { cv, utils } = args;

  const {
    funcShouldRequireArgs,
    getTestImagePath,
    generateAPITests,
  } = utils;

  let lenna: Mat;
  let got: Mat;
  let lennaBase64Buf: Buffer;
  let gotBase64Buf: Buffer;

  const getLennaBase64Buf = () => lennaBase64Buf;
  const getGotBase64Buf = () => gotBase64Buf;
  // let imageData: Buffer;
  // let imageDataCopy: Buffer;

  const lennaBase64File = fs.readFileSync(path.join(__dirname, 'data/lennaBase64.json'), { encoding: 'utf8', flag: 'r' });
  const gotBase64File = fs.readFileSync(path.join(__dirname, 'data/gotBase64.json'), { encoding: 'utf8', flag: 'r' });
  before(() => {
    lenna = cv.imread(getTestImagePath(true));
    got = cv.imread(getTestImagePath(false));
    lennaBase64Buf = Buffer.from(JSON.parse(lennaBase64File).data, 'base64');
    gotBase64Buf = Buffer.from(JSON.parse(gotBase64File).data, 'base64');
    // imageData = fs.readFileSync(getTestImagePath(true));
    // imageDataCopy = Buffer.from(imageData);
  });

  describe('imread', () => {
    const flags = cv.IMREAD_UNCHANGED;
    generateAPITests({
      getDut: () => cv,
      methodName: 'imread',
      getRequiredArgs: () => ([
        getTestImagePath(),
      ]),
      getOptionalArg: () => flags,
      expectOutput: (img) => {
        expect(img).to.be.instanceOf(cv.Mat);
        assertMetaData(img)(512, 512, cv.CV_8UC3);
      },
    });
  });
  describe('imwrite', () => {
    const file = getTmpDataFilePath('written_sync.png');
    const flags = [cv.IMWRITE_PNG_COMPRESSION];
    generateAPITests({
      beforeHook: () => { clearTmpData(); },
      afterHook: () => { clearTmpData(); },
      getDut: () => cv,
      methodName: 'imwrite',
      getRequiredArgs: () => ([
        file,
        lenna,
      ]),
      getOptionalArg: () => flags,
      expectOutput: () => {
        expect(fileExists(file)).to.be.true;
      },
    });
  });

  describe('io imencode', () => {
    describe('io imencode png', () => {
      const pngPrefixLength = 18;

      const ext = '.png';
      const flags = [cv.IMWRITE_PNG_COMPRESSION];
      generateAPITests({
        prefix: 'io imencode png',
        getDut: () => cv,
        methodName: 'imencode',
        getRequiredArgs: () => ([
          ext,
          lenna,
        ]),
        getOptionalArg: () => flags,
        expectOutput: (enc: Uint8Array) => {
          const encPrefix = enc.slice(0, pngPrefixLength);
          const lennaPrefix = getLennaBase64Buf().slice(0, pngPrefixLength);
          expect(encPrefix).to.deep.equal(lennaPrefix);
        },
      });
    });

    describe('io imencode jpg', () => {
      const jpgPrefixLength = 12;

      const ext = '.jpg';
      const flags = [cv.IMWRITE_JPEG_QUALITY];
      generateAPITests({
        prefix: 'io imencode jpg',
        getDut: () => cv,
        methodName: 'imencode',
        getRequiredArgs: () => ([
          ext,
          got,
        ]),
        getOptionalArg: () => flags,
        expectOutput: (enc: Uint8Array) => {
          const encPrefix = enc.slice(0, jpgPrefixLength);
          const lennaPrefix = getGotBase64Buf().slice(0, jpgPrefixLength);
          expect(encPrefix).to.deep.equal(lennaPrefix);
        },
      });
    });
  });

  describe('io imdecode', () => {
    describe('io imdecode sync', () => {
      // eslint-disable-next-line @typescript-eslint/ban-ts-comment
      // @ts-ignore:next-line
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

    describe('io imdecode async', () => {
      _asyncFuncShouldRequireArgs(cv.imdecodeAsync);

      it('should decode png', async () => {
        const dec = await cv.imdecodeAsync(getLennaBase64Buf());
        assertDataDeepEquals(lenna.getDataAsArray(), dec.getDataAsArray());
      });

      it('should decode jpeg', async () => {
        const dec = await cv.imdecodeAsync(getGotBase64Buf());
        assertDataDeepEquals(got.getDataAsArray(), dec.getDataAsArray());
      });

      // describe('imdecode corruption test', async () => {
      //   it('corrupted png header image loading should throw empty Mat', async () => {
      //     imageDataCopy[0] = 0;
      //     expect(() => cv.imdecode(imageDataCopy)).to.throw('empty Mat');
      //   });
      //   it('corrupted png image size loading should throw error', async () => {
      //     imageData.copy(imageDataCopy);
      //     const IHDRChunkOffset = 8;
      //     //{
      //     //  const IHDRSize = imageDataCopy.slice(IHDRChunkOffset, IHDRChunkOffset + 4);
      //     //  const IHDRSizeLess = imageDataCopy.slice(IHDRChunkOffset + 4, IHDRChunkOffset + 21);
      //     //  const IHDRCRC = imageDataCopy.slice(IHDRChunkOffset + 21, IHDRChunkOffset + 25);
      //     //  console.log('IHDRSize:     ' + IHDRSize.toString('hex'));
      //     //  console.log('IHDRSizeLess: ' + IHDRSizeLess.toString('hex'));
      //     //  console.log('IHDRCRC:      ' + IHDRCRC.toString('hex'));
      //     //}
      //     // set wide to 0
      //     imageDataCopy[16] = 0;
      //     imageDataCopy[17] = 0;
      //     imageDataCopy[18] = 0;
      //     imageDataCopy[19] = 0;
      //     const offset = IHDRChunkOffset + 21;
      //     imageDataCopy[offset + 0] = 0x23;
      //     imageDataCopy[offset + 1] = 0x76;
      //     imageDataCopy[offset + 2] = 0xFA;
      //     imageDataCopy[offset + 3] = 0x6C;
      //     expect(() => cv.imdecode(imageDataCopy)).to.throw('empty Mat');
      //   });
      // })
    });
  });
}
