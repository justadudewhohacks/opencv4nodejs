import { Mat } from './Mat.d';
import { Rect } from './Rect.d';

export class TrackerMOSSE {
  constructor();
  clear(): void;
  init(frame: Mat, boundingBox: Rect): boolean;
  update(frame: Mat): Rect;
}
