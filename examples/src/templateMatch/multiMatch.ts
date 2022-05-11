import cv, { Mat, Rect } from '@u4/opencv4nodejs';
import { getResourcePath } from '../utils';

const confidence = 0.97;

class MatchCoord {
  constructor(public x: number, public y: number, public value: number, public template: Mat) { }
  public toString(): string {
    return `${this.x}x${this.y} scode:${this.value}`;
  }

  public draw(mat: Mat) {
    let rect = new cv.Rect(this.x, this.y, this.template.cols, this.template.rows);
    rect = rect.pad(1.8);
    const color = new cv.Vec3(83, 24, 78);
    mat.drawRectangle(rect, color, 2, cv.LINE_8);
  }
}

/**
 * Find values greater than threshold in a 32bit float matrix and return a list of matchs formated as [[x1, y1, score1]. [x2, y2, score2], [x3, y3, score3]]
 * 
 * @param scoreMat Matric containing scores as 32Bit float (CV_32F)
 * @param threshold Minimal score to collect
 * @param region search region
 * @returns a list of matchs
 */
export const getScoreMax = (scoreMat: Mat, threshold: number, region?: Rect): Array<[number, number, number]> => {
  if (scoreMat.type !== cv.CV_32F)
    throw Error('this method can only be call on a CV_32F Mat');
  if (scoreMat.dims !== 2)
    throw Error('this method can only be call on a 2 dimmention Mat');

  const out: Array<[number, number, number]> = [];
  const { cols, rows } = scoreMat;
  const raw = scoreMat.getData();

  let x1, x2, y1, y2: number;
  if (region) {
    x1 = region.x;
    y1 = region.y;
    x2 = x1 + region.width;
    y2 = y1 + region.height;
  } else {
    x1 = y1 = 0;
    x2 = cols;
    y2 = rows;
  }
  for (let y = y1; y < y2; y++) {
    let offset = (x1 + y * cols) * 4;
    for (let x = x1; x < x2; x++) {
      const value = raw.readFloatLE(offset);
      if (value > threshold) {
        out.push([x, y, value]);
      }
      offset += 4;
    }
  }
  return out;
}

const locateMetroStation = async (display: boolean): Promise<void> => {
  // Load images
  const parisMapMat = await cv.imreadAsync(getResourcePath('templates/paris.jpg'));
  const metroMat = await cv.imreadAsync(getResourcePath('templates/metro.png'));

  // Match template (the brightest locations indicate the highest match)
  let matchTemplateAsyncTime = Date.now();
  const matched = await parisMapMat.matchTemplateAsync(metroMat, cv.TM_CCOEFF_NORMED);
  matchTemplateAsyncTime = Date.now() - matchTemplateAsyncTime;

  console.log(`matched Mat size is ${matched.cols}x${matched.rows} type is ${cv.toMatTypeName(matched.type)} channels: ${matched.channels} computed in ${matchTemplateAsyncTime}ms`);
  console.log(`-`);

  let minMaxLocTime = Date.now();
  // Use minMaxLoc to locate the highest value (or lower, depending of the type of matching method)
  const minMax = matched.minMaxLoc();
  minMaxLocTime = Date.now() - minMaxLocTime;
  const match = new MatchCoord(minMax.maxLoc.x, minMax.maxLoc.y, minMax.maxVal, metroMat);

  console.log(`minMaxLocTime  processed in ${minMaxLocTime.toString().padStart(4, ' ')} ms to find  1 region 1st: ${match}`)

  /** using slow getDataAsArray */
  let getDataAsArrayLoopTime = Date.now();
  const lines = matched.getDataAsArray();
  const matches0 = [] as Array<MatchCoord>;
  for (let y = 0; y < lines.length; y++) {
    const line = lines[y];
    for (let x = 0; x < line.length; x++) {
      const value = line[x];
      if (value > confidence) {
        matches0.push(new MatchCoord(x, y, value, metroMat));
      }
    }
  }
  getDataAsArrayLoopTime = Date.now() - getDataAsArrayLoopTime;
  matches0.sort((a, b) => b.value - a.value);
  console.log(`getDataAsArray processed in ${getDataAsArrayLoopTime.toString().padStart(4, ' ')} ms to find ${matches0.length} region 1st: ${matches0[0]}`);

  /** using faster raw data from getData */
  let getDataLoopTime = Date.now();

  const { cols, rows } = matched;
  const matches1 = getScoreMax(matched, confidence, new Rect(0, 0, cols - metroMat.cols + 1, rows - metroMat.rows + 1)).map(m => new MatchCoord(m[0], m[1], m[2], metroMat))
  getDataLoopTime = Date.now() - getDataLoopTime;
  matches1.sort((a, b) => b.value - a.value);
  console.log(`getData        processed in ${getDataLoopTime.toString().padStart(4, ' ')} ms to find ${matches1.length} region 1st: ${matches1[0]}`);
  console.log(``);
  console.log(`getData is ${(getDataAsArrayLoopTime / getDataLoopTime).toFixed(1)} times faster than getDataAsArray`);

  for (const zone of matches1) {
    // Draw bounding rectangle
    zone.draw(parisMapMat);
  }
  if (display) {
    const windowName = 'metro';
    // Open result in new window
    cv.imshow(windowName, parisMapMat);
    cv.setWindowTitle(windowName, `The ${matches1.length} Metros stations are here:`);
    cv.waitKey();
  }
};

locateMetroStation(false);
