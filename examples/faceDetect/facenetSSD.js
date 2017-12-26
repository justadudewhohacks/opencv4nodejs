const {
  cv,
  getDataFilePath,
  drawBlueRect
} = require('../utils');
const loadFacenet = require('../dnn/loadFacenet');
const { extractResults } = require('../dnn/ssdUtils');

const net = loadFacenet();

function classifyImg(img) {
  // facenet model works with 300 x 300 images
  const imgResized = img.resizeToMax(300);

  // network accepts blobs as input
  const inputBlob = cv.blobFromImage(imgResized);
  net.setInput(inputBlob);

  // forward pass input through entire network, will return
  // classification result as 1x1xNxM Mat
  let outputBlob = net.forward();
  // extract NxM Mat
  outputBlob = outputBlob.flattenFloat(outputBlob.sizes[2], outputBlob.sizes[3]);

  return extractResults(outputBlob, img);
}

function runDetection(img, minConfidence) {
  const predictions = classifyImg(img);
  console.log('predictons: ', predictions);

  predictions
    .filter(res => res.confidence > minConfidence)
    .forEach(p => drawBlueRect(img, p.rect));

  cv.imshowWait('result', img);
}

const minConfidence = 0.15;
runDetection(cv.imread(getDataFilePath('got.jpg')), minConfidence);
runDetection(cv.imread(getDataFilePath('Lenna.png')), minConfidence);

