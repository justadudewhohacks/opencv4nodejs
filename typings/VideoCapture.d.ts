import { Mat } from './Mat.d';

export class VideoCapture {
  constructor(filePathOrdevicePort: string | number);
  get(property: number): number;
  read(): Mat;
  readAsync(): Promise<Mat>;
  release(): void;
  reset(): void;
  set(property: number, value: number): boolean;
  setAsync(property: number, value: number): Promise<boolean>;
  
  //static fourcc(char c1, char c2, char c3, char c4 ): number;		

}
