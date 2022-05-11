import fs from 'fs';
import path from 'path';
import { FaceRecognizer, Mat } from '@u4/opencv4nodejs';
import { cv, getResourcePath, wait4key } from './utils';

async function main() {
  if (!cv.xmodules || !cv.xmodules.face) {
    console.error(`exiting: opencv4nodejs (${cv.version.major}.${cv.version.minor}) compiled without face module`);
    return;
  }

  const basePath = getResourcePath('face-recognition');
  const imgsPath = path.resolve(basePath, 'imgs');
  const nameMappings = ['daryl', 'rick', 'negan'];

  const imgFiles = fs.readdirSync(imgsPath);

  const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);
  const getFaceImage = (grayImg: Mat) => {
    const faceRects = classifier.detectMultiScale(grayImg).objects;
    if (!faceRects.length) {
      throw new Error('failed to detect faces');
    }
    return grayImg.getRegion(faceRects[0]);
  };

  const images = imgFiles
    // get absolute file path
    .map(file => path.resolve(imgsPath, file))
    // read image
    .map(filePath => cv.imread(filePath))
    // face recognizer works with gray scale images
    .map(img => img.bgrToGray())
    // detect and extract face
    .map(getFaceImage)
    // face images must be equally sized
    .map(faceImg => faceImg.resize(80, 80));

  const isImageFour = (_: unknown, i: number) => imgFiles[i].includes('4');
  const isNotImageFour = (_: unknown, i: number) => !isImageFour(_, i);
  // use images 1 - 3 for training
  const trainImages = images.filter(isNotImageFour);
  // use images 4 for testing
  const testImages = images.filter(isImageFour);
  // make labels
  const labels = imgFiles
    .filter(isNotImageFour)
    .map(file => nameMappings.findIndex(name => file.includes(name)));

  const runPrediction = async (recognizer: FaceRecognizer) => {
    for (const img of testImages) {
      const result = recognizer.predict(img);
      console.log('predicted: %s, confidence: %s', nameMappings[result.label], result.confidence);
      cv.imshow('face', img);
      await wait4key();
      cv.destroyAllWindows();
    }
  };

  const eigen = new cv.EigenFaceRecognizer();
  const fisher = new cv.FisherFaceRecognizer();
  const lbph = new cv.LBPHFaceRecognizer();
  eigen.train(trainImages, labels);
  fisher.train(trainImages, labels);
  lbph.train(trainImages, labels);

  console.log('eigen:');
  await runPrediction(eigen);

  console.log('fisher:');
  await runPrediction(fisher);

  console.log('lbph:');
  await runPrediction(lbph);
}
main();