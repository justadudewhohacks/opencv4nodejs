import { Rect } from "./Rect.d";

export class FacemarkLBFParams {
  readonly baggingOverlap: number;
  readonly cascadeFace: string;
  readonly detectROI: Rect;
  readonly featsM: number[];
  readonly initShapeN: number;
  readonly modelFilename: string;
  readonly nLandmarks: number;
  readonly pupils: number[];
  readonly radiusM: number[];
  readonly saveModel: boolean;
  readonly seed: number;
  readonly shapeOffset: number;
  readonly stagesN: number;
  readonly treeDepth: number;
  readonly treeN: number;
  readonly verbose: boolean;
  constructor();
}
