import { Mat } from './Mat.d';
import './openCV.js';

declare module "./openCV.js" {
  export class BackgroundSubtractorMOG2 {
    readonly history: number;
    readonly varThreshold: number;
    readonly detectShadows: boolean;
    constructor(history?: number, varThreshold?: number, detectShadows?: boolean);
    apply(frame: Mat, learningRate?: number): Mat;
  }
}