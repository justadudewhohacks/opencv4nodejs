import { KeyPointDetector } from './KeyPointDetector';

export interface FASTDetectorProps {
  threshold?: number;
  nonmaxSuppression?: boolean;
  type?: number;
}

export class FASTDetector extends KeyPointDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  constructor(params: FASTDetectorProps);
}

export class FASTDetectorType {
  static TYPE_9_16: number;
  static TYPE_7_12: number;
}