import { Vec } from './Vec.d';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class Vec2 extends Vec {
    readonly x: number;
    readonly y: number;
    constructor(x: number, y: number);
  }
}