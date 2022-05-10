import cv, { Mat } from '@u4/opencv4nodejs';
import { getResource } from '../utils';

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

const locateMetroStation = async () => {
  // Load images
  const parisMapMat = await cv.imreadAsync(getResource('templates/paris.jpg'));
  const metroMat = await cv.imreadAsync(getResource('templates/metro.png'));

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


  /** using slow getDataAsArray */
  let getDataLoopTime = Date.now();
  const { cols, rows } = matched;
  const raw = matched.getData();
  const matches1 = [] as Array<MatchCoord>;
  let offset = 0;
  for (let y = 0; y < rows; y++) {
    for (let x = 0; x < cols; x++) {
      const value = raw.readFloatLE(offset);
      if (value > confidence) {
        matches1.push(new MatchCoord(x, y, value, metroMat));
      }
      offset += 4;
    }
  }
  getDataLoopTime = Date.now() - getDataLoopTime;
  matches1.sort((a, b) => b.value - a.value);
  console.log(`getData        processed in ${getDataLoopTime.toString().padStart(4, ' ')} ms to find ${matches1.length} region 1st: ${matches1[0]}`);


  console.log(``);
  console.log(`getData is ${(getDataAsArrayLoopTime / getDataLoopTime).toFixed(1)} times faster than getDataAsArray`);

  for (const zone of matches1) {
    // Draw bounding rectangle
    zone.draw(parisMapMat);
  }
  const windowName = 'metro';
  // Open result in new window
  cv.imshow(windowName, parisMapMat);
  cv.setWindowTitle(windowName, `The ${matches1.length} Metros stations are here:`);
  cv.waitKey();

};

locateMetroStation();
