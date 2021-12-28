import { Mat } from './Mat.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class VideoCapture {
    constructor(filePath: string);
    constructor(devicePort: number);
    get(property: number): number;
    read(): cv.Mat;
    readAsync(): Promise<cv.Mat>;
    release(): void;
    reset(): void;
    set(property: number, value: number): boolean;
    setAsync(property: number, value: number): Promise<boolean>;
  }
}