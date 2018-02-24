import { Mat } from './Mat.d';
import { KeyPoint } from './KeyPoint.d';

export class AKAZEDetector {
  readonly descriptorType: number;
  readonly descriptorSize: number;
  readonly descriptorChannels: number;
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly diffusivity: number;
  readonly threshold: number;
  constructor(descriptorType?: number, descriptorSize?: number, descriptorChannels?: number, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
