import { KeyPointDetector } from './KeyPointDetector';
import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';

export class FeatureDetector extends KeyPointDetector {
  compute(image: Mat, keypoints: KeyPoint[]): Mat;
  computeAsync(image: Mat, keypoints: KeyPoint[]): Promise<Mat>;
}
