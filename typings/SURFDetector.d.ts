import { FeatureDetector } from './FeatureDetector.d';

export interface SURFDetectorPrams {
  hessianThreshold?: number;
  nOctaves?: number;
  nOctaveLayers?: number;
  extended?: boolean;
  upright?: boolean;
}

export class SURFDetector extends FeatureDetector {
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly hessianThreshold: number;
  readonly extended: boolean;
  readonly upright: boolean;
  constructor(hessianThreshold?: number, nOctaves?: number, nOctaveLayers?: number, extended?: boolean, upright?: boolean);
  constructor(params: SURFDetectorPrams);
}
