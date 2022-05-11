import { cv, getResourcePath, wait4key } from './utils';


export async function guidedFilter() {
    const image = cv.imread(getResourcePath('Lenna.png'));
    const dst = image.guidedFilter(image, 10, 500, -1);
    cv.imshow("dst", dst);
    await wait4key();
}

guidedFilter();