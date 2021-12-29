import { FeatureDetector } from './FeatureDetector.d';
import './openCV.js';

declare module "./openCV.js" {
  export class SURFDetector extends FeatureDetector {
    readonly nOctaves: number;
    readonly nOctaveLayers: number;
    readonly hessianThreshold: number;
    readonly extended: boolean;
    readonly upright: boolean;
    constructor(hessianThreshold?: number, nOctaves?: number, nOctaveLayers?: number, extended?: boolean, upright?: boolean);
    constructor(params: { hessianThreshold?: number, nOctaves?: number, nOctaveLayers?: number, extended?: boolean, upright?: boolean });
  }
}