import { FaceRecognizer } from './FaceRecognizer';

export class LBPHFaceRecognizer extends FaceRecognizer {
  constructor(args: {radius?: number, neighbors?: number, grid_x?: number, grid_y?: number, threshold?: number});
  constructor(radius?: number, neighbors?: number, grid_x?: number, grid_y?: number, threshold?: number);
}
