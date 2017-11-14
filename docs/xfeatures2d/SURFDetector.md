---
layout: default
---

###  SURFDetector

####  Accessors
``` ruby
SURFDetector {
  nOctaves: Int,
  nOctaveLayers: Int,
  hessianThreshold: Number,
  extended: Boolean,
  upright: Boolean
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
SURFDetector : new SURFDetector(Number hessianThreshold = 100, Int nOctaves = 4, Int nOctaveLayers = 3, Boolean extended = false, Boolean upright = false)
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