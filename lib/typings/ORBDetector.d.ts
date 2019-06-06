import { FeatureDetector } from './FeatureDetector.d';

export class ORBDetector extends FeatureDetector {
  readonly maxFeatures: number;
  readonly nLevels: number;
  readonly edgeThreshold: number;
  readonly firstLevel: number;
  readonly WTA_K: number;
  readonly scoreType: number;
  readonly patchSize: number;
  readonly fastThreshold: number;
  readonly scaleFactor: number;
  constructor(maxFeatures?: number, scaleFactor?: number, nLevels?: number, edgeThreshold?: number, firstLevel?: number, WTA_K?: number, scoreType?: number, patchSize?: number, fastThreshold?: number);
  constructor(params: { maxFeatures?: number, scaleFactor?: number, nLevels?: number, edgeThreshold?: number, firstLevel?: number, WTA_K?: number, scoreType?: number, patchSize?: number, fastThreshold?: number });
}
