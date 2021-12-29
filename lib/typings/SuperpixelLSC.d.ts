import { Mat } from './Mat.d';
import './openCV.js';

declare module "./openCV.js" {
  export class SuperpixelLSC {
    readonly image: Mat;
    readonly labels: Mat;
    readonly labelContourMask: Mat;
    readonly regionSize: number;
    readonly ratio: number;
    readonly numCalculatedSuperpixels: number;
    constructor(img: Mat, regionSize?: number, ratio?: number);
    iterate(iterations?: number): void;
  }
}