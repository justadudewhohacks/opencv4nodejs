# CascadeClassifier

<a name="constructors"></a>

## Constructors
``` javascript
CascadeClassifier : new CascadeClassifier(String xmlFilePath)
```

## Methods

<a name="detectMultiScale"></a>

### detectMultiScale
``` javascript
{ objects: [Rect], numDetections: [Int] } : cc.detectMultiScale(Mat img, [Rect], Number scaleFactor = 1.1, Int minNeighbors = 3, Uint flags = 0, Size minSize = Size(), Size maxSize = Size())
```

<a name="detectMultiScaleAsync"></a>

### detectMultiScaleAsync
``` javascript
cc.detectMultiScaleAsync(Mat img, callback(Error err, { objects: [Rect], numDetections: [Int] } res))
cc.detectMultiScaleAsync(Mat img, ...opts, callback(Error err, { objects: [Rect], numDetections: [Int] } res))
cc.detectMultiScaleAsync(Mat img, { opts }, callback(Error err, { objects: [Rect], numDetections: [Int] } res))
```

<a name="detectMultiScaleWithRejectLevels"></a>

### detectMultiScaleWithRejectLevels
``` javascript
{ objects: [Rect], rejectLevels: [Int], levelWeigths: [Number] } : cc.detectMultiScaleWithRejectLevels(Mat img, Number scaleFactor = 1.1, Int minNeighbors = 3, Uint flags = 0, Size minSize = Size(), Size maxSize = Size())
```

<a name="detectMultiScaleWithRejectLevelsAsync"></a>

### detectMultiScaleWithRejectLevelsAsync
``` javascript
cc.detectMultiScaleWithRejectLevelsAsync(Mat img, callback(Error err, { objects: [Rect], rejectLevels: [Int], levelWeigths: [Number] } res))
cc.detectMultiScaleWithRejectLevelsAsync(Mat img, ...opts, callback(Error err, { objects: [Rect], rejectLevels: [Int], levelWeigths: [Number] } res))
cc.detectMultiScaleWithRejectLevelsAsync(Mat img, { opts }, callback(Error err, { objects: [Rect], rejectLevels: [Int], levelWeigths: [Number] } res))
```