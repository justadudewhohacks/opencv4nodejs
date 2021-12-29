import { Point2 } from './Point2.d';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class DetectionROI {
    readonly scale: number;
    readonly locations: Point2[];
    readonly confidences: number[];
    constructor();
  }
}