# SIFTDetector

## Accessors
``` javascript
SIFTDetector {
  nfeatures: Int,
  nOctaveLayers: Int,
  contrastThreshold: Number,
  edgeThreshold: Number,
  sigma: Number
}
```

<a name="constructors"></a>

## Constructors
``` javascript
SIFTDetector : new SIFTDetector(Int nfeatures = 0, Int nOctaveLayers = 3,  Number contrastThreshold = 0.04, Number edgeThreshold = 10, Number sigma = 1.6)
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