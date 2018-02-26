import { FeatureDetector } from './FeatureDetector';

export class BRISKDetector extends FeatureDetector {
  readonly thresh: number;
  readonly octaves: number;
  readonly patternScale: number;
  constructor(thresh?: number, octaves?: number, patternScale?: number);
  constructor(params: { thresh?: number, octaves?: number, patternScale?: number });
}
