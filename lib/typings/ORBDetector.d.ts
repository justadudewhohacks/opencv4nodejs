import { FeatureDetector } from './FeatureDetector.d';

export class ORBDetector extends FeatureDetector {
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
  constructor(params: { nfeatures?: number, scaleFactor?: number, nlevels?: number, edgeThreshold?: number, firstLevel?: number, WTA_K?: number, scoreType?: number, patchSize?: number, fastThreshold?: number });
}
