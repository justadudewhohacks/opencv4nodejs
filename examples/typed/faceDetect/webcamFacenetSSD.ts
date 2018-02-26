import {
  grabFrames
} from '../utils';
import { makeRunDetectFacenetSSD } from './commons';
import * as cv from '../../../';

const runDetection = makeRunDetectFacenetSSD();

const webcamPort = 0;

grabFrames(webcamPort, 1, function(frame: cv.Mat) {
  cv.imshow('result', runDetection(frame, 0.2));
});
