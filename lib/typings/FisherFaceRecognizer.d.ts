import { FaceRecognizer } from './FaceRecognizer';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class FisherFaceRecognizer extends FaceRecognizer {
    constructor(num_components?: number, threshold?: number);
  }
}