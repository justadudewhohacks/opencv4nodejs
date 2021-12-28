import { KeyPointDetector } from './KeyPointDetector';
export * as cv from './cv';

declare module "./openCV.js" {

  export class GFTTDetector extends KeyPointDetector {
    readonly maxFeatures: number;
    readonly blockSize: number;
    readonly qualityLevel: number;
    readonly minDistance: number;
    readonly k: number;
    readonly harrisDetector: boolean;
    constructor(maxFeatures?: number, qualityLevel?: number, minDistance?: number, blockSize?: number, harrisDetector?: boolean, k?: number);
    constructor(params: { maxFeatures?: number, qualityLevel?: number, minDistance?: number, blockSize?: number, harrisDetector?: boolean, k?: number });
  }
}