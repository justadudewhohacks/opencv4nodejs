import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';

export class KeyPointDetector {
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
