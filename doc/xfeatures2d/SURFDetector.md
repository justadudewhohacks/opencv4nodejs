# SURFDetector

## Accessors
``` javascript
SURFDetector {
  nOctaves: Int,
  nOctaveLayers: Int,
  hessianThreshold: Number,
  extended: Boolean,
  upright: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
SURFDetector : new SURFDetector(Number hessianThreshold = 100, Int nOctaves = 4, Int nOctaveLayers = 3, Boolean extended = false, Boolean upright = false)
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