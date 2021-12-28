import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class TrackerKCF {
    constructor();
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}