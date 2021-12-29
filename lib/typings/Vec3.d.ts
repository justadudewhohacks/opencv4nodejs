import { Vec } from './Vec.d';
import './openCV.js';

declare module "./openCV.js" {
  export class Vec3 extends Vec {
    readonly x: number;
    readonly y: number;
    readonly z: number;
    constructor(x: number, y: number, z: number);
  }
}