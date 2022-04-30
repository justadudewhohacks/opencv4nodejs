export class Vec {
  absdiff(otherVec: Vec): Vec;
  add(otherVec: Vec): Vec;
  at(index: number): number;
  cross(v?: Vec): Vec;
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
