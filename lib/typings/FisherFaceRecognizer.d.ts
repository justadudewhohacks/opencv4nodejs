import { Mat } from './Mat.d';

export class FisherFaceRecognizer {
  constructor(num_components?: number, threshold?: number);
  load(file: string): void;
  predict(img: Mat): { label: number, confidence: number };
  predictAsync(img: Mat): Promise<{ label: number, confidence: number }>;
  save(file: string): void;
  train(trainImages: Mat[], labels: number[]): void;
  trainAsync(trainImages: Mat[], labels: number[]): Promise<void>;
}
