---
layout: default
---

###  KAZEDetector

####  Accessors
``` ruby
KAZEDetector {
  extended: Boolean,
  upright: Boolean,
  nOctaves: Int,
  nOctaveLayers: Int,
  diffusivity: Int,
  threshold: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
KAZEDetector : new KAZEDetector(Boolean extended = false, Boolean upright = false, Number threshold = 0.01, Int nOctaves = 4, Int nOctaveLayers = 4, Int diffusivity = KAZE.DIFF_PM_G2)
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