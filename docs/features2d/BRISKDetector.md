---
layout: default
---

###  BRISKDetector

####  Accessors
``` ruby
BRISKDetector {
  thresh: Int,
  octaves: Int,
  patternScale: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
BRISKDetector : new BRISKDetector(Int thresh = 30, Int octaves = 3, Number patternScale = 1.0)
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