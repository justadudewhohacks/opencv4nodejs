import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class SIFTDetector {
  readonly nfeatures: number;
  readonly nOctaveLayers: number;
  readonly contrastThreshold: number;
  readonly edgeThreshold: number;
  readonly sigma: number;
  constructor(nfeatures?: number, nOctaveLayers?: number, contrastThreshold?: number, edgeThreshold?: number, sigma?: number);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
