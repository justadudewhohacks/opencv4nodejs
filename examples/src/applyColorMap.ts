// using default import
import cv from '@u4/opencv4nodejs';
import { getResourcePath, wait4key } from './utils';

export async function applyColorMap() {
    const file = getResourcePath('Lenna.png');
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
    await wait4key();
}
applyColorMap();