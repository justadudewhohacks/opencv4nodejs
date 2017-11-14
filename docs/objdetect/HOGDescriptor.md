---
layout: default
---

###  HOGDescriptor

####  Accessors
``` ruby
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

<a name="constructors"></a>

####  Constructors
``` ruby
HOGDescriptor : new HOGDescriptor(Size winSize = Size(64, 128), Size blockSize = Size(16, 16), Size blockStride = Size(8, 8), Size cellSize = Size(8, 8), Uint nbins = 9, Int derivAperture = 1, Number winSigma = -1, Uint histogramNormType = L2Hys, Number L2HysThreshold = 0.2, Boolean gammaCorrection = false, Int nlevels = HOGDescriptor.DEFAULT_NLEVELS, Boolean signedGradient = false)
```

####  Methods

<a name="getDaimlerPeopleDetector"></a>

#####  getDaimlerPeopleDetector
``` ruby
[Number] : HOGDescriptor.getDaimlerPeopleDetector()
```

<a name="getDefaultPeopleDetector"></a>

#####  getDefaultPeopleDetector
``` ruby
[Number] : HOGDescriptor.getDefaultPeopleDetector()
```

<a name="compute"></a>

#####  compute
``` ruby
[Number] : hog.compute(Mat img, Size winStride = Size(), Size padding = Size(), [Point2] locations = [])
```

<a name="computeAsync"></a>

#####  computeAsync
``` ruby
hog.computeAsync(Mat img, callback(Error err, [Number] descriptor))
hog.computeAsync(Mat img, ...opts, callback(Error err, [Number] descriptor))
hog.computeAsync(Mat img, { opts }, callback(Error err, [Number] descriptor))
```

<a name="computeGradient"></a>

#####  computeGradient
``` ruby
{ grad: Mat, angleOfs: Mat } : hog.computeGradient(Mat img, Size paddingTL = Size(), Size paddingBR = Size())
```

<a name="computeGradientAsync"></a>

#####  computeGradientAsync
``` ruby
hog.computeGradientAsync(Mat img, callback(Error err, { grad: Mat, angleOfs: Mat } result))
hog.computeGradientAsync(Mat img, ...opts, callback(Error err, { grad: Mat, angleOfs: Mat } result))
hog.computeGradientAsync(Mat img, { opts }, callback(Error err, { grad: Mat, angleOfs: Mat } result))
```

<a name="detect"></a>

#####  detect
``` ruby
{ foundLocations: [Point2], weights: [Number] } : hog.detect(Mat img, Number hitThreshold = 0.0, Size winStride = Size(), Size padding = Size(), [Point2] searchLocations = [])
```

<a name="detectAsync"></a>

#####  detectAsync
``` ruby
hog.detectAsync(Mat img, callback(Error err, { foundLocations: [Point2], weights: [Number] } result))
hog.detectAsync(Mat img, ...opts, callback(Error err, { foundLocations: [Point2], weights: [Number] } result))
hog.detectAsync(Mat img, { opts }, callback(Error err, { foundLocations: [Point2], weights: [Number] } result))
```

<a name="detectROI"></a>

#####  detectROI
``` ruby
{ foundLocations: [Point2], confidences: [Number] } : hog.detectROI(Mat img, [Point2] locations, Number hitThreshold = 0.0, Size winStride = Size(), Size padding = Size())
```

<a name="detectROIAsync"></a>

#####  detectROIAsync
``` ruby
hog.detectROIAsync(Mat img, [Point2] locations, callback(Error err, { foundLocations: [Point2], weights: [Number] } result))
hog.detectROIAsync(Mat img, [Point2] locations, ...opts, callback(Error err, { foundLocations: [Point2], confidences: [Number] } result))
hog.detectROIAsync(Mat img, [Point2] locations, { opts }, callback(Error err, { foundLocations: [Point2], confidences: [Number] } result))
```

<a name="detectMultiScale"></a>

#####  detectMultiScale
``` ruby
{ foundLocations: [Rect], foundWeights: [Number] } : hog.detectMultiScale(Mat img, Number hitThreshold = 0.0, Size winStride = Size(), Size padding = Size(), Number scale = 1.05, Number finalThreshold = 2.0, Boolean useMeanshiftGrouping = false)
```

<a name="detectMultiScaleAsync"></a>

#####  detectMultiScaleAsync
``` ruby
hog.detectMultiScaleAsync(Mat img, callback(Error err, { foundLocations: [Rect], foundWeights: [Number] } result))
hog.detectMultiScaleAsync(Mat img, ...opts, callback(Error err, { foundLocations: [Rect], foundWeights: [Number] } result))
hog.detectMultiScaleAsync(Mat img, { opts }, callback(Error err, { foundLocations: [Rect], foundWeights: [Number] } result))
```

<a name="detectMultiScaleROI"></a>

#####  detectMultiScaleROI
``` ruby
[Rect] : hog.detectMultiScaleROI(Mat img, Number hitThreshold = 0.0, Int groupThreshold = 0)
```

<a name="detectMultiScaleROIAsync"></a>

#####  detectMultiScaleROIAsync
``` ruby
hog.detectMultiScaleROIAsync(Mat img, callback(Error err, [Rect] result))
hog.detectMultiScaleROIAsync(Mat img, ...opts, callback(Error err, [Rect] result))
hog.detectMultiScaleROIAsync(Mat img, { opts }, callback(Error err, [Rect] result))
```

<a name="groupRectangles"></a>

#####  groupRectangles
``` ruby
hog.groupRectangles([Rect] rectList, [Number] weights, Int groupThreshold, Number eps)
```

<a name="groupRectanglesAsync"></a>

#####  groupRectanglesAsync
``` ruby
hog.groupRectanglesAsync([Rect] rectList, [Number] weights, Int groupThreshold, Number eps, callback(Error err))
```

<a name="checkDetectorSize"></a>

#####  checkDetectorSize
``` ruby
Boolean : hog.checkDetectorSize()
```

<a name="setSVMDetector"></a>

#####  setSVMDetector
``` ruby
hog.setSVMDetector([Number] detector)
```

<a name="save"></a>

#####  save
``` ruby
hog.save(String path)
```

<a name="load"></a>

#####  load
``` ruby
hog.load(String path)
```
