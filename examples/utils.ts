import path from 'path';
import fs from 'fs';
import cv from '..';
export { default as cv } from '..';
import { Mat, Rect, Vec3 } from '..';
import Axios from 'axios';
import ProgressBar from 'progress';

export function getCachedFile(localName: string, url: string, notice?: string): Promise<string> {
  const localFile = path.resolve(__dirname, localName);
  if (fs.existsSync(localFile)) {
    return Promise.resolve(localFile);
  }
  if (notice)
    console.log(notice);
  console.log(`can not find ${localName} try downloading file from ${url}`);
  const parent = path.dirname(localFile);
  try {
    fs.mkdirSync(parent, { recursive: true });
  } catch (e) {
    // ignore error
  }
  return new Promise<string>(async (done) => {
    console.log('Connecting server…')
    const { data, headers } = await Axios({
      url,
      method: 'GET',
      responseType: 'stream'
    })
    const totalLength = headers['content-length']

    console.log('Starting download')
    const progressBar = new ProgressBar('-> downloading [:bar] :percent :etas', {
      width: 40,
      complete: '=',
      incomplete: ' ',
      renderThrottle: 1,
      total: parseInt(totalLength)
    })
    const writer = fs.createWriteStream(localFile)
    data.on('data', (chunk) => progressBar.tick(chunk.length))
    data.pipe(writer)
    data.on('complete', () => done(localFile))
  })
}


/**
 * add some helpter for examples TS
 */

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
