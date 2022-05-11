import { cv, getResourcePath } from '../utils';
import { makeRunDetectFacenetSSD } from './commons';

const runDetection = makeRunDetectFacenetSSD();

const minConfidence = 0.15;
cv.imshow('got', runDetection(cv.imread(getResourcePath('got.jpg')), minConfidence));
cv.imshow('Lenna', runDetection(cv.imread(getResourcePath('Lenna.png')), minConfidence));
cv.waitKey();

