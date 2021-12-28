import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerBoostingParams } from './TrackerBoostingParams.d';

export * as cv from './cv';

declare module "./cv.js" {
  export class TrackerBoosting {
    constructor();
    constructor(params: TrackerBoostingParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}