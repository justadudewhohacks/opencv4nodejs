import cv from '@u4/opencv4nodejs';
import { getResource } from '../utils';

// const delay = (ms: number): Promise<void> => new Promise(resolve => setTimeout(resolve, ms));

const confidence = 0.9;

const locateMetroStation = async () => {
  // Load images
  const parisMapMat = await cv.imreadAsync(getResource('templates/paris.jpg'));
  const metroMat = await cv.imreadAsync(getResource('templates/metro.png'));
  // Match template (the brightest locations indicate the highest match)
  const matched = await parisMapMat.matchTemplateAsync(metroMat, cv.TM_CCOEFF_NORMED);

  let minMaxLocTime = Date.now();
  // Use minMaxLoc to locate the highest value (or lower, depending of the type of matching method)
  const minMax = matched.minMaxLoc();
  minMaxLocTime = Date.now() - minMaxLocTime;
  const { maxLoc: { x, y } } = minMax;
  // Draw bounding rectangle
  parisMapMat.drawRectangle(
    new cv.Rect(x, y, metroMat.cols, metroMat.rows),
    new cv.Vec3(0, 255, 0),
    2,
    cv.LINE_8
  );  
  console.log(`minMaxLocTime processed in ${minMaxLocTime} ms`)



  /** using slow getDataAsArray */
  let getDataAsArrayLoopTime = Date.now();
  const lines = matched.getDataAsArray();
  const matches0 = [] as Array<{ x: number; y: number; value: number }>;
  for (let y = 0; y < lines.length; y++) {
      const line = lines[y];
      for (let x = 0; x < line.length; x++) {
          const value = line[x];
          if (value > confidence) {
              matches0.push({ x, y, value });
          }
      }
  }
  getDataAsArrayLoopTime = getDataAsArrayLoopTime - Date.now();
  console.log(`${matches0.length} region found in ${getDataAsArrayLoopTime} ms using getDataAsArray`);


  /** using slow getDataAsArray */
  let getDataLoopTime = Date.now();
  const raw = matched.getData();
  const matches1 = [] as Array<{ x: number; y: number; value: number }>;
  console.log(`buffer size is ${raw.length}`);
  // for (let y = 0; y < lines.length; y++) {
  //     const line = lines[y];
  //     for (let x = 0; x < line.length; x++) {
  //         const value = line[x];
  //         if (value > confidence) {
  //             matches0.push({ x, y, value });
  //         }
  //     }
  // }
  getDataLoopTime = getDataLoopTime - Date.now();
  console.log(`${matches0.length} region found in ${getDataLoopTime} ms using getData`);


  // const windowName = 'We\'ve found Waldo!';
  // // Open result in new window
  // cv.imshow(windowName, parisMapMat);
  // cv.setWindowTitle(windowName, "Waldo !");
  //  console.log('FULLSCREEN:', cv.getWindowProperty(windowName, cv.WND_PROP_FULLSCREEN));
  //  console.log('AUTOSIZE:', cv.getWindowProperty(windowName, cv.WND_PROP_AUTOSIZE));
  //  console.log('VISIBLE:', cv.getWindowProperty(windowName, cv.WND_PROP_VISIBLE));  
  // cv.setWindowProperty(windowName, cv.WND_PROP_VISIBLE, cv.WINDOW_FULLSCREEN)
  // cv.setWindowProperty(windowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_NORMAL)
  // cv.waitKey();
};

// noinspection JSIgnoredPromiseFromCall
locateMetroStation();
