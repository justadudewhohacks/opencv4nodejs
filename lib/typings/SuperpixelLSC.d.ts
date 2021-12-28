import { Mat } from './Mat.d';
export * as cv from './cv';

declare module "./cv.js" {
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