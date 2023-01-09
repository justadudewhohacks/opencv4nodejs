import { FaceRecognizer } from './FaceRecognizer';

export class EigenFaceRecognizer extends FaceRecognizer {
  constructor(args: {num_components?: number, threshold?: number});
  constructor(num_components?: number, threshold?: number);
}
