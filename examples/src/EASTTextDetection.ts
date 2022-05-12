import path from 'path';
import { cv, drawBlueRect, getCachedFile, getResourcePath, wait4key } from './utils';
import { Mat, Rect } from '@u4/opencv4nodejs';

/**
 * Text detection simple code example.
 * Get box containing text from image.
 * 
 * use EAST: An Efficient and Accurate Scene Text Detector
 * https://github.com/argman/EAST
 */

const MIN_CONFIDENCE = 0.5;
const NMS_THRESHOLD = 0.4;
const SIZE = 320;

function decode(scores: Mat, geometry: Mat, confThreshold = MIN_CONFIDENCE) {
  const [numRows, numCols] = scores.sizes.slice(2);
  const boxes = [];
  const confidences = [];

  for (let y = 0; y < numRows; y += 1) {
    for (let x = 0; x < numCols; x += 1) {
      const score = scores.at([0, 0, y, x]);

      if (score < confThreshold) {
        continue;
      }

      const offsetX = x * 4;
      const offsetY = y * 4;
      const angle = geometry.at([0, 4, y, x]);
      const cos = Math.cos(angle);
      const sin = Math.sin(angle);

      const h = geometry.at([0, 0, y, x]) + geometry.at([0, 2, y, x]);
      const w = geometry.at([0, 1, y, x]) + geometry.at([0, 3, y, x]);

      const endX = offsetX + (cos * geometry.at([0, 1, y, x])) + (sin * geometry.at([0, 2, y, x]));
      const endY = offsetY - (sin * geometry.at([0, 1, y, x])) + (cos * geometry.at([0, 2, y, x]));
      const startX = endX - w;
      const startY = endY - h;

      boxes.push(new cv.Rect(
        startX,
        startY,
        endX - startX,
        endY - startY
      ));
      confidences.push(score);
    }
  }
  return [boxes, confidences];
}

async function detection(modelPath: string, imgAbsPath: string): Promise<void> {
  const net = cv.readNetFromTensorflow(modelPath);
  const img = cv.imread(imgAbsPath);
  const [imgHeight, imgWidth] = img.sizes;
  const widthRatio = imgWidth / SIZE;
  const heightRatio = imgHeight / SIZE;

  const inputBlob = cv.blobFromImage(img, {
    scaleFactor: 1,
    size: new cv.Size(SIZE, SIZE),
    mean: new cv.Vec3(123.68, 116.78, 103.94),
    swapRB: true,
    crop: false
  });

  net.setInput(inputBlob);

  const outBlobNames = [
    'feature_fusion/Conv_7/Sigmoid',
    'feature_fusion/concat_3'
  ];

  const [scores, geometry] = net.forward(outBlobNames);
  const [boxes, confidences] = decode(scores, geometry, MIN_CONFIDENCE) as [Rect[], number[]];

  const indices = cv.NMSBoxes(
    boxes,
    confidences,
    MIN_CONFIDENCE, NMS_THRESHOLD
  );

  indices.forEach((i) => {
    const rect = boxes[i];
    const imgRect = new cv.Rect(
      rect.x * widthRatio,
      rect.y * heightRatio,
      rect.width * widthRatio,
      rect.height * heightRatio
    )
    drawBlueRect(img, imgRect);
  });
  cv.imshow('EAST text detection', img);
  await wait4key();
}

async function main() {
  if (!cv.xmodules || !cv.xmodules.dnn) {
    console.error('exiting: opencv4nodejs compiled without dnn module');
    return;
  }
  
  const notice = 'EAST .pb model is missing, you can create your from https://github.com/argman/EAST';
  const modelPath = await getCachedFile(getResourcePath('text-models/frozen_east_text_detection.pb'), 'https://github.com/oyyd/frozen_east_text_detection.pb/blob/71415464412c55bb1d135fcdeda498e29a67effa/frozen_east_text_detection.pb?raw=true', {notice})
  const imgPath = path.resolve(getResourcePath('text-data/detection.png'));
  await detection(modelPath, imgPath);
}
main();

