const cv = require('../');

const img = cv.imread('../data/Lenna.png');

// single axis for 1D hist
const getHistAxis = channel => ([
  {
    channel,
    bins: 256,
    ranges: [0, 256]
  }
]);

// calc histogram for blue, green, red channel
const bHist = cv.calcHist({
  img,
  histAxes: getHistAxis(0)
});
const gHist = cv.calcHist({
  img,
  histAxes: getHistAxis(1)
});
const rHist = cv.calcHist({
  img,
  histAxes: getHistAxis(2)
});

// plot blue channel histogram
let plot = cv.plot1DHist({
  hist: bHist,
  height: 300,
  width: 600,
  lineColor: new cv.Vec(255, 0, 0)
});
// add green and red channel histograms to the plot
plot = cv.plot1DHist({
  hist: gHist,
  plotTo: plot,
  lineColor: new cv.Vec(0, 255, 0)
});
plot = cv.plot1DHist({
  hist: rHist,
  plotTo: plot,
  lineColor: new cv.Vec(0, 0, 255)
});

cv.imshow('rgb image', img);
cv.imshow('rgb histogram', plot);
cv.waitKey();

const grayImg = img.bgrToGray();
const grayHist = cv.calcHist({
  img: grayImg,
  histAxes: getHistAxis(0)
});
const grayHistPlot = cv.plot1DHist({
  hist: grayHist,
  height: 300,
  width: 600
});

cv.imshow('grayscale image', grayImg);
cv.imshow('grayscale histogram', grayHistPlot);
cv.waitKey();

