import { cv, Point2, Point3 } from '@u4/opencv4nodejs';
import { Mat, Vec2, Vec3, Vec4 } from '../../typings';

export type OpenCV = typeof cv

export interface APITestOpts {
    getDut?: any,
    methodName?: string,
    methodNameSpace?: string,
    expectOutput?: (res: any, dut: any, args: any) => void,
    getOptionalArg?: () => any, 
    getOptionalArgsMap?: () => {[key: string]: any},


    getClassInstance: () => any,
    classNameSpace?: string,

    getRequiredArgs?: () => any,
    // getOptionalParamsMap?: () => Array<[string, any]|[string]|[number]>,
    getOptionalParams?: () => Array<string|number>,
    getOptionalParamsMap?: () => Array<[string, any]>,

    hasAsync: boolean,
    otherSyncTests: () => void,
    otherAsyncCallbackedTests: () => void,
    otherAsyncPromisedTests: () => void,
    beforeHook: () => any,
    afterHook: () => any  
}

export interface TestContext {
    cv: OpenCV,
    utils: {
        funcShouldRequireArgs: (func: () => any) => void;
        assertPropsWithValue: (obj: any) => (props: any, floatSafe ?: boolean) => void;
        expectToBeVec2: (vec: Vec2 | Point2) => void;
        expectToBeVec3: (vec: Vec3 | Point3) => void;
        expectToBeVec4: (vec: Vec4) => void;
    
        assertError: (func: () => any, msg: string) => void;
        assertDataDeepEquals: (data0: any, data1: any) => void;
        assertDataAlmostDeepEquals: (data0: any, data1: any) => void;
        assertMatValueAlmostEquals: (val0: number, val1: number) => void;
        assertMatValueEquals: (val0: number, val1: number) => void;
        assertMetaData: (mat: Mat | number[]) => (arg0: any, cols?: any, type?: any) => void;
        dangerousDeepEquals: (obj0: any, obj1: any) => boolean;
        generateIts: (msg: string, testFunc: Function, exclusions?: Set<string>) => void;
        isZeroMat: (mat: Mat) => boolean;
        isUniformMat: (mat: Mat, matVal: number) => boolean;
        MatValuesComparator: (mat0: Mat, mat1: Mat) => (cmpFunc: (a: number, b: number) => void) => void;

        cvVersionGreaterEqual: (major: number, minor: number, revision: number) => boolean;
        cvVersionLowerThan: (major: number, minor: number, revision: number) => boolean;
        cvVersionEqual: (major: number, minor: number, revision: number) => boolean;
        generateAPITests: (opts: Partial<APITestOpts>) => void,
        generateClassMethodTests: (opts) => void;
        getNodeMajorVersion: () => number;

        getTestVideoPath?: () => string;
        getTestImagePath?: (isPng?: boolean) => string;

        clearTmpData?: () => void;
        getTmpDataFilePath?: (file: string) => string;
        fileExists?: (filePath: string) => boolean;
        _asyncFuncShouldRequireArgs?: (func: (...args: any[]) => any) => void;
        asyncFuncShouldRequireArgs?: (func: (...args: any[]) => any) => void;
        _funcShouldRequireArgs?: (func: () => any) => void
        expectFloat?: (val: number, expected: number) => Chai.Assertion;
        readTestImage?: () => Mat;
        readPeoplesTestImage?: () => Mat;
    },
    getTestImg: () => Mat;
    getPeoplesTestImg?: () => Mat;
}

