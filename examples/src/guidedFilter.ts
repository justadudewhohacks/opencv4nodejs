import { cv, getResourcePath } from './utils';

const image = cv.imread(getResourcePath('Lenna.png'));

const dst = image.guidedFilter(image, 10, 500, -1);

cv.imshowWait("dst", dst);