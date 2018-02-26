import { KeyPointDetector } from './KeyPointDetector';

export class GFTTDetector  extends KeyPointDetector {
  readonly maxCorners: number;
  readonly blockSize: number;
  readonly qualityLevel: number;
  readonly minDistance: number;
  readonly k: number;
  readonly useHarrisDetector: boolean;
  constructor(maxCorners?: number, qualityLevel?: number, minDistance?: number, blockSize?: number, useHarrisDetector?: boolean, k?: number);
  constructor(params: { maxCorners?: number, qualityLevel?: number, minDistance?: number, blockSize?: number, useHarrisDetector?: boolean, k?: number });
}
