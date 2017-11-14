---
layout: default
---

###  SuperpixelLSC

####  Accessors
``` ruby
{
	img: Mat,
  labels: Mat,
  labelContourMask: Mat,
  regionSize: Int,
  ratio: Number,
  numCalculatedSuperpixels: Int
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
SuperpixelLSC : new SuperpixelLSC(Mat img, Int regionSize = 10, Number ratio = 10)
```

####  Methods

<a name="iterate"></a>

#####  iterate
``` ruby
lsc.iterate(Uint iterations = 10)
```