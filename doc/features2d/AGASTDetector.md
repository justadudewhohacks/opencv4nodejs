# AGASTDetector

## Accessors
``` javascript
AGASTDetector {
  threshold: Int,
  type: Int,
  nonmaxSuppression: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
AGASTDetector : new AGASTDetector(Int threshold = 10, Boolean nonmaxSuppression = true, Int type = AGAST.OAST_9_16)
```
## Methods

<a name="detect"></a>

### apply
``` javascript
[KeyPoint] : detector.detect(Mat image)
```