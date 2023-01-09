import { Mat } from './Mat.d';

export interface TrainDataParams {
  varIdx?: number[];
  sampleIdx?: number[];
  sampleWeights?: number[];
  varType?: number[];
}

export class TrainData {
  readonly layout: number;
  readonly samples: Mat;
  readonly responses: Mat;
  readonly varIdx: number[];
  readonly sampleWeights: number[];
  readonly varType: number[];
  constructor(samples: Mat, layout: number, responses: Mat, varIdx?: number[], sampleIdx?: number[], sampleWeights?: number[], varType?: number[]);
  constructor(samples: Mat, layout: number, responses: Mat, opt: TrainDataParams);
}
