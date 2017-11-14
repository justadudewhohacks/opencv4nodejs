---
layout: default
---

###  BackgroundSubtractorKNN

####  Accessors
``` ruby
BackgroundSubtractorKNN
{
  history: Uint,
  dist2Threshold: Number,
  detectShadows: Boolean
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
BackgroundSubtractorKNN : new BackgroundSubtractorKNN(Uint history = 500, Number varThreshold = 400, Boolean detectShadows = true)
```

####  Methods

<a name="apply"></a>

#####  apply
``` ruby
Mat : bgsubtractor.apply(Mat frame, Number learningRate = -1)
```