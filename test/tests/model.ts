/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable no-unused-vars */
import { cv, Mat } from '@u4/opencv4nodejs';

export type OpenCV = typeof cv

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

export interface TestContext {
    cv: OpenCV,
    utils: {
        funcShouldRequireArgs: (func: () => any) => void;
        generateIts: (msg: string, testFunc: (t: number) => void, exclusions?: Set<string>) => void;
        cvVersionGreaterEqual: (major: number, minor: number, revision: number) => boolean;
        cvVersionLowerThan: (major: number, minor: number, revision: number) => boolean;
        cvVersionEqual: (major: number, minor: number, revision: number) => boolean;
        generateAPITests: (opts: Partial<APITestOpts>) => void,
        generateClassMethodTests: (opts) => void;
        getNodeMajorVersion: () => number;
        getTestVideoPath?: () => string;
        getTestImagePath?: (isPng?: boolean) => string;
        readTestImage?: () => Mat;
        readPeoplesTestImage?: () => Mat;
    },
    getTestImg: () => Mat;
    getPeoplesTestImg?: () => Mat;
}
