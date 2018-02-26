import { KeyPointDetector } from './KeyPointDetector';

export class FASTDetector extends KeyPointDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  constructor(params: { threshold?: number, nonmaxSuppression?: boolean, type?: number });
}
