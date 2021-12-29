import { Mat } from './Mat.d';

export interface ddnLayerParams {
  blobs: Mat[];
  name: string;
  type: string;
}

export class Net {
  addLayer(name: string, type: string, params: ddnLayerParams): number
  addLayerToPrev(name: string, type: string, params: ddnLayerParams): number
  connect(outPin: string, inpPin: string): void;
  connect(outLayerId: number, outNum: number, inpLayerId: number, inpNum: number);
  dump(): string;
  dumpToFile(path: string): void;
  empty(): void;
  enableFusion(fusion: boolean): void

  //Runs forward pass to compute output of layer with name outputName. More...
  // forward (OutputArrayOfArrays outputBlobs, const String &outputName=String()): void
  // Runs forward pass to compute outputs of layers listed in outBlobNames. More...
  //forward (OutputArrayOfArrays outputBlobs, const std::vector< String > &outBlobNames): void        
  // Runs forward pass to compute outputs of layers listed in outBlobNames. More...
  //forward (std::vector< std::vector< Mat > > &outputBlobs, const std::vector< String > &outBlobNames): void

  getLayerNames(): string[];
  getUnconnectedOutLayers(): number[];
  setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number);
  setInput(blob: Mat, inputName?: string): void;

  // forward(outputName?: string): Mat;
  // forward(outputName: string[]): Mat[];

  forward(inputName?: string): Mat;
  forward(outBlobNames?: string[]): Mat[];
  forwardAsync(inputName?: string): Promise<Mat>;
  forwardAsync(outBlobNames?: string[]): Promise<Mat[]>;
  setInputAsync(blob: Mat, inputName?: string): Promise<void>;
  getLayerNamesAsync(): Promise<string[]>;
  getUnconnectedOutLayersAsync(): Promise<number[]>;

}
