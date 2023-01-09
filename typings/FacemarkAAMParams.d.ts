import { Facemark } from "./Facemark";

export class FacemarkAAM extends Facemark { }

export interface FacemarkAAMParamsI {
  m: number;
  maxM: number;
  maxN: number;
  modelFilename: string;
  n: number;
  nIter: number;
  saveModel: boolean;
  scales: number[];
  textureMaxM: number;
  verbose: boolean;
}

export class FacemarkAAMParams {
  readonly m: number;
  readonly maxM: number;
  readonly maxN: number;
  readonly modelFilename: string;
  readonly n: number;
  readonly nIter: number;
  readonly saveModel: boolean;
  readonly scales: number[];
  readonly textureMaxM: number;
  readonly verbose: boolean;
  constructor(param?: Partial<FacemarkAAMParamsI>);
}

export class FacemarkAAMData {
  s0: Point2[]; // was string 
}