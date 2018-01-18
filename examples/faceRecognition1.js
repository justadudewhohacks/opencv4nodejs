const fs = require('fs');
const path = require('path');
const cv = require('../');

if (!cv.xmodules.face) {
  return console.log('exiting: opencv4nodejs compiled without face module');
}

const basePath = '../data/face-recognition';
const imgsPath = path.resolve(basePath, 'imgs');
const nameMappings = ['daryl', 'rick', 'negan'];

const imgFiles = fs.readdirSync(imgsPath);

const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);
const getFaceImage = (grayImg) => {
  const faceRects = classifier.detectMultiScale(grayImg).objects;
  if (!faceRects.length) {
    throw new Error('failed to detect faces');
  }
  return grayImg.getRegion(faceRects[0]);
};

const trainImgs = imgFiles
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

// make labels
const labels = imgFiles
  .map(file => nameMappings.findIndex(name => file.includes(name)));

const lbph = new cv.LBPHFaceRecognizer();
lbph.train(trainImgs, labels);

const twoFacesImg = cv.imread(path.resolve(basePath, 'daryl-rick.jpg'));
const faces = classifier.detectMultiScale(twoFacesImg.bgrToGray()).objects;

faces.forEach((faceRect) => {
  const faceImg = twoFacesImg.getRegion(faceRect).bgrToGray();
  const who = nameMappings[lbph.predict(faceImg).label];

  const upperLeft = new cv.Point(faceRect.x, faceRect.y);
  const size = new cv.Point(faceRect.width, faceRect.height);

  // make rectangle a bit larger
  const off = size.div(2);
  const upperLeftLarge = upperLeft.sub(off);
  const bottomRight = upperLeft.add(size).add(off);
  const thickness = 2;
  // draw rectangle
  twoFacesImg.drawRectangle(
    upperLeftLarge,
    bottomRight,
    {
      color: new cv.Vec(255, 0, 0),
      thickness
    }
  );

  // label the rectangle with prediction result
  twoFacesImg.putText(
    who.substr(0, 1).toUpperCase() + who.substr(1),
    upperLeftLarge.add(new cv.Point(0, 140)),
    cv.FONT_ITALIC,
    1.2,
    {
      color: new cv.Vec(0, 0, 255),
      thickness
    }
  );
});

cv.imshowWait('result', twoFacesImg);
