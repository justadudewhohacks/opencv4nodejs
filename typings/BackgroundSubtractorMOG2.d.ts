import { Mat } from './Mat.d';

export interface BackgroundSubtractorMOG2Props {
  history?: number;
  varThreshold?: number;
  detectShadows?: boolean;
}

export class BackgroundSubtractorMOG2 {
  readonly history: number;
  readonly varThreshold: number;
  readonly detectShadows: boolean;
  constructor(history?: number, varThreshold?: number, detectShadows?: boolean);
  constructor(opt: BackgroundSubtractorMOG2Props);
  apply(frame: Mat, learningRate?: number): Mat;
}
