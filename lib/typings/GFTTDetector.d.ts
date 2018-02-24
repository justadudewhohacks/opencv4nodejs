import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class GFTTDetector {
  readonly maxCorners: number;
  readonly blockSize: number;
  readonly qualityLevel: number;
  readonly minDistance: number;
  readonly k: number;
  readonly useHarrisDetector: boolean;
  constructor(maxCorners?: number, qualityLevel?: number, minDistance?: number, blockSize?: number, useHarrisDetector?: boolean, k?: number);
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
