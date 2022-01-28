export class Point {
  add<T extends Point>(otherPoint: T): T;
  at(index: number): number;
  div(s: number): this;
  mul(s: number): this;
  norm(): number;
  sub<T extends Point>(otherPoint: T): T;
}
