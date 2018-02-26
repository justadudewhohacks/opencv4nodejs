import * as path from 'path';
import * as cv from '../../';

export const dataPath = path.resolve(__dirname, '../../data');
export const getDataFilePath = (fileName: string) => path.resolve(dataPath, fileName);

export function grabFrames (videoFile: any, delay: number, onFrame: (frame: cv.Mat) => void): void {
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

export function drawRectAroundBlobs (binaryImg: cv.Mat, dstImg: cv.Mat, minPxSize: number, fixedRectWidth?: number): void {
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
    if (minPxSize < size) {
      dstImg.drawRectangle(
        new cv.Point2(x1, y1),
        new cv.Point2(x2, y2),
        blue,
        2
      );
    }
  }
};

export function drawRect (image: cv.Mat, rect: cv.Rect, color: cv.Vec3, thickness: number = 2): void {
  return image.drawRectangle(
    rect,
    color,
    thickness,
    cv.LINE_8
  );
}

export function drawBlueRect (image: cv.Mat, rect: cv.Rect, thickness?: number) {
  return drawRect(image, rect, new cv.Vec3(255, 0, 0), thickness);
}
export function drawGreenRect (image: cv.Mat, rect: cv.Rect, thickness?: number) {
  return drawRect(image, rect, new cv.Vec3(0, 255, 0), thickness);
}
export function drawRedRect (image: cv.Mat, rect: cv.Rect, thickness?: number) {
  return drawRect(image, rect, new cv.Vec3(0, 0, 255), thickness);
}