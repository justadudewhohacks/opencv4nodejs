const {
  cv,
  getDataFilePath
} = require('../utils');

const { makeRunDetectFacenetSSD } = require('./commons');

const runDetection = makeRunDetectFacenetSSD();

const minConfidence = 0.15;
cv.imshow('got', runDetection(cv.imread(getDataFilePath('got.jpg')), minConfidence));
cv.imshow('Lenna', runDetection(cv.imread(getDataFilePath('Lenna.png')), minConfidence));
cv.waitKey();

