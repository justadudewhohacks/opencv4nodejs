import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerMILParams } from './TrackerMILParams.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class TrackerMIL {
    constructor();
    constructor(params: TrackerMILParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}