import './openCV.js';

declare module "./openCV.js" {
  export class Size {
    readonly width: number;
    readonly height: number;
    constructor();
    constructor(width: number, height: number);
  }
}