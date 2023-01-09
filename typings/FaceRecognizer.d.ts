import { Mat } from './Mat';

export interface FaceRecognizerpredictRet {
  label: number;
  confidence: number;
}

export class FaceRecognizer {
  load(file: string): void;
  predict(img: Mat): FaceRecognizerpredictRet;
  predictAsync(img: Mat): Promise<FaceRecognizerpredictRet>;
  save(file: string): void;
  train(trainImages: Mat[], labels: number[]): void;
  trainAsync(trainImages: Mat[], labels: number[]): Promise<void>;
}
