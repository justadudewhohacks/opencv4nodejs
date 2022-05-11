import { cv, getResourcePath, wait4key } from './utils';
import fs from 'fs';
import path from 'path';
import { Mat } from '@u4/opencv4nodejs';

async function main() {
  if (!cv.xmodules || !cv.xmodules.dnn) {
    console.error(`exiting: opencv4nodejs (${cv.version.major}.${cv.version.minor}) compiled without dnn module`);
    return;
  }

  // replace with path where you unzipped inception model
  const inceptionModelPath = path.join(getResourcePath('dnn'), 'tf-inception');
  const modelFile = path.resolve(inceptionModelPath, 'tensorflow_inception_graph.pb');
  const classNamesFile = path.resolve(inceptionModelPath, 'imagenet_comp_graph_label_strings.txt');
  if (!fs.existsSync(modelFile) || !fs.existsSync(classNamesFile)) {
    fs.mkdirSync(inceptionModelPath, {recursive: true});
    console.log('could not find inception model', [modelFile, classNamesFile]);
    console.log('Download the model from: https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip');
    return;
  }

  // read classNames and store them in an array
  const classNames = fs.readFileSync(classNamesFile).toString().split('\n');

  // initialize tensorflow inception model from modelFile
  const net = cv.readNetFromTensorflow(modelFile);

  const classifyImg = (img: Mat) => {
    // inception model works with 224 x 224 images, so we resize
    // our input images and pad the image with white pixels to
    // make the images have the same width and height
    const maxImgDim = 224;
    const white = new cv.Vec3(255, 255, 255);
    const imgResized = img.resizeToMax(maxImgDim).padToSquare(white);

    // network accepts blobs as input
    const inputBlob = cv.blobFromImage(imgResized);
    net.setInput(inputBlob);

    // forward pass input through entire network, will return
    // classification result as 1xN Mat with confidences of each class
    const outputBlob = net.forward();

    // find all labels with a minimum confidence
    const minConfidence = 0.05;
    const locations =
      outputBlob
        .threshold(minConfidence, 1, cv.THRESH_BINARY)
        .convertTo(cv.CV_8U)
        .findNonZero();

    const result =
      locations.map(pt => ({
        confidence: outputBlob.at(0, pt.x),
        className: classNames[pt.x]
      }))
        // sort result by confidence
        .sort((r0, r1) => r1.confidence - r0.confidence)
        .map(res => `${res.className} (${res.confidence})`);

    return result;
  };

  const testData = [
    {
      image: getResourcePath('banana.jpg'),
      label: 'banana'
    },
    {
      image: getResourcePath('husky.jpg'),
      label: 'husky'
    },
    {
      image: getResourcePath('car.jpeg'),
      label: 'car'
    },
    {
      image: getResourcePath('lenna.png'),
      label: 'lenna'
    }
  ];

  for (const data of testData) {
    const fullpath = path.resolve(data.image);
    if (!fs.existsSync(fullpath)) {
      console.log(`${fullpath} not found`);
      return;
    }
    const img = cv.imread(fullpath);
    if (img.empty) {
      console.log(`image ${fullpath} is empty `);
      return;
    }
    console.log('%s: ', data.label);
    const predictions = classifyImg(img);
    predictions.forEach(p => console.log(p));
    console.log();

    const alpha = 0.4;
    cv.drawTextBox(
      img,
      { x: 0, y: 0 },
      predictions.map(p => ({ text: p, fontSize: 0.5, thickness: 1 })),
      alpha
    );
    cv.imshow('img', img);
    await wait4key();
  }
}

main();