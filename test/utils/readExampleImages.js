const fs = require('fs')
const path = require('path')

module.exports = function(cv) {

  const getTestImagePath = (isPng = true) =>
    (isPng ? '../data/Lenna.png' : '../data/got.jpg');
  const getTestVideoPath = () => '../data/traffic.mp4';

  return {
    getTestImagePath,
    getTestVideoPath,
    readTestImage: () => new cv.Mat(fs.readFileSync(path.resolve(__dirname, './Lenna.data')), 512, 512, cv.CV_8UC3),
    readPeoplesTestImage: () => new cv.Mat(fs.readFileSync(path.resolve(__dirname, './people.data')), 360, 640, cv.CV_8UC3)
  };
};