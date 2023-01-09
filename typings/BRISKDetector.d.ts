import { FeatureDetector } from './FeatureDetector';

export interface BRISKDetectorProps {
  thresh?: number;
  octaves?: number;
  patternScale?: number;
}

export class BRISKDetector extends FeatureDetector {
  readonly thresh: number;
  readonly octaves: number;
  readonly patternScale: number;
  constructor(thresh?: number, octaves?: number, patternScale?: number);
  constructor(params: BRISKDetectorProps);
}
