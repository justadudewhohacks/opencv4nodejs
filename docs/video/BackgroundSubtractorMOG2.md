---
layout: default
---

###  BackgroundSubtractorMOG2

####  Accessors
``` ruby
BackgroundSubtractorMOG2
{
  history: Uint,
  varThreshold: Number,
  detectShadows: Boolean
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
BackgroundSubtractorMOG2 : new BackgroundSubtractorMOG2(Uint history = 500, Number varThreshold = 16, Boolean detectShadows = true)
```

####  Methods

<a name="apply"></a>

#####  apply
``` ruby
Mat : bgsubtractor.apply(Mat frame, Number learningRate = -1)
```