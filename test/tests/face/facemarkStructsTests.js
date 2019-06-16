module.exports = ({ cv, utils }) => {

  const { assertPropsWithValue } = utils;

  describe('Facemark structures', () => {
    it('FacemarkAAMData', () => {
      const data = {
        s0: [new cv.Point2(0, 0), new cv.Point2(0, 0)]
      };

      const facemarkData = new cv.FacemarkAAMData();
      Object.keys(data).forEach((item) => {
        facemarkData[item] = data[item];
      });

      assertPropsWithValue(facemarkData)(data);
    });

    it('FacemarkAAMParams', () => {
      const params = {
        m: 10,
        n: 10,
        maxM: 30,
        maxN: 30,
        modelFilename: 'filename.xml',
        nIter: 4,
        saveModel: true,
        scales: [3.0, 2.0],
        textureMaxM: 12,
        verbose: true
      };

      const facemarkParams = new cv.FacemarkAAMParams();
      Object.keys(params).forEach((param) => {
        facemarkParams[param] = params[param];
      });

      assertPropsWithValue(facemarkParams)(params);
    });

    it('FacemarkLBFParams', () => {
      const params = {
        baggingOverlap: 2.5,
        cascadeFile: 'cascadeFile.xml',
        detectROI: new cv.Rect(0, 0, 10, 10),
        featsM: [5, 4, 3, 2, 1],
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
        verbose: true
      };

      const facemarkParams = new cv.FacemarkLBFParams();
      Object.keys(params).forEach((param) => {
        facemarkParams[param] = params[param];
      });

      assertPropsWithValue(facemarkParams)(params);
    });
  });
};
