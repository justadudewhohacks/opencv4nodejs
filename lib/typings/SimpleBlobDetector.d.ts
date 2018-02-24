import { Mat } from './Mat.d';
import { SimpleBlobDetectorParams } from './SimpleBlobDetectorParams.d';
import { KeyPoint } from './KeyPoint.d';

export class SimpleBlobDetector {
  constructor(params: SimpleBlobDetectorParams);
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
  detect(image: Mat): KeyPoint[];
  detectAsync(image: Mat): Promise<KeyPoint[]>;
}
