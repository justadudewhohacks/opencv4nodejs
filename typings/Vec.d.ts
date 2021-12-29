import { Vec3 } from './Vec3.d';

export class Vec {
  absdiff(otherVec: Vec): Vec;
  add(otherVec: Vec): Vec;
  at(index: number): number;
  cross(): Vec3;
  div(s: number): Vec;
  exp(): Vec;
  hDiv(otherVec: Vec): Vec;
  hMul(otherVec: Vec): Vec;
  mean(): Vec;
  mul(s: number): Vec;
  norm(): number;
  sqrt(): Vec;
  sub(otherVec: Vec): Vec;
}
