export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class Point {
    add<T extends Point>(otherPoint: T): T;
    at(index: number): number;
    div(s: number): this; //Point;
    mul(s: number): this; //Point;
    norm(): number;
    sub<T extends Point>(otherPoint: T): T;
  }
}