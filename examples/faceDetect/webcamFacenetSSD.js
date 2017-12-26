const {
  cv,
  grabFrames
} = require('../utils');

const { makeRunDetectFacenetSSD } = require('./commons');

const runDetection = makeRunDetectFacenetSSD();

const webcamPort = 0;

grabFrames(webcamPort, 1, function(frame) {
  cv.imshow('result', runDetection(frame, 0.2));
});
