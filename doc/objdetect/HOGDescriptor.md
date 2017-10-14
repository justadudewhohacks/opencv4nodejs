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

<a name="constructors"></a>

## Constructors
``` javascript
HOGDescriptor : new HOGDescriptor(Size winSize = Size(64, 128), Size blockSize = Size(16, 16), Size blockStride = Size(8, 8), Size cellSize = Size(8, 8), Uint nbins = 9, Int derivAperture = 1, Number winSigma = -1, Uint histogramNormType = L2Hys, Number L2HysThreshold = 0.2, Boolean gammaCorrection = false, Int nlevels = HOGDescriptor.DEFAULT_NLEVELS, Boolean signedGradient = false)
```

## Methods

<a name="compute"></a>

### compute
``` javascript
[Number] : hog.compute(Mat img, Size winStride = Size(), Size padding = Size(), [Point2] locations = [])
```

<a name="computeAsync"></a>

### computeAsync
``` javascript
hog.computeAsync(Mat img, callback(Error err, [Number] descriptor))
hog.computeAsync(Mat img, ...opts, callback(Error err, [Number] descriptor))
hog.computeAsync(Mat img, { opts }, callback(Error err, [Number] descriptor))
```
