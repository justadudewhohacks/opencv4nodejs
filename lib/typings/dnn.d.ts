import { Point2 } from './Point2.d';
export * as cv from './cv';

declare module "./cv.js" {
    export interface ddnLayerParams {
        blobs: Mat[];
        name: string;
        type: string;
    }

    export function readNetFromTensorflow(model: string, config: string): DdnNet;

    export function readNetFromDarknet(cfgFile: string, darknetModel: string): DdnNet;

    // see https://docs.opencv.org/3.4/db/d30/classcv_1_1dnn_1_1Net.html
    export class DdnNet {
        addLayer(name: name, type: String, params: ddnLayerParams): number
        addLayerToPrev(name: string, type: string, params: ddnLayerParams): number
        connect(outPin: string, inpPin: string): void;
        connect(outLayerId: number, outNum: number, inpLayerId: number, inpNum: number);
        dump(): string;
        dumpToFile(path: string): void;
        empty(): void;
        enableFusion(fusion: boolean): void
        forward(outputName?: string): Mat;
        forward(outputName: string[]): Mat[];
        //Runs forward pass to compute output of layer with name outputName. More...
        // forward (OutputArrayOfArrays outputBlobs, const String &outputName=String()): void
        // Runs forward pass to compute outputs of layers listed in outBlobNames. More...
        //forward (OutputArrayOfArrays outputBlobs, const std::vector< String > &outBlobNames): void        
        // Runs forward pass to compute outputs of layers listed in outBlobNames. More...
        //forward (std::vector< std::vector< Mat > > &outputBlobs, const std::vector< String > &outBlobNames): void

        getLayerNames(): string[];
        getUnconnectedOutLayers(): number[];
        setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number);
    }
}