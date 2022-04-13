export class TermCriteria {
  readonly type: number;
  readonly maxCount: number;
  readonly epsilon: number;
  constructor();
  constructor(type: number, maxCount: number, epsilon: number);
}
