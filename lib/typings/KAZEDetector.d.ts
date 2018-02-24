import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class KAZEDetector {
  readonly extended: boolean;
  readonly upright: boolean;
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly diffusivity: number;
  readonly threshold: number;
  constructor(extended?: boolean, upright?: boolean, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
