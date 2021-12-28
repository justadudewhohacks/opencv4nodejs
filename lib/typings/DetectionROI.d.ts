import { Point2 } from './Point2.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class DetectionROI {
    readonly scale: number;
    readonly locations: Point2[];
    readonly confidences: number[];
    constructor();
  }
}