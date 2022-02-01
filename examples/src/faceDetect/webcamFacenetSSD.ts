import { Mat } from '@u4/opencv4nodejs';
import { cv, grabFrames } from '../utils';
import { makeRunDetectFacenetSSD } from './commons';

const runDetection = makeRunDetectFacenetSSD();

const webcamPort = 0;

grabFrames(webcamPort, 1, function(frame: Mat) {
  cv.imshow('result', runDetection(frame, 0.2));
});
