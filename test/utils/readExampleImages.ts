import fs from 'fs';
import path from 'path';
import type openCV from '@u4/opencv4nodejs';

export default function (cv: typeof openCV) {
  return {
    getTestImagePath: (isPng = true) => (isPng ? '../data/Lenna.png' : '../data/got.jpg'),
    getTestVideoPath: () => '../data/traffic.mp4',
    readTestImage: () => new cv.Mat(fs.readFileSync(path.resolve(__dirname, './Lenna.data')), 512, 512, cv.CV_8UC3),
    readPeoplesTestImage: () => new cv.Mat(fs.readFileSync(path.resolve(__dirname, './people.data')), 360, 640, cv.CV_8UC3),
  };
}
