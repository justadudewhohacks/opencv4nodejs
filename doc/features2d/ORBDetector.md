# ORBDetector

## Accessors
``` javascript
ORBDetector {
  nfeatures: Int,
  nlevels: Int,
  edgeThreshold: Int,
  firstLevel: Int,
  WTA_K: Int,
  scoreType: Int,
  patchSize: Int,
  fastThreshold: Int,
  scaleFactor: Number
}
```

<a name="constructors"></a>

## Constructors
``` javascript
ORBDetector : new ORBDetector(Int nfeatures = 500, Number scaleFactor = 1.2, Int nlevels = 8, Int edgeThreshold = 31, Int firstLevel = 0, Int WTA_K = 2, Int scoreType = ORB.HARRIS_SCORE, Int patchSize = 31, Int fastThreshold = 20)
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

<a name="compute"></a>

### compute
``` javascript
Mat : detector.compute(Mat image, [KeyPoint] keypoints)
```

<a name="computeAsync"></a>

### computeAsync
``` javascript
detector.computeAsync(Mat image, [KeyPoint] keypoints, callback(Error err, Mat descriptors))
```