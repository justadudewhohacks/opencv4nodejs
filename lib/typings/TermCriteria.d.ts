export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class TermCriteria {
    readonly type: number;
    readonly maxCount: number;
    readonly epsilon: number;
    constructor();
    constructor(type: number, maxCount: number, epsilon: number);
  }
}