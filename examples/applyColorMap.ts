import cv from '../lib';
import path from 'path';

const image = cv.imread(path.resolve(__dirname, '../data/Lenna.png'));

const processedImage = cv.applyColorMap(image, cv.COLORMAP_AUTUMN);

cv.imshowWait("applyColorMap", processedImage);
