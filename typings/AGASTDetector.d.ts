import { KeyPointDetector } from './KeyPointDetector.d';

export interface AGASTDetectorProps {
  threshold?: number;
  nonmaxSuppression?: boolean;
  type?: number;
}

export class AGASTDetector extends KeyPointDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  constructor(params: AGASTDetectorProps);
}

export class AGASTDetectorType {
  static OAST_9_16: number;
  static AGAST_7_12d: number;
}