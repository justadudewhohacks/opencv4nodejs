import { Mat } from './Mat.d';

export class SuperpixelSEEDS {
  readonly img: Mat;
  readonly labels: Mat;
  readonly labelContourMask: Mat;
  readonly numSuperpixels: number;
  readonly numLevels: number;
  readonly prior: number;
  readonly histogramBins: number;
  readonly numCalculatedSuperpixels: number;
  readonly doubleStep: boolean;
  constructor(img: Mat, numSuperpixels: number, numLevels: number, prior?: number, histogramBins?: number, doubleStep?: boolean);
  iterate(iterations?: number): void;
}
