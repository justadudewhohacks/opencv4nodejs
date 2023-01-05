import cv, { Mat } from '@u4/opencv4nodejs';
import { getResourcePath, wait4key } from '../utils';

const confidence = 0.60;

class MatchCoord {
  constructor(public x: number, public y: number, public value: number, public template: Mat) { }
  public toString(): string {
    return `${this.x}x${this.y} scode:${this.value}`;
  }

  public draw(mat: Mat) {
    const rect = new cv.Rect(this.x, this.y, this.template.cols, this.template.rows);
    // rect = rect.pad(1.8);
    const color = new cv.Vec3(83, 24, 78);
    mat.drawRectangle(rect, color, 2, cv.LINE_8);
  }
}

const locateDiceDot = async (display: boolean): Promise<void> => {
  // Load images
  const parisMapMat = await cv.imreadAsync(getResourcePath('templates/dice.jpg'));
  const metroMat = await cv.imreadAsync(getResourcePath('templates/dice-dot.jpg'));

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

  /** using faster raw data from getData */
  let getDataLoopTime = Date.now();

  const matchesRaw = cv.getScoreMax(matched, confidence);
  console.log(`matchesRaw is ${matchesRaw.length} length`)
  const matchesFiltered = cv.dropOverlappingZone(metroMat, matchesRaw);
  console.log(`matchesFiltered is ${matchesFiltered.length} length`)
  
  
  const matches1 = matchesFiltered.map(m => new MatchCoord(m[0], m[1], m[2], metroMat));

  getDataLoopTime = Date.now() - getDataLoopTime;
  matches1.sort((a, b) => b.value - a.value);
  console.log(`getData        processed in ${getDataLoopTime.toString().padStart(4, ' ')} ms to find ${matches1.length} region 1st: ${matches1[0]}`);
  console.log(``);

  for (const zone of matches1) {
    // Draw bounding rectangle
    zone.draw(parisMapMat);
  }
  if (display) {
    const windowName = 'metro';
    // Open result in new window
    cv.imshow(windowName, parisMapMat);
    cv.setWindowTitle(windowName, `The ${matches1.length} Metros stations are here:`);
    await wait4key();
  }
};

locateDiceDot(true);
