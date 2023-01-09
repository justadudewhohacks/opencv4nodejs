import { Mat } from './Mat.d';

export interface OCRHMMClassifierEvalRet {
  classes: number[];
  confidences: number[];
}

export class OCRHMMClassifier {
  constructor(classifier: OCRHMMClassifier, vocabulary: string, transitionPropabilitiesTable: Mat, emissionPropabilitiesTable: Mat, mode?: number);
  eval(img: Mat): OCRHMMClassifierEvalRet;
  evalAsync(img: Mat): Promise<OCRHMMClassifierEvalRet>;
}
