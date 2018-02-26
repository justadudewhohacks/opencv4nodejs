import { Size } from './Size.d';

export class Rect {
  readonly x: number;
  readonly y: number;
  readonly width: number;
  readonly height: number;
  constructor();
  constructor(x: number, y: number, width: number, height: number);
  and(rect2: Rect): Rect;
  or(rect2: Rect): Rect;
  pad(factor: number): Rect;
  pad(size: Size): Rect;
  padAsync(factor: number): Promise<Rect>;
  padAsync(size: Size): Promise<Rect>;
  rescale(factor: number): Rect;
  rescaleAsync(factor: number): Promise<Rect>;
  toSquare(): Rect;
  toSquareAsync(): Promise<Rect>;
}
