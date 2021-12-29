import { Mat } from './Mat.d';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class TrainData {
    readonly samples: Mat;
    readonly layout: number;
    readonly responses: Mat;
    readonly varType: number[];
    constructor(samples: Mat, layout: number, responses: Mat, varIdx?: number[], sampleIdx?: number[], sampleWeights?: number[], varType?: number[]);
  }
}