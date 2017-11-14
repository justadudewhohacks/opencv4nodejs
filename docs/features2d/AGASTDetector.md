---
layout: default
---

###  AGASTDetector

####  Accessors
``` ruby
AGASTDetector {
  threshold: Int,
  type: Int,
  nonmaxSuppression: Boolean
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
AGASTDetector : new AGASTDetector(Int threshold = 10, Boolean nonmaxSuppression = true, Int type = AGAST.OAST_9_16)
```
####  Methods

<a name="detect"></a>

#####  detect
``` ruby
[KeyPoint] : detector.detect(Mat image)
```

<a name="detectAsync"></a>

#####  detectAsync
``` ruby
detector.detectAsync(Mat image, callback(Error err, [KeyPoint] kps))
```