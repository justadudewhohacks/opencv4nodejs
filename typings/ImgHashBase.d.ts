import { Mat } from "./Mat.d";

export class ImgHashBase {
  compute(inputArr: Mat): string[];
  computeAsync(inputArr: Mat): Promise<string[]>;
  compare(hashOne: string[], hashTwo: string[]): number;
  compareAsync(hashOne: string[], hashTwo: string[]): Promise<number>;
}
