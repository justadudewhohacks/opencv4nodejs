import { Mat } from './Mat.d';

export class SuperpixelSEEDS {
  readonly image: Mat;
  readonly labels: Mat;
  readonly labelContourMask: Mat;
  readonly num_superpixels: number;
  readonly num_levels: number;
  readonly prior: number;
  readonly histogramBins: number;
  readonly numCalculatedSuperpixels: number;
  readonly doubleStep: boolean;
  constructor(img: Mat, num_superpixels: number, num_levels: number, prior?: number, histogramBins?: number, doubleStep?: boolean);
  iterate(iterations?: number): void;
}
