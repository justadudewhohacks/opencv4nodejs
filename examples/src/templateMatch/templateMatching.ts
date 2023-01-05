import cv from '@u4/opencv4nodejs';
import { getResourcePath, wait4key } from '../utils';

const findWaldo = async () => {
  // Load images
  const originalMat = await cv.imreadAsync(getResourcePath('templates/findwaldo.jpg'));
  const waldoMat = await cv.imreadAsync(getResourcePath('templates/waldo.jpg'));
  // Match template (the brightest locations indicate the highest match)
  const matched = originalMat.matchTemplate(waldoMat, cv.TM_CCOEFF_NORMED);

  // Use minMaxLoc to locate the highest value (or lower, depending of the type of matching method)
  const minMax = matched.minMaxLoc();
  const { maxLoc: { x, y } } = minMax;
  
  // Draw bounding rectangle
  originalMat.drawRectangle(
    new cv.Rect(x, y, waldoMat.cols, waldoMat.rows),
    new cv.Vec3(0, 255, 0),
    2,
    cv.LINE_8
  );

  const windowName = 'We\'ve found Waldo!';
  // Open result in new window
  cv.imshow(windowName, originalMat);
  cv.setWindowTitle(windowName, "Waldo !");
  //  console.log('FULLSCREEN:', cv.getWindowProperty(windowName, cv.WND_PROP_FULLSCREEN));
  //  console.log('AUTOSIZE:', cv.getWindowProperty(windowName, cv.WND_PROP_AUTOSIZE));
  //  console.log('VISIBLE:', cv.getWindowProperty(windowName, cv.WND_PROP_VISIBLE));  
  // cv.setWindowProperty(windowName, cv.WND_PROP_VISIBLE, cv.WINDOW_FULLSCREEN)
  // cv.setWindowProperty(windowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_NORMAL)
  await wait4key();
};

// noinspection JSIgnoredPromiseFromCall
findWaldo();
