import { cv, getResource } from './utils';

const image = cv.imread(getResource('Lenna.png'));

const dst = image.guidedFilter(image, 10, 500, -1);

cv.imshowWait("dst", dst);