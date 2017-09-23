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

<a name="detectMultiScaleWithRejectLevels"></a>

### detectMultiScaleWithRejectLevels
``` javascript
{ objects: [Rect], rejectLevels: [Int], levelWeigths: [Number] } : cc.detectMultiScaleWithRejectLevels(Mat img, Number scaleFactor = 1.1, Int minNeighbors = 3, Uint flags = 0, Size minSize = Size(), Size maxSize = Size())
```