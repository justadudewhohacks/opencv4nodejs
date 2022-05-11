import cv, { Mat, Rect } from '@u4/opencv4nodejs';
import { getResourcePath, wait4key } from '../utils';

const confidence = 0.90;

/**
 * drop overlaping zones
 * @param template template Matrix used to get dimentions.
 * @param matches list of matches as a list in [x,y,score]. (this data will be altered)
 * @returns best match without colisions
 */
function dropCollision(template: Mat, matches: Array<[number, number, number]>): Array<[number, number, number]> {
  ////////////
  // supression des colisions
  const total = matches.length;
  const width = template.cols / 2;
  const height = template.rows / 2;
  for (let i = 0; i < total; i++) {
    const cur = matches[i];
    if (!cur[2]) continue;
    for (let j = i + 1; j < total; j++) {
      const sec = matches[j];
      if (!sec[2]) continue;
      if (Math.abs(cur[1] - sec[1]) > height) continue;
      if (Math.abs(cur[0] - sec[0]) > width) continue;
      if (cur[2] > sec[2]) {
        sec[2] = 0;
      } else {
        cur[2] = 0;
        break;
      }
    }
    // if (cur[2])
    //  matchesClean.push(cur);
    // fin supression collisions
  }
  return matches.filter(m => !m[2]);
}


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

  const { cols, rows } = matched;
  const matchesRaw = cv.getScoreMax(matched, confidence, new Rect(0, 0, cols - metroMat.cols + 1, rows - metroMat.rows + 1));
  console.log(`matchesRaw is ${matchesRaw.length} length`)
  const matchesFiltered = dropCollision(metroMat, matchesRaw);
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
