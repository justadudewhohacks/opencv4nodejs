import { Point } from './Point.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class Point2 extends Point {
    readonly x: number;
    readonly y: number;
    constructor(x: number, y: number);
  }
}