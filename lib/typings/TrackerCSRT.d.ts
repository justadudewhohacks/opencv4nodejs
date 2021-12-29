import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerCSRTParams } from './TrackerCSRTParams.d';
import './openCV.js';

declare module "./openCV.js" {
  export class TrackerCSRT {
    constructor();
    constructor(params: TrackerCSRTParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}