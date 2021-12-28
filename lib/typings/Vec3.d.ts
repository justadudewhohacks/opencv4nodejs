import { Vec } from './Vec.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class Vec3 extends Vec {
    readonly x: number;
    readonly y: number;
    readonly z: number;
    constructor(x: number, y: number, z: number);
  }
}