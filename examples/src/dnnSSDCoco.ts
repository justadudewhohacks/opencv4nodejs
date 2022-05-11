import { getResourcePath, drawRect, wait4key } from './utils';
import fs from 'fs';
import path from 'path';
import { classNames } from './data/dnnCocoClassNames';
import { extractResults, Prediction } from './dnn/ssdUtils';
import {cv, Mat, Net, Vec3 } from '@u4/opencv4nodejs';

if (!cv.xmodules || !cv.xmodules.dnn) {
  throw new Error('exiting: opencv4nodejs compiled without dnn module');
}

function classifyImg(net: Net, img: Mat) {
  // ssdcoco model works with 300 x 300 images
  const imgResized = img.resize(300, 300);

  // network accepts blobs as input
  const inputBlob = cv.blobFromImage(imgResized);
  net.setInput(inputBlob);

  // forward pass input through entire network, will return
  // classification result as 1x1xNxM Mat
  let outputBlob = net.forward();
  // extract NxM Mat
  outputBlob = outputBlob.flattenFloat(outputBlob.sizes[2], outputBlob.sizes[3]);

  return extractResults(outputBlob, img)
    .map(r => Object.assign({}, r, { className: classNames[r.classLabel] }));
}

const makeDrawClassDetections = (predictions: Prediction[]) => (drawImg: Mat, className: string, getColor: () => Vec3, thickness = 2) => {
  predictions
    .filter(p => classNames[p.classLabel] === className)
    .forEach(p => drawRect(drawImg, p.rect, getColor(), { thickness }));
  return drawImg;
};

const runDetectDishesExample = async (net: Net) => {
  const img = cv.imread(getResourcePath('dishes.jpg'));
  const minConfidence = 0.2;

  const predictions = classifyImg(net, img).filter(res => res.confidence > minConfidence);

  const drawClassDetections = makeDrawClassDetections(predictions);

  const classColors: {[name: string]: Vec3} = {
    fork: new cv.Vec3(0, 255, 0),
    bowl: new cv.Vec3(255, 0, 0),
    'wine glass': new cv.Vec3(0, 0, 255),
    cup: new cv.Vec3(0, 255, 255)
  };

  const legendLeftTop = new cv.Point2(580, 20);
  const alpha = 0.4;
  cv.drawTextBox(
    img,
    legendLeftTop,
    Object.keys(classColors).map(className => ({
      text: className,
      fontSize: 0.8,
      color: classColors[className]
    })),
    alpha
  );

  Object.keys(classColors).forEach((className) => {
    const color = classColors[className];
    // draw detections
    drawClassDetections(img, className, () => color);
  });

  cv.imshow('img', img);
  await wait4key();
};

const runDetectPeopleExample = async (net: Net) => {
  const img = cv.imread(getResourcePath('cars.jpeg'));
  const minConfidence = 0.4;

  const predictions = classifyImg(net, img).filter(res => res.confidence > minConfidence);

  const drawClassDetections = makeDrawClassDetections(predictions);

  const getRandomColor = () => new cv.Vec3(Math.random() * 255, Math.random() * 255, 255);

  drawClassDetections(img, 'car', getRandomColor);
  cv.imshow('img', img);
  await wait4key();
};

async function main() {
  // replace with path where you unzipped inception model
  const ssdcocoModelPath = path.join(getResourcePath('dnn'), 'coco-SSD_300x300');
  const prototxt = path.resolve(ssdcocoModelPath, 'deploy.prototxt');
  const modelFile = path.resolve(ssdcocoModelPath, 'VGG_coco_SSD_300x300_iter_400000.caffemodel');

  if (!fs.existsSync(prototxt) || !fs.existsSync(modelFile)) {
    console.log('could not find ssdcoco model in ', ssdcocoModelPath);
    try {
      fs.mkdirSync(ssdcocoModelPath, {recursive: true});
    } catch (e) {
      // ignore
    }
    //console.log('Download the model from: https://drive.google.com/file/d/0BzKzrI_SkD1_dUY1Ml9GRTFpUWc/view');
    // console.log('Download the model from: https://drive.google.com/u/0/uc?id=0BzKzrI_SkD1_dUY1Ml9GRTFpUWc&export=download');
    console.log('Download the model from: https://drive.google.com/u/0/uc?export=download&id=0BzKzrI_SkD1_dUY1Ml9GRTFpUWc');
    return;
    // throw new Error('exiting: could not find ssdcoco model');
  }

  // initialize ssdcoco model from prototxt and modelFile
  const net = cv.readNetFromCaffe(prototxt, modelFile);

  await runDetectDishesExample(net);
  await runDetectPeopleExample(net);
}
main();
