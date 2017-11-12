const cv = require('../');
const fs = require('fs');
const path = require('path');
const classNames = require('./dnnCocoClassNames');

if (!cv.xmodules.dnn) {
  return console.log('exiting: opencv4nodejs compiled without dnn module');
}

// replace with path where you unzipped inception model
const ssdcocoModelPath = '../data/dnn/coco-SSD_300x300'

const prototxt = path.resolve(ssdcocoModelPath, 'deploy.prototxt');
const modelFile = path.resolve(ssdcocoModelPath, 'VGG_coco_SSD_300x300_iter_400000.caffemodel');

if (!fs.existsSync(prototxt) || !fs.existsSync(modelFile)) {
  console.log('exiting: could not find ssdcoco model');
  console.log('download the model from: https://drive.google.com/file/d/0BzKzrI_SkD1_dUY1Ml9GRTFpUWc/view');
  return;
}

// initialize ssdcoco model from prototxt and modelFile
const net = cv.readNetFromCaffe(prototxt, modelFile);

const classifyImg = (img) => {
  const white = new cv.Vec(255, 255, 255);
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

  const results = Array(outputBlob.rows).fill(0)
    .map((res, i) => {
      const className = classNames[outputBlob.at(i, 1)];
      const confidence = outputBlob.at(i, 2);
      const topLeft = new cv.Point(
        outputBlob.at(i, 3) * img.cols,
        outputBlob.at(i, 6) * img.rows
      );
      const bottomRight = new cv.Point(
        outputBlob.at(i, 5) * img.cols,
        outputBlob.at(i, 4) * img.rows
      );

      return ({
        className,
        confidence,
        topLeft,
        bottomRight
      })
    });

    return results;
};

const makeDrawClassDetections = predictions => (drawImg, className, getColor, thickness = 2) => {
  predictions
    .filter(p => p.className === className)
    .forEach(p => {
      drawImg.drawRectangle(
        p.topLeft,
        p.bottomRight,
        getColor(),
        { thickness }
      );
    });
  return drawImg;
};

const runDetectDishesExample = () => {
  const img = cv.imread('../data/dishes.jpg');
  const minConfidence = 0.2;

  const predictions = classifyImg(img).filter(res => res.confidence > minConfidence);

  const drawClassDetections = makeDrawClassDetections(predictions);

  const classColors = {
    fork: new cv.Vec(0, 255, 0),
    bowl: new cv.Vec(255, 0, 0),
    'wine glass': new cv.Vec(0, 0, 255),
    cup: new cv.Vec(0, 255, 255)
  };

  const legendLeftTop = new cv.Point(550, 20);
  Object.keys(classColors).forEach((className, i) => {
    const color = classColors[className];

    // const draw legend
    const offY = i * 30;
    img.drawCircle(
      legendLeftTop.add(new cv.Point(0, offY)),
      3,
      color,
      { thickness: 4 }
    );
    img.putText(
      className,
      legendLeftTop.add(new cv.Point(20, offY + 8)),
      cv.FONT_ITALIC,
      0.8,
      color,
      { thickness: 2 }
    );

    // draw detections
    drawClassDetections(img, className, () => color);
  });

  cv.imshowWait('img', img);
};

const runDetectPeopleExample = () => {
  const img = cv.imread('../data/cars.jpeg');
  const minConfidence = 0.4;

  const predictions = classifyImg(img).filter(res => res.confidence > minConfidence);

  const drawClassDetections = makeDrawClassDetections(predictions);

  const getRandomColor = () => new cv.Vec(Math.random() * 255, Math.random() * 255, 255);

  drawClassDetections(img, 'car', getRandomColor);
  cv.imshowWait('img', img);
};

runDetectDishesExample();
runDetectPeopleExample();