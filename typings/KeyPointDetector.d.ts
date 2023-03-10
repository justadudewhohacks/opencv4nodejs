import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';

export class KeyPointDetector {
  detect(image: Mat, mask?: Mat): KeyPoint[];
  detectAsync(image: Mat, mask?: Mat): Promise<KeyPoint[]>;
}
