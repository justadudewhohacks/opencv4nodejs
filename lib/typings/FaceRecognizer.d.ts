import { Mat } from './Mat';

export class FaceRecognizer {
  load(file: string): void;
  predict(img: Mat): { label: number, confidence: number };
  predictAsync(img: Mat): Promise<{ label: number, confidence: number }>;
  save(file: string): void;
  train(trainImages: Mat[], labels: number[]): void;
  trainAsync(trainImages: Mat[], labels: number[]): Promise<void>;
}