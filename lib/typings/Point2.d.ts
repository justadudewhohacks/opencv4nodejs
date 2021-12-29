import { Point } from './Point.d';
import './openCV.js';

declare module "./openCV.js" {
  export class Point2 extends Point {
    readonly x: number;
    readonly y: number;
    constructor(x: number, y: number);
  }
}