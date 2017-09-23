# FASTDetector

## Accessors
``` javascript
FASTDetector {
  threshold: Int,
  type: Int,
  nonmaxSuppression: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
FASTDetector : new FASTDetector(Int threshold = 10, Boolean nonmaxSuppression = true, Int type = FAST.TYPE_9_16)
```
## Methods

<a name="detect"></a>

### apply
``` javascript
[KeyPoint] : detector.detect(Mat image)
```