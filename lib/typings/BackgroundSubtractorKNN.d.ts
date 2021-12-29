import { Mat } from './Mat.d';
import './openCV.js';

declare module "./openCV.js" {
  export class BackgroundSubtractorKNN {
    readonly history: number;
    readonly dist2Threshold: number;
    readonly detectShadows: boolean;
    constructor(history?: number, varThreshold?: number, detectShadows?: boolean);
    apply(frame: Mat, learningRate?: number): Mat;
  }
}