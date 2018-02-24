import { Mat } from './Mat.d';

export class LBPHFaceRecognizer {
  constructor(radius?: number, neighbors?: number, grid_x?: number, grid_y?: number, threshold?: number);
  load(file: string): void;
  predict(img: Mat): { label: number, confidence: number };
  predictAsync(img: Mat): Promise<{ label: number, confidence: number }>;
  save(file: string): void;
  train(trainImages: Mat[], labels: number[]): void;
  trainAsync(trainImages: Mat[], labels: number[]): Promise<void>;
}
