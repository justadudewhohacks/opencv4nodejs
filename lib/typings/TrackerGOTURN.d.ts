import { Mat } from './Mat.d';
import { Rect } from './Rect.d';

export class TrackerGOTURN {
  constructor();
  clear(): void;
  init(frame: Mat, boundingBox: Rect): boolean;
  update(frame: Mat): Rect;
}
