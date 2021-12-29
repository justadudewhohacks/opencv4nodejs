import { KeyPointDetector } from './KeyPointDetector';

export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class FASTDetector extends KeyPointDetector {
    readonly threshold: number;
    readonly type: number;
    readonly nonmaxSuppression: boolean;
    constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
    constructor(params: { threshold?: number, nonmaxSuppression?: boolean, type?: number });
  }
}