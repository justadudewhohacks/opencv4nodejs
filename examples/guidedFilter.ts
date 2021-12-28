const path = require('path');
import cv from './utils';

const image = cv.imread(path.resolve(__dirname, '../data/Lenna.png'));

const dst = image.guidedFilter(image, 10, 500, -1);

cv.imshowWait("dst", dst);