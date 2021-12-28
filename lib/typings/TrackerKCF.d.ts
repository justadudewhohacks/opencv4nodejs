import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerKCFParams } from './TrackerKCFParams.d';
export * as cv from './cv';

declare module "./openCV.js" {
  export class TrackerKCF {
    constructor();
    constructor(params: TrackerKCFParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}