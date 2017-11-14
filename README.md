opencv4nodejs
=============
[![Build Status](https://travis-ci.org/justadudewhohacks/opencv4nodejs.svg?branch=master)](http://travis-ci.org/justadudewhohacks/opencv4nodejs)
[![Coverage](https://codecov.io/github/justadudewhohacks/opencv4nodejs/coverage.svg?branch=master)](https://codecov.io/gh/justadudewhohacks/opencv4nodejs)
[![npm download](https://img.shields.io/npm/dm/opencv4nodejs.svg?style=flat)](https://www.npmjs.com/package/opencv4nodejs)
[![node version](https://img.shields.io/badge/node.js-%3E=_6-green.svg?style=flat)](http://nodejs.org/download/)

**By its nature, JavaScript lacks the performance to implement Computer Vision tasks efficiently. Therefore this package brings the performance of the native OpenCV library to your Node.js application. Supports all OpenCV 3 versions. The bindings are available as an asynchronous (via promises or callbacks) and synchronous API.**

**The ultimate goal of this project is to provide a collection of Node.js bindings, which supports the entire OpenCV and OpenCV-contrib API. An overview of available bindings can be found in the [API Documentation](https://justadudewhohacks.github.io/opencv4nodejs/docs/). The implementation of missing bindings can be specifically prioritized by [requesting new features](#request-features). Furthermore, contribution is highly appreciated. If you want to get involved you can have a look at the <a href="https://github.com/justadudewhohacks/opencv4nodejs/tree/master/CONTRIBUTING.md"><b>contribution guide</b>.**

 * **[Examples](#examples)**
 * **[How to install](#how-to-install)**
 * **[Usage with Docker](#usage-with-docker)**
 * **[Usage with Electron](#usage-with-electron)**
 * **[Quick Start](#quick-start)**
 * **[Async API](#async-api)**
 * **[Available Modules](#available-modules)**
 * **[Request new Features](#request-features)**

<a name="examples"></a>

## Examples

See <a href="https://github.com/justadudewhohacks/opencv4nodejs/tree/master/examples"><b>examples</b></a> for implementation.

### Face Detection

![face0](https://user-images.githubusercontent.com/31125521/29702727-c796acc4-8972-11e7-8043-117dd2761833.jpg)
![face1](https://user-images.githubusercontent.com/31125521/29702730-c79d3904-8972-11e7-8ccb-e8c467244ad8.jpg)

### Face Recognition

Check out my <a href="https://medium.com/@muehler.v/simple-hand-gesture-recognition-using-opencv-and-javascript-eb3d6ced28a0"><b>article</b></a> about face recognition.

![facerec](https://user-images.githubusercontent.com/31125521/32416405-d71ad684-c248-11e7-9a6f-016d0edf2c15.jpg)

### Hand Gesture Recognition
Check out my <a href="https://medium.com/@muehler.v/simple-hand-gesture-recognition-using-opencv-and-javascript-eb3d6ced28a0"><b>article</b></a> about fingertip detection.

![gesture-rec_sm](https://user-images.githubusercontent.com/31125521/30052864-41bd5680-9227-11e7-8a62-6205f3d99d5c.gif)

### Object Recognition with Deep Neural Networks

#### Tensorflow Inception

![husky](https://user-images.githubusercontent.com/31125521/32703295-f6b0e7ee-c7f3-11e7-8039-b3ada21810a0.jpg)
![car](https://user-images.githubusercontent.com/31125521/32703296-f6cea892-c7f3-11e7-8aaa-9fe48b88fe05.jpeg)
![banana](https://user-images.githubusercontent.com/31125521/32703297-f6e932ca-c7f3-11e7-9a66-bbc826ebf007.jpg)


#### Single Shot Multibox Detector with COCO

![dishes-detection](https://user-images.githubusercontent.com/31125521/32703228-eae787d4-c7f2-11e7-8323-ea0265deccb3.jpg)
![car-detection](https://user-images.githubusercontent.com/31125521/32703229-eb081e36-c7f2-11e7-8b26-4d253b4702b4.jpg)

### Machine Learning
Check out my <a href="https://medium.com/@muehler.v/machine-learning-with-opencv-and-javascript-part-1-recognizing-handwritten-letters-using-hog-and-88719b70efaa"><b>article</b></a> about recognition of handwritten letters using Histogram of oriented Gradients (HOG) and Support Vector Machines (SVM).

![resulttable](https://user-images.githubusercontent.com/31125521/30635645-5a466ea8-9df3-11e7-8498-527e1293c4fa.png)

### Object Tracking

![trackbgsubtract](https://user-images.githubusercontent.com/31125521/29702733-c7b59864-8972-11e7-996b-d28cb508f3b8.gif)
![trackbycolor](https://user-images.githubusercontent.com/31125521/29702735-c8057686-8972-11e7-9c8d-13e30ab74628.gif)

### Feature Matching

![matchsift](https://user-images.githubusercontent.com/31125521/29702731-c79e3142-8972-11e7-947e-db109d415469.jpg)

### Image Histogram

![plotbgr](https://user-images.githubusercontent.com/31125521/29995016-1b847970-8fdf-11e7-9316-4eb0fd550adc.jpg)
![plotgray](https://user-images.githubusercontent.com/31125521/29995015-1b83e06e-8fdf-11e7-8fa8-5d18326b9cd3.jpg)

<a name="how-to-install"></a>

## How to install

``` bash
$ npm install --save opencv4nodejs
```

Make sure to have OpenCV 3+ ( extra modules are optional ) installed on your System https://github.com/opencv/opencv/releases/. In case you are running Windows or have OpenCV set up in a custom directory make sure to set the following environment variables:
1. OPENCV_DIR pointing to the root path containing include directory or set OPENCV_INCLUDE_DIR explicitly.
2. OPENCV_LIB_DIR pointing to the library dir containing the OpenCV .lib or .so files.

If you are running into issues also check the requirements for node-gyp specific to your OS https://github.com/nodejs/node-gyp.

<a name="usage-with-docker"></a>

## Usage with Docker

### [opencv-express](https://github.com/justadudewhohacks/opencv-express) - example for opencv4nodejs with express.js and docker

Or simply pull from [justadudewhohacks/opencv-nodejs](https://hub.docker.com/r/justadudewhohacks/opencv-nodejs/) for opencv-3.2 + contrib-3.2 with opencv4nodejs globally installed:

``` docker
FROM justadudewhohacks/opencv-nodejs
```

Different OpenCV 3.x base images can be found here: https://hub.docker.com/r/justadudewhohacks/.

<a name="usage-with-electron"></a>

## Usage with Electron

### [opencv-electron](https://github.com/justadudewhohacks/opencv-electron) - example for opencv4nodejs with electron

Add the following script to your package.json:
``` python
"electron-rebuild": "electron-rebuild -w opencv4nodejs"
```

Run the script:
``` bash
$ npm run electron-rebuild
```

Require it in the application:
``` javascript
const electron = require('electron');
const cv = electron.remote.require('opencv4nodejs');
```

<a name="quick-start"></a>

## Quick Start

``` javascript
const cv = require('opencv4nodejs');
```

### Initializing Mat (image matrix), Vec, Point

``` javascript
const rows = 100; // height
const cols = 100; // width

// empty Mat
const emptyMat = new cv.Mat(rows, cols, cv.CV_8UC3);

// fill the Mat with default value
const whiteMat = new cv.Mat(rows, cols, cv.CV_8UC1, 255);
const blueMat = new cv.Mat(rows, cols, cv.CV_8UC3, [255, 0, 0]);

// from array (3x3 Matrix, 3 channels)
const matData = [
  [[255, 0, 0], [255, 0, 0], [255, 0, 0]],
  [[0, 0, 0], [0, 0, 0], [0, 0, 0]],
  [[255, 0, 0], [255, 0, 0], [255, 0, 0]]
];
const matFromArray = new cv.Mat(matData, cv.CV_8UC3);

// from node buffer
const charData = [255, 0, ...];
const matFromArray = new cv.Mat(new Buffer.from(charData), rows, cols, cv.CV_8UC3);

// Point
const pt2 = new cv.Point(100, 100);
const pt3 = new cv.Point(100, 100, 0.5);

// Vector
const vec2 = new cv.Vec(100, 100);
const vec3 = new cv.Vec(100, 100, 0.5);
const vec4 = new cv.Vec(100, 100, 0.5, 0.5);
```

### Mat and Vec operations

``` javascript
const mat0 = new cv.Mat(...);
const mat1 = new cv.Mat(...);

// arithmetic operations for Mats and Vecs
const matMultipliedByScalar = mat0.mul(0.5);  // scalar multiplication
const matDividedByScalar = mat0.div(2);       // scalar division
const mat0PlusMat1 = mat0.add(mat1);          // addition
const mat0MinusMat1 = mat0.sub(mat1);         // subtraction
const mat0MulMat1 = mat0.hMul(mat1);          // elementwise multiplication
const mat0DivMat1 = mat0.hDiv(mat1);          // elementwise division

// logical operations Mat only
const mat0AndMat1 = mat0.and(mat1);
const mat0OrMat1 = mat0.or(mat1);
const mat0bwAndMat1 = mat0.bitwiseAnd(mat1);
const mat0bwOrMat1 = mat0.bitwiseOr(mat1);
const mat0bwXorMat1 = mat0.bitwiseXor(mat1);
const mat0bwNot = mat0.bitwiseNot();
```

### Accessing Mat data

``` javascript
const matBGR = new cv.Mat(..., cv.CV_8UC3);
const matGray = new cv.Mat(..., cv.CV_8UC1);

// get pixel value as vector or number value
const vec3 = matBGR.at(200, 100);
const grayVal = matGray.at(200, 100);

// get raw pixel value as array
const [b, g, r] = matBGR.atRaw(200, 100);

// set single pixel values
matBGR.set(50, 50, [255, 0, 0]);
matBGR.set(50, 50, new Vec(255, 0, 0));
matGray.set(50, 50, 255);

// get a 25x25 sub region of the Mat at offset (50, 50)
const width = 25;
const height = 25;
const region = matBGR.getRegion(new cv.Rect(50, 50, width, height));

// get a node buffer with raw Mat data
const matAsBuffer = matBGR.getData();

// get entire Mat data as JS array
const matAsArray = matBGR.getDataAsArray();
```

### IO

``` javascript
// load image from file
const mat = cv.imread('./path/img.jpg');
cv.imreadAsync('./path/img.jpg', (err, mat) => {
  ...
})

// save image
cv.imwrite('./path/img.png', mat);
cv.imwriteAsync('./path/img.jpg', (err) => {
  ...
})

// show image
cv.imshow('a window name', mat);
cv.waitKey();

// open capture from webcam
const devicePort = 0;
const wCap = new cv.VideoCapture(devicePort);

// open video capture
const vCap = new cv.VideoCapture('./path/video.mp4');

// read frames from capture
const frame = vCap.read();
vCap.readAsync((err, frame) => {
  ...
});

// loop through the capture
const delay = 10;
let done = false;
while (!done) {
  let frame = vCap.read();
  // loop back to start on end of stream reached
  if (frame.empty) {
    vCap.reset();
    frame = vCap.read();
  }

  // ...

  const key = cv.waitKey(delay);
  done = key !== 255;
}
```

### Useful Mat methods

``` javascript
const matBGR = new cv.Mat(..., cv.CV_8UC3);

// convert types
const matSignedInt = matBGR.convertTo(cv.CV_32SC3);
const matDoublePrecision = matBGR.convertTo(cv.CV_64FC3);

// convert color space
const matGray = matBGR.bgrToGray();
const matHSV = matBGR.cvtColor(cv.COLOR_BGR2HSV);
const matLab = matBGR.cvtColor(cv.COLOR_BGR2Lab);

// resize
const matHalfSize = matBGR.rescale(0.5);
const mat100x100 = matBGR.resize(100, 100);
const matMaxDimIs100 = matBGR.resizeToMax(100);

// extract channels and create Mat from channels
const [matB, matG, matR] = matBGR.splitChannels();
const matRGB = new cv.Mat([matR, matB, matG]);
```

### Drawing a Mat into HTML Canvas

``` javascript
const img = ...

// convert your image to rgba color space
const matRGBA = img.channels === 1
  ? img.cvtColor(cv.COLOR_GRAY2RGBA)
  : img.cvtColor(cv.COLOR_BGR2RGBA);

// create new ImageData from raw mat data
const imgData = new ImageData(
  new Uint8ClampedArray(matRGBA.getData()),
  img.cols,
  img.rows
);

// set canvas dimensions
const canvas = document.getElementById('myCanvas');
canvas.height = img.rows;
canvas.width = img.cols;

// set image data
const ctx = canvas.getContext('2d');
ctx.putImageData(imgData, 0, 0);
```

### Method Interface

OpenCV method interface from official docs or src:
``` c++
void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFAULT);
```

translates to:

``` javascript
const src = new cv.Mat(...);
// invoke with required arguments
const dst0 = src.gaussianBlur(new cv.Size(5, 5), 1.2);
// with optional paramaters
const dst2 = src.gaussianBlur(new cv.Size(5, 5), 1.2, 0.8, cv.BORDER_REFLECT);
// or pass specific optional parameters
const optionalArgs = {
  borderType: cv.BORDER_CONSTANT
};
const dst2 = src.gaussianBlur(new cv.Size(5, 5), 1.2, optionalArgs);
```

<a name="async-api"></a>

## Async API

The async API can be consumed by passing a callback as the last argument of the function call. By default, if an async method is called without passing a callback, the function call will yield a Promise.

### Async Face Detection

``` javascript
const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

// by nesting callbacks
cv.imreadAsync('./faceimg.jpg', (err, img) => {
  if (err) { return console.error(err); }

  const grayImg = img.bgrToGray();
  classifier.detectMultiScaleAsync(grayImg, (err, res) => {
    if (err) { return console.error(err); }

    const { objects, numDetections } = res;
    ...
  });
});

// via Promise
cv.imreadAsync('./faceimg.jpg')
  .then(img =>
    img.bgrToGrayAsync()
      .then(grayImg => classifier.detectMultiScaleAsync(grayImg))
      .then((res) => {
        const { objects, numDetections } = res;
        ...
      })
  )
  .catch(err => console.error(err));

// using async await
try {
  const img = await cv.imreadAsync('./faceimg.jpg');
  const grayImg = await img.bgrToGrayAsync();
  const { objects, numDetections } = await classifier.detectMultiScaleAsync(grayImg);
  ...
} catch (err) {
  console.error(err);
}
```

<a name="available-modules"></a>

## Available Modules

### <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>API doc overview</b></a>

* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>core</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>io</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>imgproc</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>ximgproc</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>objdetect</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>machinelearning</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>deepneuralnetworks</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>video</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>calib3d</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>photo</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>features2d</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>xfeatures2d</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>tracking</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>text</b></a>
* <a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>face</b></a>

<a name="request-features"></a>

## Request new Features

Are you missing some functions from OpenCV (<a href="https://justadudewhohacks.github.io/opencv4nodejs/docs/"><b>overview</b></a> of available bindings) or have an idea for utility in regards to the OpenCV API, which you would like to be added to this package? No problem! Open a new <a href="https://github.com/justadudewhohacks/opencv4nodejs/issues"><b>issue</b></a> with a listing of the desired function bindings or features and you will find them in this package soon.


