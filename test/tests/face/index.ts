import facemarkStructsTests from './facemarkStructsTests';
import recognizerTestsFactory from './recognizerTests';
import facemarkTestsFactory from './facemarkTests';
import { TestContext } from '../model';

export default function (ctxt: TestContext) {
  const { cv, cvVersionGreaterEqual } = ctxt;

  const recognizerTests = recognizerTestsFactory(ctxt);
  const facemarkTests = facemarkTestsFactory(ctxt);

  describe('FaceRecognizers', () => {
    describe('EigenFaceRecognizer', () => {
      const args2 = ['num_components', 'threshold'];
      const values = [10, 0.8];
      recognizerTests(args2, values, cv.EigenFaceRecognizer);
    });

    describe('FisherFaceRecognizer', () => {
      const args2 = ['num_components', 'threshold'];
      const values = [10, 0.8];
      recognizerTests(args2, values, cv.FisherFaceRecognizer);
    });

    describe('LBPHFaceRecognizer', () => {
      const args2 = ['radius', 'neighbors', 'grid_x', 'grid_y'];
      const values = [2, 16, 16, 16];
      recognizerTests(args2, values, cv.LBPHFaceRecognizer);
    });
  });

  if (cvVersionGreaterEqual(3, 4, 0)) {
    describe('FaceMark', () => {
      facemarkStructsTests(ctxt);

      describe('FacemarkLBF', () => {
        facemarkTests(cv.FacemarkLBF, cv.FacemarkLBFParams);
      });

      describe('FacemarkAAM', () => {
        facemarkTests(cv.FacemarkAAM, cv.FacemarkAAMParams);
      });
    });
  }
}
