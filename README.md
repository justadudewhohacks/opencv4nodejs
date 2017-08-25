opencv4nodejs
=============

**Brings lots of features of OpenCV 3.x to nodejs to use as a service, integrate into your electron app or to simply play around with the OpenCV API in Javascript instead of C++.**

## How to install

``` bash
$ npm install --save opencv4nodejs
```

Make sure to have OpenCV 3+ ( extra modules are optional ) installed on your System. In case you are running Windows or have OpenCV setup in a custom directory make sure to set the following environment variables:
1. OPENCV_DIR pointing to the root path containing include directory or set OPENCV_INCLUDE_DIR explicitly.
2. OPENCV_LIB_DIR pointing to the static library dir containing the OpenCV .lib or .so files.

If you are running into issues also check the requirements for node-gyp specific to your OS https://github.com/nodejs/node-gyp.

## Usage with electron

``` bash
$ npm install --save electron-rebuild
```

Add the following script to your package.json:
``` python
"electron-rebuild": "electron-rebuild -w opencv4nodejs -m ./node_modules/opencv4nodejs" ...
```

Run the script after installing the library:
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
...

// Point
const pt2 = new cv.Point(100, 100);
const pt3 = new cv.Point(100, 100, 0.5);

// Vector
const vec2 = new cv.Vec(100, 100);
const vec3 = new cv.Vec(100, 100, 0.5);
const vec4 = new cv.Vec(100, 100, 0.5, 0.5);
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