import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { TrackerMILParams } from './TrackerMILParams.d';
import './openCV.js';

declare module "./openCV.js" {
  export class TrackerMIL {
    constructor();
    constructor(params: TrackerMILParams);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}