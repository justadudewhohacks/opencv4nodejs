import { KeyPointDetector } from './KeyPointDetector';

export class FASTDetector extends KeyPointDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  constructor(params: { threshold?: number, nonmaxSuppression?: boolean, type?: number });
}

export class FASTDetectorType {
  static TYPE_9_16: number;
  static TYPE_7_12: number;
}