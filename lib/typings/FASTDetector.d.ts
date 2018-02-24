import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class FASTDetector {
  readonly threshold: number;
  readonly type: number;
  readonly nonmaxSuppression: boolean;
  constructor(threshold?: number, nonmaxSuppression?: boolean, type?: number);
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
