import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';

export class BRISKDetector {
  readonly thresh: number;
  readonly octaves: number;
  readonly patternScale: number;
  constructor(thresh?: number, octaves?: number, patternScale?: number);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
