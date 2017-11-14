---
layout: default
---

###  SimpleBlobDetector

<a name="constructors"></a>

####  Constructors
``` ruby
SimpleBlobDetector : new SimpleBlobDetector(SimpleBlobDetectorParams params)
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