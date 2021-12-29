import { FaceRecognizer } from './FaceRecognizer';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class EigenFaceRecognizer extends FaceRecognizer {
  constructor(num_components?: number, threshold?: number);
}
}