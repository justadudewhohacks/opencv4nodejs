# BRISKDetector

## Accessors
``` javascript
BRISKDetector {
  thresh: Int,
  octaves: Int,
  patternScale: Number
}
```

<a name="constructors"></a>

## Constructors
``` javascript
BRISKDetector : new BRISKDetector(Int thresh = 30, Int octaves = 3, Number patternScale = 1.0)
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