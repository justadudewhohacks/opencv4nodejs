import { Mat } from './Mat.d';

export class OCRHMMClassifier {
  constructor(classifier: OCRHMMClassifier, vocabulary: string, transitionPropabilitiesTable: Mat, emissionPropabilitiesTable: Mat, mode?: number);
  eval(img: Mat): { classes: number[], confidences: number[] };
  evalAsync(img: Mat): Promise<{ classes: number[], confidences: number[] }>;
}
