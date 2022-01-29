import { Mat } from './Mat.d';
import { Rect } from './Rect.d';

export class MultiTracker {
  constructor();
  addBOOSTING(frame: Mat, boundingBox: Rect): boolean;
  addKCF(frame: Mat, boundingBox: Rect): boolean;
  addMEDIANFLOW(frame: Mat, boundingBox: Rect): boolean;
  addMIL(frame: Mat, boundingBox: Rect): boolean;
  addTLD(frame: Mat, boundingBox: Rect): boolean;
  // openCV >= 3.4.0
  addMOSSE(frame: Mat, boundingBox: Rect): boolean;
  // openCV >= 3.4.1
  addCSRT(frame: Mat, boundingBox: Rect): boolean;
  
  update(frame: Mat): Rect[];
}
