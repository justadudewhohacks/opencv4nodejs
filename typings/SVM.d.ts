import { Mat } from './Mat.d';
import { TrainData } from './TrainData.d';
import { ParamGrid } from './ParamGrid.d';

export class SVM {
  readonly c: number;
  readonly coef0: number;
  readonly degree: number;
  readonly gamma: number;
  readonly nu: number;
  readonly p: number;
  readonly kernelType: number;
  readonly classWeights: Mat;
  readonly varCount: number;
  readonly isTrained: boolean;
  constructor(c?: number, coef0?: number, degree?: number, gamma?: number, nu?: number, p?: number, kernelType?: number, classWeights?: Mat);
  constructor(params: { c?: number, coef0?: number, degree?: number, gamma?: number, nu?: number, p?: number, kernelType?: number, classWeights?: Mat });
  calcError(trainData: TrainData, test: boolean): { error: number, responses: Mat };
  getSupportVectors(): Mat;
  getDecisionFunction(): { rho: number, alpha: Mat, svidx: Mat };
  load(file: string): void;
  predict(sample: number[], flags?: number): number;
  predict(samples: Mat, flags?: number): number[];
  save(file: string): void;
  setParams(c?: number, coef0?: number, degree?: number, gamma?: number, nu?: number, p?: number, kernelType?: number, classWeights?: Mat): void;
  train(trainData: TrainData, flags?: number): boolean;
  train(samples: Mat, layout: number, responses: Mat): boolean;
  trainAsync(trainData: TrainData, flags?: number): Promise<boolean>;
  trainAsync(samples: Mat, layout: number, responses: Mat): Promise<boolean>;
  trainAuto(trainData: TrainData, kFold?: number, cGrid?: ParamGrid, gammaGrid?: ParamGrid, pGrid?: ParamGrid, nuGrid?: ParamGrid, coeffGrid?: ParamGrid, degreeGrid?: ParamGrid, balanced?: boolean): Mat;
  trainAutoAsync(trainData: TrainData, kFold?: number, cGrid?: ParamGrid, gammaGrid?: ParamGrid, pGrid?: ParamGrid, nuGrid?: ParamGrid, coeffGrid?: ParamGrid, degreeGrid?: ParamGrid, balanced?: boolean): Promise<Mat>;
}
