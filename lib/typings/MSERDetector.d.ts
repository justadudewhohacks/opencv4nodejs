import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class MSERDetector {
  readonly delta: number;
  readonly minArea: number;
  readonly maxArea: number;
  readonly maxEvolution: number;
  readonly edgeBlurSize: number;
  readonly maxVariation: number;
  readonly minDiversity: number;
  readonly areaThreshold: number;
  readonly minMargin: number;
  constructor(delta?: number, minArea?: number, maxArea?: number, maxVariation?: number, minDiversity?: number, maxEvolution?: number, areaThreshold?: number, minMargin?: number, edgeBlurSize?: number);
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
