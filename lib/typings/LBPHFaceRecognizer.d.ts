import { FaceRecognizer } from './FaceRecognizer';
export * as cv from './cv';

declare module "./openCV.js" {
  export class LBPHFaceRecognizer extends FaceRecognizer {
    constructor(radius?: number, neighbors?: number, grid_x?: number, grid_y?: number, threshold?: number);
  }
}