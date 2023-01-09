import { Mat } from './Mat.d';

export interface BackgroundSubtractorKNNProps {
  history?: number;
  dist2Threshold?: number;
  detectShadows?: boolean;
}

export class BackgroundSubtractorKNN {
  readonly history: number;
  readonly dist2Threshold: number;
  readonly detectShadows: boolean;
  constructor(history?: number, dist2Threshold?: number, detectShadows?: boolean);
  constructor(opt: BackgroundSubtractorKNNProps);
  apply(frame: Mat, learningRate?: number): Mat;
}
