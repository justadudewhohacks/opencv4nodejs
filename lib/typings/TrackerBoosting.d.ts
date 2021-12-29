import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerBoostingParams } from './TrackerBoostingParams.d';

import './openCV.js';

declare module "./openCV.js" {
  export class TrackerBoosting {
    constructor();
    constructor(params: TrackerBoostingParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}