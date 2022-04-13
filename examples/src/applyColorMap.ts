// using default import
import cv from '@u4/opencv4nodejs';
import { getResource } from './utils';

const file = getResource('Lenna.png');
console.log('loading ', file);
const image = cv.imread(file);
console.log('Lenna.png loaded');
const processedImage = cv.applyColorMap(image, cv.COLORMAP_AUTUMN);

const windowName = "applyColorMap";
cv.imshow(windowName, processedImage);
cv.setWindowProperty(windowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_FULLSCREEN)
// console.log('FULLSCREEN:', cv.getWindowProperty(windowName, cv.WND_PROP_FULLSCREEN));
// console.log('AUTOSIZE:', cv.getWindowProperty(windowName, cv.WND_PROP_AUTOSIZE));
// console.log('VISIBLE:', cv.getWindowProperty(windowName, cv.WND_PROP_VISIBLE));
// cv.setWindowProperty(windowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_NORMAL)
cv.waitKey();

