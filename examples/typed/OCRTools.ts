import * as fs from 'fs';
import * as cv from '../../';

// a - z
export const lccs = Array(26).fill(97).map((v, i) => v + i).map(ascii => String.fromCharCode(ascii));

const invert = (img: cv.Mat) => img.threshold(254, 255, cv.THRESH_BINARY_INV);

const getBoundingRect = (component: number[]) => new cv.Rect(
  component[cv.CC_STAT_LEFT],
  component[cv.CC_STAT_TOP],
  component[cv.CC_STAT_WIDTH],
  component[cv.CC_STAT_HEIGHT]
);

const getLetterBoundingRect = (img: cv.Mat, isIorJ: boolean) => {
  const { stats } = invert(img).bgrToGray().connectedComponentsWithStats();
  const componentsOrderedBySize =
    stats.getDataAsArray().sort((s0, s1) => s1[cv.CC_STAT_AREA] - s0[cv.CC_STAT_AREA]);

  if (componentsOrderedBySize.length < 2) {
    return null;
  }

  // background actually is largest component so we take the next largest
  let largestComponent = componentsOrderedBySize[1];
  let letterRect = getBoundingRect(largestComponent);

  if (isIorJ && componentsOrderedBySize.length > 2) {
    let dotComponent = componentsOrderedBySize[2];

    if (largestComponent[cv.CC_STAT_TOP] < dotComponent[cv.CC_STAT_TOP]) {
      largestComponent = componentsOrderedBySize[2];
      dotComponent = componentsOrderedBySize[1];
      letterRect = getBoundingRect(largestComponent);
    }

    const dotRectXRight = dotComponent[cv.CC_STAT_LEFT] + dotComponent[cv.CC_STAT_WIDTH];
    const xLeft = Math.min(letterRect.x, dotComponent[cv.CC_STAT_LEFT]);
    const letterRectYBottom = letterRect.y + letterRect.height;

    letterRect = new cv.Rect(
      xLeft,
      dotComponent[cv.CC_STAT_TOP],
      Math.max(letterRect.width, dotRectXRight - xLeft),
      (letterRectYBottom - dotComponent[cv.CC_STAT_TOP])
    );
  }

  return letterRect;
};

export function centerLetterInImage (img: cv.Mat, isIorJ: boolean): cv.Mat {
  const rect = getLetterBoundingRect(img, isIorJ);
  if (!rect) {
    return null;
  }

  const offX = (img.cols - rect.width) / 2;
  const offY = (img.rows - rect.height) / 2;
  const centeredRect = new cv.Rect(
    offX,
    offY,
    rect.width,
    rect.height
  );

  const centered = new cv.Mat(img.rows, img.cols, img.type, [255, 255, 255]);
  img.getRegion(rect).copyTo(centered.getRegion(centeredRect));

  return centered;
};

export function saveConfusionMatrix (
  testDataFiles: any[],
  predict: (mat: cv.Mat, isIorJ: boolean) => number,
  numTestImagesPerClass: number,
  outputFile: string
): void {
  const confusionMat = new cv.Mat(26, 26, cv.CV_64F, 0);
  testDataFiles.forEach((files, label) => {
    files.forEach((file: string) => {
      const img = cv.imread(file);
      const predictedLabel = predict(img, label === 8 || label === 9);
      confusionMat.set(label, predictedLabel, confusionMat.at(label, predictedLabel) + 1);
    });
  });

  const confusionMatMatrix = [[''].concat(lccs)].concat(
    confusionMat.div(numTestImagesPerClass)
      .getDataAsArray().map((col, l) => [lccs[l]].concat(`${col.map(v => Math.round(v * 100) / 100)}`))
  );

  const csvRows = confusionMatMatrix.map(cols => cols.join(';'));
  fs.writeFileSync(outputFile, csvRows.join('\n'));
};
