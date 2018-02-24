import { Size } from './Size.d';
import { Rect } from './Rect.d';
import { Point2 } from './Point2.d';

export class RotatedRect {
  readonly center: Point2;
  readonly size: Size;
  readonly angle: number;
  constructor();
  constructor(center: Point2, size: Size, angle: number);
  boundingRect(): Rect;
}
