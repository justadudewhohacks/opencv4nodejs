import path from 'path';
import cv from '../lib';
export {default as cv} from '../lib';
import { Mat, Rect, Vec3 } from '../lib/typings/openCV';


export const dataPath = path.resolve(__dirname, '../data');
export const getDataFilePath = (fileName: string): string => path.resolve(dataPath, fileName);
export const grabFrames = (videoFile: number | string, delay: number, onFrame: (mat: Mat) => void): void => {
  const cap = new cv.VideoCapture(videoFile);
  let done = false;
  const intvl = setInterval(() => {
    let frame = cap.read();
    // loop back to start on end of stream reached
    if (frame.empty) {
      cap.reset();
      frame = cap.read();
    }
    onFrame(frame);

    const key = cv.waitKey(delay);
    done = key !== -1 && key !== 255;
    if (done) {
      clearInterval(intvl);
      console.log('Key pressed, exiting.');
    }
  }, 0);
};

export const runVideoDetection = (src: number, detect: (mat: Mat) => any): void => {
  grabFrames(src, 1, frame => {
    detect(frame);
  });
};

export const drawRectAroundBlobs = (binaryImg: Mat, dstImg: Mat, minPxSize: number, fixedRectWidth?: number) => {
  const {
    centroids,
    stats
  } = binaryImg.connectedComponentsWithStats();

  // pretend label 0 is background
  for (let label = 1; label < centroids.rows; label += 1) {
    const [x1, y1] = [stats.at(label, cv.CC_STAT_LEFT), stats.at(label, cv.CC_STAT_TOP)];
    const [x2, y2] = [
      x1 + (fixedRectWidth || stats.at(label, cv.CC_STAT_WIDTH)),
      y1 + (fixedRectWidth || stats.at(label, cv.CC_STAT_HEIGHT))
    ];
    const size = stats.at(label, cv.CC_STAT_AREA);
    const blue = new cv.Vec3(255, 0, 0);
    const thickness = 2;
    if (minPxSize < size) {
      dstImg.drawRectangle(
        new cv.Point2(x1, y1),
        new cv.Point2(x2, y2),
        blue, thickness
      );
    }
  }
};
// drawRectangle(rect: Rect, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
export const drawRect = (image: Mat, rect: Rect, color: Vec3, opts = { thickness: 2 }): void =>
  image.drawRectangle(
    rect,
    color,
    opts.thickness,
    cv.LINE_8
  );

export const drawBlueRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(255, 0, 0), opts);
export const drawGreenRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(0, 255, 0), opts);
export const drawRedRect = (image: Mat, rect: Rect, opts = { thickness: 2 }) =>
  drawRect(image, rect, new cv.Vec3(0, 0, 255), opts);
