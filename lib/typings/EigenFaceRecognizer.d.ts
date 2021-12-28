import { FaceRecognizer } from './FaceRecognizer';
export * as cv from './cv';

declare module "./cv.js" {
  export class EigenFaceRecognizer extends FaceRecognizer {
  constructor(num_components?: number, threshold?: number);
}
}