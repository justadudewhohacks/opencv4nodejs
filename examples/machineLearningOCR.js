const cv = require('../');
const fs = require('fs');

const dataPath = '';
const outPath = '../data/ocr-nocommit';

const lccs = Array(26).fill(97).map((v, i) => v + i).map(a => String.fromCharCode(a));
const folders = lccs.slice();
const classes = lccs.slice();

const numbers = Array(10).fill(0).map((v, i) => v + i);
//const folders = numbers.slice();
//const classes = numbers.slice();console.log(numbers);

/*
const deskew = (img) => {
  const m = img.bgrToGray().moments();
  if (Math.abs(m.mu02) < 0.01) return img;

  // Calculate skew based on central momemts.
  const skew = m.mu11 / m.mu02;
  console.log(skew)
  // Calculate affine transform to correct skewness.
  const warpMat = new cv.Mat([
    [1, skew, -0.5 * 40 * skew],
    [0, 1, 0]
  ], cv.cvTypes.CV_32F);

  const { WARP_INVERSE_MAP, INTER_LINEAR } = cv.cvTypes.interpolationFlags;
  console.log(WARP_INVERSE_MAP | INTER_LINEAR)
  return img.warpAffine(warpMat, { flags: (WARP_INVERSE_MAP | INTER_LINEAR) });
};
*/

const maxDigits = 500;

const trainSVM = (svm, hog, imgSize, trainData, isAuto = false) => {
  // make hog features of trainingData and label it
  console.log('make features');
  const samples = [];
  const labels = [];
  trainData.forEach((files, label) => {
    files.forEach((file) => {
      const img = cv.imread(file);
      const imgResized = img.resize(imgSize.height, imgSize.width);
      const desc = hog.compute({ img: imgResized });
      samples.push(desc);
      labels.push(label);
    });
  });

  console.log('training');
  svm[isAuto ? 'trainAuto' : 'train'](
    new cv.TrainData(
      new cv.Mat(samples, cv.cvTypes.CV_32F),
      cv.cvTypes.sampleTypes.ROW_SAMPLE,
      new cv.Mat([labels], cv.cvTypes.CV_32S)
    )
  );
};

const imgSize = new cv.Size(40, 40);
const hog = new cv.HOGDescriptor({
  // winSize: new cv.Size(10, 10),
  // winSize: new cv.Size(12, 12),
  // winSize: new cv.Size(20, 15),
  winSize: new cv.Size(40, 40),
  // blockSize: new cv.Size(12, 12),
  // blockSize: new cv.Size(16, 16),
  // blockSize: new cv.Size(20, 15),
  blockSize: new cv.Size(10, 10),
  // blockStride: new cv.Size(2, 2),
  // blockStride: new cv.Size(4, 4),
  blockStride: new cv.Size(5, 5),
  // cellSize: new cv.Size(4, 4),
  // cellSize: new cv.Size(8, 8),
  cellSize: new cv.Size(5, 5),
  L2HysThreshold: 0.2,
  nbins: 9,
  gammaCorrection: true,
  signedGradient: true
});

const svm = new cv.SVM({
  kernelType: cv.cvTypes.svmKernelTypes.RBF,
  c: 12.5,
  gamma: 0.03375 // gamma: 0.50625
});

const data = classes.map((c, label) => {
  const dir = `${dataPath}/${folders[label]}`;
  const files = fs.readdirSync(dir);
  return ({
    train: files.slice(0, 5).map(f => `${dir}/${f}`),
    test: files.slice(5).map(f => `${dir}/${f}`)
  });
});

const trainData = data.map(classData => classData.train);
const testData = data.map(classData => classData.test);

//trainSVM(svm, hog, imgSize, trainData, false);
//svm.save(`${outPath}/lcletters.xml`);
svm.load(`${outPath}/lcletters.xml`);
console.log(svm);


const predict = img => svm.predict(hog.compute({ img }));
/**
const errs = Array(10).fill(0);
classes.forEach((c) => {
  for (let i = 1; i < 50; i += 1) {
    const img = cv.imread(`${testPath}/${c}/${i}.png`);
    if(c !== classes[predict(img)]) {
      errs[c] = errs[c] + 1;
    }
  }
});

console.log(errs);


for (let c = 0; c < 4; c++) {
  for (let i = 1; i < 4; i++) {
    const img = cv.imread(`C:/Users/user/Pictures/ocr/ocr-self/digits/${c}_${i}.png`);
    console.log(c, classes[predict(img.resize(28, 28))])
  }
}
*/

testData.forEach((files, label) => {
  files.forEach((file) => {
    const img = cv.imread(file);
    console.log(classes[label], classes[predict(img.resize(imgSize.height, imgSize.width))])
  });
});
