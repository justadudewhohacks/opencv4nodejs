import { KeyPointDetector } from './KeyPointDetector.d';

export class AGASTDetector extends KeyPointDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  constructor(params: { threshold?: number, nonmaxSuppression?: boolean, type?: number });
}
