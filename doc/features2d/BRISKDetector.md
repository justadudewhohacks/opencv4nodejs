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