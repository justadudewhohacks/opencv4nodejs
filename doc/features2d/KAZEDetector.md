# KAZEDetector

## Accessors
``` javascript
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

## Constructors
``` javascript
KAZEDetector : new KAZEDetector(Boolean extended = false, Boolean upright = false, Number threshold = 0.01, Int nOctaves = 4, Int nOctaveLayers = 4, Int diffusivity = KAZE.DIFF_PM_G2)
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