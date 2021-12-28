export * as cv from './cv';

declare module "./cv.js" {
  export class TermCriteria {
    readonly type: number;
    readonly maxCount: number;
    readonly epsilon: number;
    constructor();
    constructor(type: number, maxCount: number, epsilon: number);
  }
}