import { cv } from './utils';
import path from 'path';

const file = path.resolve(__dirname, '..', 'data', 'Lenna.png');
console.log('loading ', file);
const image = cv.imread(file);
console.log('Lenna.png loaded');
const processedImage = cv.applyColorMap(image, cv.COLORMAP_AUTUMN);

cv.imshowWait("applyColorMap", processedImage);
