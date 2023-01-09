import { Size } from './Size.d';
import { Mat } from './Mat.d';
import { Rect } from './Rect.d';

export interface detectMultiScaleProps {
  scaleFactor?: number;
  minNeighbors?: number;
  flags?: number;
  minSize?: Size;
  maxSize?: Size;
}

export interface DetectMultiScaleRet {
  objects: Rect[];
  numDetections: number[];
}

export interface DetectMultiScaleWithRejectLevels {
  objects: Rect[];
  rejectLevels: number[];
  levelWeights: number[];
}

export class CascadeClassifier {
  constructor(xmlFilePath: string);
  detectMultiScale(img: Mat, opts: detectMultiScaleProps): DetectMultiScaleRet;
  detectMultiScale(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): DetectMultiScaleRet;
  
  detectMultiScaleAsync(img: Mat, opts: detectMultiScaleProps): Promise<DetectMultiScaleRet>;
  detectMultiScaleAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<DetectMultiScaleRet>;

  detectMultiScaleGpu(img: Mat, opt: detectMultiScaleProps): DetectMultiScaleRet;
  detectMultiScaleGpu(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): DetectMultiScaleRet;

  detectMultiScaleGpuAsync(img: Mat, opt: detectMultiScaleProps): Promise<DetectMultiScaleRet>;
  detectMultiScaleGpuAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<DetectMultiScaleRet>;
  
  detectMultiScaleWithRejectLevels(img: Mat, opt: detectMultiScaleProps): DetectMultiScaleWithRejectLevels;
  detectMultiScaleWithRejectLevels(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): DetectMultiScaleWithRejectLevels;

  detectMultiScaleWithRejectLevelsAsync(img: Mat, opt: detectMultiScaleProps): Promise<DetectMultiScaleWithRejectLevels>;
  detectMultiScaleWithRejectLevelsAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<DetectMultiScaleWithRejectLevels>;
}
