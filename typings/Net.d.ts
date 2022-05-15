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
  connect(outLayerId: number, outNum: number, inpLayerId: number, inpNum: number): void;
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
  /**
   * Returns indexes of layers with unconnected outputs.
   * 
   * FIXIT: Rework API to registerOutput() approach, deprecate this call
   */
  getUnconnectedOutLayers(): number[];
  /**
   * Sets the new input value for the network.
   * 
   * https://docs.opencv.org/4.x/db/d30/classcv_1_1dnn_1_1Net.html#a5e74adacffd6aa53d56046581de7fcbd
   * 
   * @param blob 	A new blob. Should have CV_32F or CV_8U depth.
   * @param name 	A name of input layer.
   * @param scalefactor An optional normalization scale.
   * @param mean 	An optional mean subtraction values.
   */
  setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number): void;
  setInput(blob: Mat, inputName?: string): void;

  // forward(outputName?: string): Mat;
  // forward(outputName: string[]): Mat[];
  /**
   * Runs forward pass to compute output of layer with name outputName.
   * 
   * https://docs.opencv.org/3.4/db/d30/classcv_1_1dnn_1_1Net.html#a98ed94cb6ef7063d3697259566da310b
   * 
   * @param inputName name for layer which output is needed to get
   */
  forward(inputName?: string): Mat;
  /**
   * 
   * @param outBlobNames names for layers which outputs are needed to get
   */
  forward(outBlobNames?: string[]): Mat[];
  forwardAsync(inputName?: string): Promise<Mat>;
  forwardAsync(outBlobNames?: string[]): Promise<Mat[]>;
  setInputAsync(blob: Mat, inputName?: string): Promise<void>;
  getLayerNamesAsync(): Promise<string[]>;
  getUnconnectedOutLayersAsync(): Promise<number[]>;

  /**
   * Ask network to use specific computation backend where it supported.
   * 
   * @param backendId backend identifier.
   */
  setPreferableBackend(backendId: number): void;

  /**
   * Ask network to make computations on specific target device.
   * @param targetId target identifier.
   */
  setPreferableTarget(targetId: number): void;

  /**
   * Returns overall time for inference and timings (in ticks) for layers.
   * 
   * Indexes in returned vector correspond to layers ids. Some layers can be fused with others, in this case zero ticks count will be return for that skipped layers. Supported by DNN_BACKEND_OPENCV on DNN_TARGET_CPU only.
   * 
   * https://docs.opencv.org/4.x/db/d30/classcv_1_1dnn_1_1Net.html#a06ce946f675f75d1c020c5ddbc78aedc
   *  
   * [out]	timings	vector for tick timings for all layers.
   * Returns
   * overall ticks for model inference.
   * WARN retval is a int64, which can overflow nodejs number
   */
  getPerfProfile(): {	retval: number, timings: number[] };

}
