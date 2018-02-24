import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class SURFDetector {
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly hessianThreshold: number;
  readonly extended: boolean;
  readonly upright: boolean;
  constructor(hessianThreshold?: number, nOctaves?: number, nOctaveLayers?: number, extended?: boolean, upright?: boolean);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
