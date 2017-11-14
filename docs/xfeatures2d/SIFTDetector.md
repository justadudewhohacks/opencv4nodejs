---
layout: default
---

###  SIFTDetector

####  Accessors
``` ruby
SIFTDetector {
  nfeatures: Int,
  nOctaveLayers: Int,
  contrastThreshold: Number,
  edgeThreshold: Number,
  sigma: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
SIFTDetector : new SIFTDetector(Int nfeatures = 0, Int nOctaveLayers = 3,  Number contrastThreshold = 0.04, Number edgeThreshold = 10, Number sigma = 1.6)
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