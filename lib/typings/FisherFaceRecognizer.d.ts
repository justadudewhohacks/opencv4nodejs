import { FaceRecognizer } from './FaceRecognizer';
export * as cv from './cv';

declare module "./cv.js" {
  export class FisherFaceRecognizer extends FaceRecognizer {
    constructor(num_components?: number, threshold?: number);
  }
}