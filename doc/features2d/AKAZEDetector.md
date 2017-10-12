# AKAZEDetector

## Accessors
``` javascript
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

## Constructors
``` javascript
AKAZEDetector : new AKAZEDetector(Int descriptorType = AKAZE.DESCRIPTOR_MLDB, Int descriptorSize = 0, Int descriptorChannels = 3, Number threshold = 0.01, Int nOctaves = 4, Int nOctaveLayers = 4, Int diffusivity = KAZE.DIFF_PM_G2)
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