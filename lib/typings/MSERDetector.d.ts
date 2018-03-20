import { KeyPointDetector } from './KeyPointDetector.d';
import { Point2 } from './Point2.d';
import { Rect } from './Rect.d';
import { Mat } from './Mat.d';

export class MSERDetector extends KeyPointDetector {
  readonly delta: number;
  readonly minArea: number;
  readonly maxArea: number;
  readonly maxEvolution: number;
  readonly edgeBlurSize: number;
  readonly maxVariation: number;
  readonly minDiversity: number;
  readonly areaThreshold: number;
  readonly minMargin: number;
  constructor(delta?: number, minArea?: number, maxArea?: number, maxVariation?: number, minDiversity?: number, maxEvolution?: number, areaThreshold?: number, minMargin?: number, edgeBlurSize?: number);
  constructor(params: { delta?: number, minArea?: number, maxArea?: number, maxVariation?: number, minDiversity?: number, maxEvolution?: number, areaThreshold?: number, minMargin?: number, edgeBlurSize?: number });
  detectRegions(image: Mat): { msers: Point2[][], bboxes: Rect[] };
  detectRegionsAsync(image: Mat): Promise< { msers: Point2[][], bboxes: Rect[] }>;
}
