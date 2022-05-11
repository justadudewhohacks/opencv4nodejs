import path from 'path';
import fs from 'fs';
import { cv, getResourcePath } from './utils';
import { lccs, centerLetterInImage, saveConfusionMatrix } from './OCRTools';
import { Mat } from '@u4/opencv4nodejs';

const outPath = getResourcePath('ocr');
const trainDataPath = path.join(outPath, 'traindata');
const testDataPath = path.join(outPath, 'testdata');


const SVMFile = 'lcletters.xml';

const hog = new cv.HOGDescriptor({
  winSize: new cv.Size(40, 40),
  blockSize: new cv.Size(20, 20),
  blockStride: new cv.Size(10, 10),
  cellSize: new cv.Size(10, 10),
  L2HysThreshold: 0.2,
  nbins: 9,
  gammaCorrection: true,
  signedGradient: true
});

const svm = new cv.SVM({
  kernelType: cv.ml.SVM.RBF,
  c: 12.5,
  gamma: 0.50625
});

const computeHOGDescriptorFromImage = (img: Mat, isIorJ?: boolean) => {
  let im: Mat | null = img;
  if (im.rows !== 40 || im.cols !== 40) {
    im = im.resize(40, 40);
  }

  // center the letter
  im = centerLetterInImage(img, isIorJ);
  if (!im) {
    return null;
  }

  return hog.compute(im);
};

const trainSVM = (trainDataFiles: string[][], isAuto = false) => {
  // make hog features of trainingData and label it
  console.log('make features');
  const samples: number[][] = [];
  const labels: number[] = [];
  trainDataFiles.forEach((files, label) => {
    files.forEach((file) => {
      const img = cv.imread(file);
      const isIorJ = label === 8 || label === 9;
      const desc = computeHOGDescriptorFromImage(img, isIorJ);
      if (!desc) {
        return;
      }

      samples.push(desc);
      labels.push(label);
    });
  });

  // train the SVM
  console.log('training');
  const trainData = new cv.TrainData(
    new cv.Mat(samples, cv.CV_32F),
    cv.ml.ROW_SAMPLE,
    new cv.Mat([labels], cv.CV_32S)
  );
  svm[isAuto ? 'trainAuto' : 'train'](trainData);
};

const data = lccs.map((letter) => {
  const trainDataDir = path.join(trainDataPath, letter);
  const testDataDir = path.join(testDataPath, letter);
  const train = fs.readdirSync(trainDataDir).map(file => path.join(trainDataDir,file));
  const test = fs.readdirSync(testDataDir).map(file => path.join(testDataDir, file));
  return ({ train, test });
});

const trainDataFiles = data.map(classData => classData.train);
const testDataFiles = data.map(classData => classData.test);

const numTrainImagesPerClass = trainDataFiles[0].length;
const numTestImagesPerClass = testDataFiles[0].length;
console.log('train data per class:', numTrainImagesPerClass);
console.log('test data per class:', numTestImagesPerClass);

trainSVM(trainDataFiles, false);
svm.save(path.join(outPath, SVMFile));
svm.load(path.join(outPath, SVMFile));

// compute prediction error for each letter
const errs = Array(26).fill(0);
testDataFiles.forEach((files, label) => {
  files.forEach((file) => {
    const img = cv.imread(file);
    const isIorJ = label === 8 || label === 9;
    const desc = computeHOGDescriptorFromImage(img, isIorJ);
    if (!desc) {
      throw new Error(`Computing HOG descriptor failed for file: ${file}`);
    }
    const predictedLabel = svm.predict(desc);
    if (label !== predictedLabel) {
      errs[label] += 1;
    }
  });
});

console.log('prediction result:');
errs.forEach((err, l) => console.log(lccs[l], err, 1 - (err / numTestImagesPerClass)));
console.log('average: ', 1 - (errs.reduce((e1, e2) => e1 + e2) / (lccs.length * numTestImagesPerClass)));


saveConfusionMatrix(
  testDataFiles,
  (img, isIorJ) => svm.predict(computeHOGDescriptorFromImage(img, isIorJ) as number[]),
  numTestImagesPerClass,
  path.join(outPath, 'confusionmatrix.csv')
);
