import { Mat } from "./Mat.d";
import { Rect } from "./Rect.d";
import { Point2 } from "./Point2.d";

export class Facemark {
  addTrainingSample(image: Mat, landmarks: number[][]): boolean;
  addTrainingSampleAsync(image: Mat, landmarks: number[][]): Promise<boolean>;
  loadModel(model: string): void;
  loadModelAsync(model: string): Promise<void>;
  getFaces(image: Mat): Rect[];
  getFacesAsync(image: Mat): Promise<Rect[]>;
  setFaceDetector(callback: Function): boolean;
  training(): void;
  trainingAsync(): Promise<void>;
  fit(image: Mat, faces: Rect[]): Point2[][];
  fitAsync(image: Mat, faces: Rect[]): Promise<Point2[][]>;
  save(file: string): void;
  load(file: string): void;
}
