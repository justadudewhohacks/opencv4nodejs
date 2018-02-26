import { Mat } from './Mat.d';

export class VideoCapture {
  constructor(filePath: string);
  constructor(devicePort: number);
  get(property: number): void;
  read(): Mat;
  readAsync(): Promise<Mat>;
  release(): void;
  reset(): void;
  set(property: number, value: number): void;
}
