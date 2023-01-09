import {
  FacemarkAAMData,
  FacemarkAAMParams,
  FacemarkLBFParams,
  Point2,
} from '../../../typings';
import { assertPropsWithValue } from '../../utils/testUtils';
import { TestContext } from '../model';

type Mutable<T> = {
  -readonly [k in keyof T]: T[k];
};

export default (args: TestContext) => {
  const { cv } = args;

  describe('Facemark structures', () => {
    it('FacemarkAAMData', () => {
      const data: Mutable<FacemarkAAMData> = {
        s0: [new cv.Point2(0, 0), new cv.Point2(0, 0)] as Point2[],
      } as const;

      const facemarkData = new cv.FacemarkAAMData();
      Object.keys(data).forEach((item: 's0') => {
        (facemarkData as any)[item] = data[item];
      });

      assertPropsWithValue(facemarkData, data);
    });

    it('FacemarkAAMParams', () => {
      const params: FacemarkAAMParams = {
        m: 10,
        n: 10,
        maxM: 30,
        maxN: 30,
        modelFilename: 'filename.xml',
        nIter: 4,
        saveModel: true,
        scales: [3.0, 2.0] as number[],
        textureMaxM: 12,
        verbose: true,
      } as const;

      const facemarkParams: Mutable<FacemarkAAMParams> = new cv.FacemarkAAMParams();
      Object.keys(params).forEach((param: keyof FacemarkAAMParams) => {
        (facemarkParams as any)[param] = params[param];
      });

      assertPropsWithValue(facemarkParams, params);
    });

    it('FacemarkLBFParams', () => {
      const params: Mutable<FacemarkLBFParams> = {
        baggingOverlap: 2.5,
        cascadeFile: 'cascadeFile.xml',
        detectROI: new cv.Rect(0, 0, 10, 10),
        featsM: [5, 4, 3, 2, 1] as number[],
        initShapeN: 32,
        modelFilename: 'modelFilename.xml',
        nLandmarks: 68,
        pupils: [[1, 2, 3, 4], [4, 3, 2, 1]],
        radiusM: [2.5, 5.5],
        saveModel: true,
        seed: 1000,
        shapeOffset: 5.4,
        stagesN: 4,
        treeDepth: 3,
        treeN: 2,
        verbose: true,
      };

      const facemarkParams: Mutable<FacemarkLBFParams> = new cv.FacemarkLBFParams();
      Object.keys(params).forEach((param: keyof FacemarkLBFParams) => {
        (facemarkParams as any)[param] = params[param];
      });

      assertPropsWithValue(facemarkParams, params);
    });
  });
};
