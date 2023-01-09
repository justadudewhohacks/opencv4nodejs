import { Rect } from "./Rect.d";

export interface IFacemarkLBFParams {
  baggingOverlap: number;
  cascadeFile: string;
  // cascadeFace: string;
  detectROI: Rect;
  featsM: number[];
  initShapeN: number;
  modelFilename: string;
  nLandmarks: number;
  pupils: number[][];
  radiusM: number[];
  saveModel: boolean;
  seed: number;
  shapeOffset: number;
  stagesN: number;
  treeDepth: number;
  treeN: number;
  verbose: boolean;
}


export class FacemarkLBFParams {
  readonly baggingOverlap: number;
  readonly cascadeFile: string;
  // readonly cascadeFace: string;
  readonly detectROI: Rect;
  readonly featsM: number[];
  readonly initShapeN: number;
  readonly modelFilename: string;
  readonly nLandmarks: number;
  readonly pupils: number[][];
  readonly radiusM: number[];
  readonly saveModel: boolean;
  readonly seed: number;
  readonly shapeOffset: number;
  readonly stagesN: number;
  readonly treeDepth: number;
  readonly treeN: number;
  readonly verbose: boolean;
  constructor(params?: Partial<IFacemarkLBFParams>);
}
