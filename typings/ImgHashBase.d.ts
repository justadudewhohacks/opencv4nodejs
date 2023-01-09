import { Mat } from "./Mat.d";

export class ImgHashBase {
  compute(inputArr: Mat): number[];
  computeAsync(inputArr: Mat): Promise<number[]>;
  compare(hashOne: number[], hashTwo: number[]): number;
  compareAsync(hashOne: number[], hashTwo: number[]): Promise<number>;
}
