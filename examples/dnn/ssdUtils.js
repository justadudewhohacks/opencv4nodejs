const {
  cv
} = require('../utils');


exports.extractResults = function (outputBlob, imgDimensions) {
  return Array(outputBlob.rows).fill(0)
    .map((res, i) => {
      const classLabel = outputBlob.at(i, 1);
      const confidence = outputBlob.at(i, 2);
      const topLeft = new cv.Point(
        outputBlob.at(i, 3) * imgDimensions.cols,
        outputBlob.at(i, 6) * imgDimensions.rows
      );
      const bottomRight = new cv.Point(
        outputBlob.at(i, 5) * imgDimensions.cols,
        outputBlob.at(i, 4) * imgDimensions.rows
      );
      const rect = new cv.Rect(
        topLeft.x,
        topLeft.y,
        bottomRight.x - topLeft.x,
        bottomRight.y - topLeft.y
      );

      return ({
        classLabel,
        confidence,
        rect
      });
    });
};
