import facemarkStructsTests from './facemarkStructsTests';
import recognizerTestsFactory from './recognizerTests';
import facemarkTestsFactory from './facemarkTests';
import { TestContext } from '../model';

export default function (args: TestContext) {
  const { cv, utils, getTestImg } = args;

  const {
    cvVersionGreaterEqual,
  } = utils;

  const recognizerTests = recognizerTestsFactory({ cv, utils, getTestImg });
  const facemarkTests = facemarkTestsFactory({ cv, utils, getTestImg });

  describe('FaceRecognizers', () => {
    describe('EigenFaceRecognizer', () => {
      const args = ['num_components', 'threshold'];
      const values = [10, 0.8];
      recognizerTests(args, values, cv.EigenFaceRecognizer);
    });

    describe('FisherFaceRecognizer', () => {
      const args = ['num_components', 'threshold'];
      const values = [10, 0.8];
      recognizerTests(args, values, cv.FisherFaceRecognizer);
    });

    describe('LBPHFaceRecognizer', () => {
      const args = ['radius', 'neighbors', 'grid_x', 'grid_y'];
      const values = [2, 16, 16, 16];
      recognizerTests(args, values, cv.LBPHFaceRecognizer);
    });
  });

  if (cvVersionGreaterEqual(3, 4, 0)) {
    describe('FaceMark', () => {
      facemarkStructsTests(args);

      describe('FacemarkLBF', () => {
        facemarkTests(cv.FacemarkLBF, cv.FacemarkLBFParams);
      });

      describe('FacemarkAAM', () => {
        facemarkTests(cv.FacemarkAAM, cv.FacemarkAAMParams);
      });
    });
  }
}
