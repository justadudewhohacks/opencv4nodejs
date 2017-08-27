opencv4nodejs
=============
[![Build Status](https://travis-ci.org/justadudewhohacks/opencv4nodejs.svg?branch=master)](http://travis-ci.org/justadudewhohacks/opencv4nodejs)

**Brings lots of features of OpenCV 3.x to nodejs to use as a service, integrate into your Electron app or simply to play around with the OpenCV API in Javascript instead of C++.**

## How to install

``` bash
$ npm install --save opencv4nodejs
```

Make sure to have OpenCV 3+ ( extra modules are optional ) installed on your System https://github.com/opencv/opencv/releases/. In case you are running Windows or have OpenCV set up in a custom directory make sure to set the following environment variables:
1. OPENCV_DIR pointing to the root path containing include directory or set OPENCV_INCLUDE_DIR explicitly.
2. OPENCV_LIB_DIR pointing to the static library dir containing the OpenCV .lib or .so files.

If you are running into issues also check the requirements for node-gyp specific to your OS https://github.com/nodejs/node-gyp.

## Usage with Electron

``` bash
$ npm install --save electron-rebuild
```

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

## Examples

See examples folder for implementation.

### Face Detection

![face0](https://user-images.githubusercontent.com/31125521/29702727-c796acc4-8972-11e7-8043-117dd2761833.jpg)
![face1](https://user-images.githubusercontent.com/31125521/29702730-c79d3904-8972-11e7-8ccb-e8c467244ad8.jpg)

### Object Tracking

![trackbgsubtract](https://user-images.githubusercontent.com/31125521/29702733-c7b59864-8972-11e7-996b-d28cb508f3b8.gif)
![trackbycolor](https://user-images.githubusercontent.com/31125521/29702735-c8057686-8972-11e7-9c8d-13e30ab74628.gif)

### Feature Matching

![matchorb](https://user-images.githubusercontent.com/31125521/29702728-c7983be8-8972-11e7-8773-e1f01631a1eb.jpg)
![matchsift](https://user-images.githubusercontent.com/31125521/29702731-c79e3142-8972-11e7-947e-db109d415469.jpg)

### Image Histogram

![plotbgr](https://user-images.githubusercontent.com/31125521/29702729-c798f83a-8972-11e7-9b40-b42829cc2bb7.jpg)
![plotgray](https://user-images.githubusercontent.com/31125521/29702732-c7a42746-8972-11e7-9f9f-945edc20045e.jpg)

## Documentation

``` javascript
const cv = require('opencv4nodejs');
```

### Initializing Mat (image matrix), Vec, Point

``` javascript
const rows = 100; // height
const cols = 100; // width

// empty Mat
const emptyMat = new cv.Mat(rows, cols, cv.cvTypes.CV_8UC3);

// fill the Mat with default value
const whiteMat = new cv.Mat(rows, cols, cv.cvTypes.CV_8UC1, 255);
const blueMat = new cv.Mat(rows, cols, cv.cvTypes.CV_8UC3, [255, 0, 0]);

// from array (3x3 Matrix, 3 channels)
const matData = [
  [[255, 0, 0], [255, 0, 0], [255, 0, 0]],
  [[0, 0, 0], [0, 0, 0], [0, 0, 0]],
  [[255, 0, 0], [255, 0, 0], [255, 0, 0]]
];
const matFromArray = new cv.Mat(matData, cv.cvTypes.CV_8UC3);

// from node buffer
const charData = [255, 0, ...];
const matFromArray = new cv.Mat(new Buffer.from(charData), rows, cols, cv.cvTypes.CV_8UC3);

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
const matBGR = new cv.Mat(..., cv.cvTypes.CV_8UC3);
const matGray = new cv.Mat(..., cv.cvTypes.CV_8UC1);

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
const matAsArray = matBGR.getData();

// get entire Mat data as JS array
const matAsArray = matBGR.getDataAsArray();
```

### IO

``` javascript
// load image from file
const mat = cv.imread('./path/img.jpg');

// save image
cv.imwrite('./path/img.png', mat);

// show image
cv.imshow('a window name', mat);
cv.waitKey();
```

### Useful Mat methods

``` javascript
const matBGR = new cv.Mat(..., cv.cvTypes.CV_8UC3);

// convert types
const matSignedInt = matBGR.convertTo({
  type: cv.cvTypes.CV_32SC3
});
const matDoublePrecision = matBGR.convertTo({
  type: cv.cvTypes.CV_64FC3
});

// convert color space
const { COLOR_BGR2HSV, COLOR_BGR2Lab } = cv.cvTypes;
const matGray = matBGR.bgrToGray();
const matHSV = matBGR.cvtColor({
  code: COLOR_BGR2HSV
});
const matLab = matBGR.cvtColor({
  code: COLOR_BGR2Lab
});

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
    const matBGR = ...;
    // convert your Mat to rgba space
    const matRGBA = matBGR.cvtColor({
      type: cv.cvTypes.colorConversionCodes.COLOR_BGR2RGBA
    });
    // get raw Mat data
    const matDataRaw = matRGBA.getData();

    // fill canvas pixels
    const canvas = document.getElementById('myCanvas');
    const ctx = canvas.getContext('2d');
    const imgData = ctx.getImageData(0, 0, matRGBA.cols, matRGBA.rows);
    for (let i = 0; i < matDataRaw.length; i += 1) {
      imgData.data[i] = matDataRaw[i];
    }
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
const dst0 = src.gaussianBlur({
  ksize: new cv.Size(5, 5),
  sigmaX: 1.2
});
// or pass optional parameters
const dst1 = src.gaussianBlur({
  ksize: new cv.Size(5, 5),
  sigmaX: 1.2,
  borderType: cv.cvTypes.borderTypes.BORDER_CONSTANT
});
```

For more documentation refer to examples or have a look into the tests for method invocation.