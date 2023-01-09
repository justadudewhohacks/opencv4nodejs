import { FeatureDetector } from './FeatureDetector.d';

export interface SIFTDetectorParams {
  nFeatures?: number;
  nOctaveLayers?: number;
  contrastThreshold?: number;
  edgeThreshold?: number;
  sigma?: number;
}

export class SIFTDetector extends FeatureDetector {
  readonly nfeatures: number;
  readonly nOctaveLayers: number;
  readonly contrastThreshold: number;
  readonly edgeThreshold: number;
  readonly sigma: number;
  constructor(nFeatures?: number, nOctaveLayers?: number, contrastThreshold?: number, edgeThreshold?: number, sigma?: number);
  constructor(params: SIFTDetectorParams);
}
