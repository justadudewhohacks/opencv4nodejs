import * as cv from '../../';

const img = cv.imread('../../data/Lenna.png');

// single axis for 1D hist
const getHistAxis = (channel: number) => ([
  {
    channel,
    bins: 256,
    ranges: [0, 256]
  }
]);

// calc histogram for blue, green, red channel
const bHist = cv.calcHist(img, getHistAxis(0));
const gHist = cv.calcHist(img, getHistAxis(1));
const rHist = cv.calcHist(img, getHistAxis(2));

const blue = new cv.Vec3(255, 0, 0);
const green = new cv.Vec3(0, 255, 0);
const red = new cv.Vec3(0, 0, 255);

// plot channel histograms
const plot = new cv.Mat(300, 600, cv.CV_8UC3, [255, 255, 255]);
cv.plot1DHist(bHist, plot, blue, cv.LINE_8, 2);
cv.plot1DHist(gHist, plot, green, cv.LINE_8, 2);
cv.plot1DHist(rHist, plot, red, cv.LINE_8, 2);

cv.imshow('rgb image', img);
cv.imshow('rgb histogram', plot);
cv.waitKey();

const grayImg = img.bgrToGray();
const grayHist = cv.calcHist(grayImg, getHistAxis(0));
const grayHistPlot = new cv.Mat(300, 600, cv.CV_8UC3, [255, 255, 255]);
cv.plot1DHist(grayHist, grayHistPlot, new cv.Vec3(0, 0, 0));

cv.imshow('grayscale image', grayImg);
cv.imshow('grayscale histogram', grayHistPlot);
cv.waitKey();

