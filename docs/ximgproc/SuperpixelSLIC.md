---
layout: default
---

###  SuperpixelSLIC

####  Accessors
``` ruby
{
	img: Mat,
  labels: Mat,
  labelContourMask: Mat,
  algorithm: Int,
  regionSize: Int,
  ruler: Number,
  numCalculatedSuperpixels: Int
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
SuperpixelSLIC : new SuperpixelSLIC(Mat img, Int algorithm = cv.SLICO, Int regionSize = 10, Number ruler = 10)
```

####  Methods

<a name="iterate"></a>

#####  iterate
``` ruby
slic.iterate(Uint iterations = 10)
```