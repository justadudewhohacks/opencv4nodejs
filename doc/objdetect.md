# objdetect

<a name="CascadeClassifier"></a>

# CascadeClassifier

<a name="CascadeClassifier.constructors"></a>

## Constructors
``` javascript
CascadeClassifier : new CascadeClassifier(String xmlFilePath)
```

## Methods

<a name="CascadeClassifier.detectMultiScale"></a>

### detectMultiScale
``` javascript
[Rect] : detectMultiScale(Mat img, [Rect] objects, [Int] rejectLevels, [Number] levelWeigths, Number scaleFactor = 1.1, Int minNeighbors = 3, Uint flags = 0, Size minSize = Size(), Size maxSize = Size())
[Rect] : detectMultiScale(Mat img, [Rect] objects, [Int] numDetections, Number scaleFactor = 1.1, Int minNeighbors = 3, Uint flags = 0, Size minSize = Size(), Size maxSize = Size())
```

<a name="HOGDescriptor"></a>

# HOGDescriptor

## Accessors
``` javascript
HOGDescriptor {
  winSize: Size, 
  blockSize: Size, 
  blockStride: Size, 
  cellSize: Size, 
  nbins: Uint, 
  derivAperture: Int,
  histogramNormType: Uint,
  nlevels: Int, 
  winSigma: Number, 
  L2HysThreshold: Number, 
  gammaCorrection: Boolean, 
  signedGradient: Boolean
}
```

<a name="HOGDescriptor.constructors"></a>

## Constructors
``` javascript
HOGDescriptor : new HOGDescriptor(Size winSize = Size(64, 128), Size blockSize = Size(16, 16), Size blockStride = Size(8, 8), Size cellSize = Size(8, 8), Uint nbins = 9, Int derivAperture = 1, Uint histogramNormType = HOGDescriptor.L2Hys, Int nlevels = HOGDescriptor.DEFAULT_NLEVELS, Number winSigma = -1, Number L2HysThreshold = 0.2, Boolean gammaCorrection = false, Boolean signedGradient = false)
```

## Methods

<a name="HOGDescriptor.compute"></a>

### compute
``` javascript
[Number] : compute(Mat img, Size winStride = Size(), Size padding = Size(), [Point2] locations = [])
```