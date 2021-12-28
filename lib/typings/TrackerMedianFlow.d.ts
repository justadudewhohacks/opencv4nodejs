import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
export * as cv from './cv';

declare module "./openCV.js" {
  export class TrackerMedianFlow {
    constructor(pointsInGrid?: number);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}