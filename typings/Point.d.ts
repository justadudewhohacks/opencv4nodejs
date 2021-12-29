export class Point {
  add<T extends Point>(otherPoint: T): T;
  at(index: number): number;
  div(s: number): this; //Point;
  mul(s: number): this; //Point;
  norm(): number;
  sub<T extends Point>(otherPoint: T): T;
}
