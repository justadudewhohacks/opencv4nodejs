/* eslint-disable arrow-body-style */
/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable no-unused-vars */
import { cv as realCV, Mat } from '@u4/opencv4nodejs';
import fs from 'fs';
import path from 'path';
import generateClassMethodTestsFactory from '../utils/generateClassMethodTests';

export type OpenCV = typeof realCV

export interface APITestOpts {
    prefix?: string,
    getDut?: () => any,
    methodName?: string,
    methodNameSpace?: string,
    expectOutput?: (res: any, dut: any, args: any) => void,
    getOptionalArg?: () => any,
    getOptionalArgsMap?: () => { [key: string]: any },

    getClassInstance: () => any,
    classNameSpace?: string,

    getRequiredArgs?: () => any[],
    // getOptionalParamsMap?: () => Array<[string, any]|[string]|[number]>,
    getOptionalParams?: () => Array<string | number>,
    getOptionalParamsMap?: () => Array<[string, any]>,

    hasAsync: boolean,
    otherSyncTests: () => void,
    otherAsyncCallbackedTests: () => void,
    otherAsyncPromisedTests: () => void,
    beforeHook: () => void,
    afterHook: () => void
}

const matTypeNames = [
  'CV_8UC1', 'CV_8UC2', 'CV_8UC3', 'CV_8UC4',
  'CV_8SC1', 'CV_8SC2', 'CV_8SC3', 'CV_8SC4',
  'CV_16UC1', 'CV_16UC2', 'CV_16UC3', 'CV_16UC4',
  'CV_16SC1', 'CV_16SC2', 'CV_16SC3', 'CV_16SC4',
  'CV_32SC1', 'CV_32SC2', 'CV_32SC3', 'CV_32SC4',
  'CV_32FC1', 'CV_32FC2', 'CV_32FC3', 'CV_32FC4',
  'CV_64FC1', 'CV_64FC2', 'CV_64FC3', 'CV_64FC4',
];

export class TestContext {
  public dataPrefix = '../data';

  public getTestImg: () => Mat;

  public getPeoplesTestImg?: () => Mat;

  constructor(public cv: OpenCV, getTestImg: () => Mat, getPeoplesTestImg?: () => Mat) {
    this.getTestImg = getTestImg;
    this.getPeoplesTestImg = getPeoplesTestImg;
    this.generateClassMethodTests = generateClassMethodTestsFactory(cv);
  }

  public generateIts = (msg: string, testFunc: Function, exclusions = new Set<string>()): void => {
    return matTypeNames.filter((type) => !exclusions.has(type)).forEach((type) => {
      it(`${type} ${msg}`, () => testFunc(this.cv[type]));
    });
  };

  public cvVersionGreaterEqual = (major: number, minor: number, revision: number): boolean => {
    return this.cv.version.major > major
            || (this.cv.version.major === major && this.cv.version.minor > minor)
            || (this.cv.version.major === major && this.cv.version.minor === minor && this.cv.version.revision >= revision);
  };

  public cvVersionLowerThan = (major: number, minor: number, revision: number): boolean => {
    return !this.cvVersionGreaterEqual(major, minor, revision);
  };

  public cvVersionEqual = (major: number, minor: number, revision: number): boolean => {
    return this.cv.version.major === major && this.cv.version.minor === minor && this.cv.version.revision === revision;
  };

  // eslint-disable-next-line class-methods-use-this
  public getNodeMajorVersion = (): number => {
    return parseInt(process.version.split('.')[0].slice(1));
  };

  public generateClassMethodTests: (opts: Partial<APITestOpts>) => void;

  public getTestImagePath = (isPng = true): string => {
    return this.dataPrefix + (isPng ? '/Lenna.png' : '/got.jpg');
  };

  public getTestVideoPath = (): string => {
    return `${this.dataPrefix}/traffic.mp4`;
  };

  public readTestImage = () => {
    return new this.cv.Mat(fs.readFileSync(path.resolve(__dirname, '../utils/Lenna.data')), 512, 512, this.cv.CV_8UC3);
  };

  public readPeoplesTestImage = () => {
    return new this.cv.Mat(fs.readFileSync(path.resolve(__dirname, '../utils/people.data')), 360, 640, this.cv.CV_8UC3);
  };
}
