import { cv, getResourcePath, wait4key } from '../utils';
import { makeRunDetectFacenetSSD } from './commons';

export async function facenetSSD() {
    const runDetection = makeRunDetectFacenetSSD();

    const minConfidence = 0.15;
    cv.imshow('got', runDetection(cv.imread(getResourcePath('got.jpg')), minConfidence));
    cv.imshow('Lenna', runDetection(cv.imread(getResourcePath('Lenna.png')), minConfidence));
    await wait4key();
}

facenetSSD();