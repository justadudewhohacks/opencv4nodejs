# SuperpixelSLIC

## Accessors
``` javascript
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

## Constructors
``` javascript
SuperpixelSLIC : new SuperpixelSLIC(Mat img, Int algorithm = cv.SLICO, Int regionSize = 10, Number ruler = 10)
```

## Methods

<a name="iterate"></a>

### iterate
``` javascript
slic.iterate(Uint iterations = 10)
```