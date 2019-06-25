import { Vec } from './Vec.d';

export class Vec4 extends Vec {
  readonly w: number;
  readonly x: number;
  readonly y: number;
  readonly z: number;
  constructor(w: number, x: number, y: number, z: number);
}
