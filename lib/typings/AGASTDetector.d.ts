import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';

export class AGASTDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
