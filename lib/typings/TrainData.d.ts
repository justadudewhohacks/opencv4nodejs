import { Mat } from './Mat.d';

export class TrainData {
  readonly samples: Mat;
  readonly layout: number;
  readonly responses: Mat;
  readonly varType: number[];
  constructor(samples: Mat, layout: number, responses: Mat, varIdx?: number[], sampleIdx?: number[], sampleWeights?: number[], varType?: number[]);
}
