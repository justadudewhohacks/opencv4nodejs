# MSERDetector

## Accessors
``` javascript
MSERDetector {
  delta: Int,
  minArea: Int,
  maxArea: Int,
  maxEvolution: Int,
  edgeBlurSize: Int,
  maxVariation: Number,
  minDiversity: Number,
  areaThreshold: Number,
  minMargin: Number
}
```

<a name="constructors"></a>

## Constructors
``` javascript
MSERDetector : new MSERDetector(Int delta = 5, Int minArea = 60, Int maxArea = 14400, Number maxVariation = 0.25, Number minDiversity = 0.2, Int maxEvolution = 200, Number areaThreshold = 1.01, Number minMargin = 0.003, Int edgeBlurSize = 5)
```
## Methods

<a name="detect"></a>

### detect
``` javascript
[KeyPoint] : detector.detect(Mat image)
```

<a name="detectAsync"></a>

### detectAsync
``` javascript
detector.detectAsync(Mat image, callback(Error err, [KeyPoint] kps))
```
