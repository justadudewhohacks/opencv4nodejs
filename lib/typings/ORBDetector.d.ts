import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class ORBDetector {
  readonly nfeatures: number;
  readonly nlevels: number;
  readonly edgeThreshold: number;
  readonly firstLevel: number;
  readonly WTA_K: number;
  readonly scoreType: number;
  readonly patchSize: number;
  readonly fastThreshold: number;
  readonly scaleFactor: number;
  constructor(nfeatures?: number, scaleFactor?: number, nlevels?: number, edgeThreshold?: number, firstLevel?: number, WTA_K?: number, scoreType?: number, patchSize?: number, fastThreshold?: number);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
