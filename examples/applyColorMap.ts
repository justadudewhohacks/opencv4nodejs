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

const WindowName = "applyColorMap";
cv.imshowWait(WindowName, processedImage);
//cv.setWindowProperty(WindowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_FULLSCREEN)
//cv.setWindowProperty(WindowName, cv.WND_PROP_FULLSCREEN, cv.WINDOW_NORMAL)
