export class Point {
  add(otherPoint: Point): Point;
  at(index: number): number;
  div(s: number): Point;
  mul(s: number): Point;
  norm(): number;
  sub(otherPoint: Point): Point;
}
