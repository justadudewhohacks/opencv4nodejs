import { EigenFaceRecognizer } from './EigenFaceRecognizer.d';
import { FisherFaceRecognizer } from './FisherFaceRecognizer.d';
import { LBPHFaceRecognizer } from './LBPHFaceRecognizer.d';

export type FaceRecognizer = LBPHFaceRecognizer | FisherFaceRecognizer | LBPHFaceRecognizer;