# GFTTDetector

## Accessors
``` javascript
GFTTDetector {
  maxCorners: Int,
  blockSize: Int,
  qualityLevel: Number,
  minDistance: Number,
  k: Number,
  useHarrisDetector: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
GFTTDetector : new GFTTDetector(Int maxCorners = 1000, Number qualityLevel = 0.01, Number minDistance = 1.0, Int blockSize = 3, Boolean useHarrisDetector = false, Number k = 0.04)
```
## Methods

<a name="detect"></a>

### apply
``` javascript
[KeyPoint] : detector.detect(Mat image)
```