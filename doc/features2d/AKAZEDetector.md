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

### apply
``` javascript
[KeyPoint] : detector.detect(Mat image)
```

<a name="compute"></a>

### apply
``` javascript
Mat : detector.compute(Mat image, [KeyPoint] keypoints)
```