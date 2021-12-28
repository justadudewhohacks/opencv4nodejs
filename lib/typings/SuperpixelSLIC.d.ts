import { Mat } from './Mat.d';
export * as cv from './cv';

declare module "./openCV.js" {
  export class SuperpixelSLIC {
    readonly image: Mat;
    readonly labels: Mat;
    readonly labelContourMask: Mat;
    readonly algorithm: number;
    readonly regionSize: number;
    readonly ruler: number;
    readonly numCalculatedSuperpixels: number;
    constructor(img: Mat, algorithm?: number, regionSize?: number, ruler?: number);
    iterate(iterations?: number): void;
  }
}