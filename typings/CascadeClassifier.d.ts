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

export class CascadeClassifier {
  constructor(xmlFilePath: string);
  detectMultiScale(img: Mat, opts: detectMultiScaleProps): { objects: Rect[], numDetections: number[] };
  detectMultiScale(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): { objects: Rect[], numDetections: number[] };
  
  detectMultiScaleAsync(img: Mat, opts: detectMultiScaleProps): Promise<{ objects: Rect[], numDetections: number[] }>;
  detectMultiScaleAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<{ objects: Rect[], numDetections: number[] }>;

  detectMultiScaleGpu(img: Mat, opt: detectMultiScaleProps): { objects: Rect[], numDetections: number[] };
  detectMultiScaleGpu(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): { objects: Rect[], numDetections: number[] };

  detectMultiScaleGpuAsync(img: Mat, opt: detectMultiScaleProps): Promise<{ objects: Rect[], numDetections: number[] }>;
  detectMultiScaleGpuAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<{ objects: Rect[], numDetections: number[] }>;
  
  detectMultiScaleWithRejectLevels(img: Mat, opt: detectMultiScaleProps): { objects: Rect[], rejectLevels: number[], levelWeights: number[] };
  detectMultiScaleWithRejectLevels(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): { objects: Rect[], rejectLevels: number[], levelWeights: number[] };

  detectMultiScaleWithRejectLevelsAsync(img: Mat, opt: detectMultiScaleProps): Promise<{ objects: Rect[], rejectLevels: number[], levelWeights: number[] }>;
  detectMultiScaleWithRejectLevelsAsync(img: Mat, scaleFactor?: number, minNeighbors?: number, flags?: number, minSize?: Size, maxSize?: Size): Promise<{ objects: Rect[], rejectLevels: number[], levelWeights: number[] }>;
}
