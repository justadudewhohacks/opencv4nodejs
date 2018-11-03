import { Mat } from './Mat.d';

export class Net {
  forward(inputName?: string): Mat;
  forward(outBlobNames?: string[]): Mat[];
  forwardAsync(inputName?: string): Promise<Mat>;
  forwardAsync(outBlobNames?: string[]): Promise<Mat[]>;
  setInput(blob: Mat, inputName?: string): void;
  setInputAsync(blob: Mat, inputName?: string): Promise<void>;
}
