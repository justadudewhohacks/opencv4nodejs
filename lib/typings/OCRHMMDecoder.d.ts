import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import { OCRHMMClassifier } from './OCRHMMClassifier.d';

export class OCRHMMDecoder {
  constructor(classifier: OCRHMMClassifier, vocabulary: string, transitionPropabilitiesTable: Mat, emissionPropabilitiesTable: Mat, mode?: number);
  run(img: Mat, mask?: Mat, componentLevel?: number): string;
  runAsync(img: Mat, mask?: Mat, componentLevel?: number): Promise<string>;
  runWithInfo(img: Mat, mask?: Mat, componentLevel?: number): { outputText: string, rects: Rect[], words: string[], confidences: number[] };
  runWithInfoAsync(img: Mat, mask?: Mat, componentLevel?: number): Promise<{ outputText: string, rects: Rect[], words: string[], confidences: number[] }>;
}
