---
layout: default
---

###  ORBDetector

####  Accessors
``` ruby
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

####  Constructors
``` ruby
ORBDetector : new ORBDetector(Int nfeatures = 500, Number scaleFactor = 1.2, Int nlevels = 8, Int edgeThreshold = 31, Int firstLevel = 0, Int WTA_K = 2, Int scoreType = ORB.HARRIS_SCORE, Int patchSize = 31, Int fastThreshold = 20)
```
####  Methods

<a name="detect"></a>

#####  detect
``` ruby
[KeyPoint] : detector.detect(Mat image)
```

<a name="detectAsync"></a>

#####  detectAsync
``` ruby
detector.detectAsync(Mat image, callback(Error err, [KeyPoint] kps))
```

<a name="compute"></a>

#####  compute
``` ruby
Mat : detector.compute(Mat image, [KeyPoint] keypoints)
```

<a name="computeAsync"></a>

#####  computeAsync
``` ruby
detector.computeAsync(Mat image, [KeyPoint] keypoints, callback(Error err, Mat descriptors))
```