import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { OCRHMMClassifier } from './OCRHMMClassifier.d';

export interface OCRHMMDecoderRunWithInfoRet {
  outputText: string;
  rects: Rect[];
  words: string[];
  confidences: number[];
}

export class OCRHMMDecoder {
  constructor(classifier: OCRHMMClassifier, vocabulary: string, transitionPropabilitiesTable: Mat, emissionPropabilitiesTable: Mat, mode?: number);
  run(img: Mat, mask?: Mat, componentLevel?: number): string;
  runAsync(img: Mat, mask?: Mat, componentLevel?: number): Promise<string>;
  runWithInfo(img: Mat, mask?: Mat, componentLevel?: number): OCRHMMDecoderRunWithInfoRet;
  runWithInfoAsync(img: Mat, mask?: Mat, componentLevel?: number): Promise<OCRHMMDecoderRunWithInfoRet>;
}
