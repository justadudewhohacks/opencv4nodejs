import * as path from 'path';
import * as cv from '../../';

if (!cv.xmodules.text) {
  throw new Error('exiting: opencv4nodejs compiled without text module');
}

const dataPath = path.resolve('../../data/text-data/');
const modelsPath = path.resolve('../../data/text-models');
const beamSearchModel = path.resolve(modelsPath, 'OCRBeamSearch_CNN_model_data.xml.gz');

const vocabulary = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
const lexicon = [
  'abb', 'riser', 'CHINA', 'HERE', 'HERO', 'President', 'smash', 'KUALA', 'Produkt', 'NINTENDO',
  'foo', 'asdf', 'BAR', 'this', 'makes', 'no', 'sense', 'at', 'all'
];

const transitionP = cv.createOCRHMMTransitionsTable(vocabulary, lexicon);
const emissionP = cv.Mat.eye(62, 62, cv.CV_64FC1);
const hmmClassifier = cv.loadOCRHMMClassifierCNN(beamSearchModel);
const hmmDecoder = new cv.OCRHMMDecoder(hmmClassifier, vocabulary, transitionP, emissionP);

const wordImages = ['scenetext_word01.jpg', 'scenetext_word02.jpg']
  .map(file => path.resolve(dataPath, file))
  .map(cv.imread);

wordImages.forEach((img) => {
  const grayImg = img.type === cv.CV_8U ? img : img.bgrToGray();
  const mask = grayImg.threshold(100, 255, cv.THRESH_BINARY_INV);

  const ret = hmmDecoder.runWithInfo(grayImg, mask);

  console.log('outputText:', ret.outputText);
  cv.imshow('mask', mask);
  cv.imshowWait('img', img);
});
