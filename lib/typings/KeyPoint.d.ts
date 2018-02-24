import { Point2 } from './Point2.d';

export class KeyPoint {
  readonly point: Point2;
  readonly size: number;
  readonly angle: number;
  readonly response: number;
  readonly octave: number;
  readonly classId: number;
  readonly localId: number;
  constructor(point: Point2, size: number, angle: number, response: number, octave: number, classId: number);
}
