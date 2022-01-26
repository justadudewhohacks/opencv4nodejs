// using default import
import cv from '..';
// using old import style
// import { cv } from './utils';
import path from 'path';

const file = path.resolve(__dirname, '..', 'data', 'Lenna.png');
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

