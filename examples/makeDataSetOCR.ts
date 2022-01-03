import fs from 'fs';
import { cv } from './utils';
import type { Mat } from '..';
import path from 'path';

const labeledDataPath = path.join(__dirname, '..', 'data', 'ocr-nocommit', 'letters');
const outputDataPath = path.join(__dirname, '..', 'data', 'ocr-nocommit', 'letters_generated');

const lccs = Array(26).fill(97).map((v, i) => v + i).map(a => String.fromCharCode(a));

const blur = (img: Mat) => img.blur(new cv.Size(8, 8), new cv.Point2(1, 1));

const invert = (img: Mat) => img.threshold(254, 255, cv.THRESH_BINARY_INV);

const generate = (img: Mat, clazz, nr) => {
  for (let angle = 0; angle <= 60; angle += 10) {
    const rotAngle = -30 + angle;
    const rotMat = cv.getRotationMatrix2D(new cv.Point2(img.cols / 2, img.rows / 2), rotAngle);
    const rotated = invert(img).warpAffine(rotMat);
    for (let weight = 0; weight <= 3; weight += 1) {
      const threshWeight = 200 - (weight * 50);
      const result = blur(rotated)
        .threshold(threshWeight, 255, cv.THRESH_BINARY_INV);
      cv.imwrite(path.join(outputDataPath, clazz, `${clazz}_${nr}_w${weight}_r${angle}.png`), result.resize(40, 40));
    }
  }
};
/*
lccs.forEach((clazz) => {
  for (let nr = 0; nr < 10; nr += 1) {
    const img = cv.imread(path.join(labeledDataPath, clazz, `${clazz}${nr}.png`));
    generate(img, clazz, nr);
  }
});
*/
const makeGrid = (clazz) => {
  const dir = path.join(outputDataPath, clazz);
  const gridMat = new cv.Mat(10 * 40, 28 * 40, cv.CV_8UC3);
  const files = fs.readdirSync(dir);
  files.forEach((file, i) => {
    const x = (i % 28) * 40;
    const y = Math.floor(i / 28) * 40;
    cv.imread(path.join(dir, file)).copyTo(gridMat.getRegion(new cv.Rect(x, y, 40, 40)));
  });
  cv.imwrite(path.join(outputDataPath, `${clazz}_grid.png`), gridMat);
};
