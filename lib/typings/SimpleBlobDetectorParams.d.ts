export class SimpleBlobDetectorParams {
  readonly blobColor: number;
  readonly filterByArea: boolean;
  readonly filterByCircularity: boolean;
  readonly filterByColor: boolean;
  readonly filterByConvexity: boolean;
  readonly filterByInertia: boolean;
  readonly maxArea: number;
  readonly maxCircularity: number;
  readonly maxConvexity: number;
  readonly maxInertiaRatio: number;
  readonly maxThreshold: number;
  readonly minArea: number;
  readonly minCircularity: number;
  readonly minConvexity: number;
  readonly minDistBetweenBlobs: number;
  readonly minInertiaRatio: number;
  readonly minRepeatability: number;
  readonly minThreshold: number;
  readonly thresholdStep: number;
  constructor();
}
