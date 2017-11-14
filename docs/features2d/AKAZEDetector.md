---
layout: default
---

###  AKAZEDetector

####  Accessors
``` ruby
AKAZEDetector {
  descriptorType: Int,
  descriptorSize: Int,
  descriptorChannels: Int,
  nOctaves: Int,
  nOctaveLayers: Int,
  diffusivity: Int,
  threshold: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
AKAZEDetector : new AKAZEDetector(Int descriptorType = AKAZE.DESCRIPTOR_MLDB, Int descriptorSize = 0, Int descriptorChannels = 3, Number threshold = 0.01, Int nOctaves = 4, Int nOctaveLayers = 4, Int diffusivity = KAZE.DIFF_PM_G2)
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