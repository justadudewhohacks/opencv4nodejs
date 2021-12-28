import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class MultiTracker {
    constructor();
    addBOOSTING(frame: Mat, boundingBox: Rect): boolean;
    addKCF(frame: Mat, boundingBox: Rect): boolean;
    addMEDIANFLOW(frame: Mat, boundingBox: Rect): boolean;
    addMil(frame: Mat, boundingBox: Rect): boolean;
    addTLD(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect[];
  }
}