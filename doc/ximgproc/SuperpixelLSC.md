# SuperpixelLSC

## Accessors
``` javascript
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

## Constructors
``` javascript
SuperpixelLSC : new SuperpixelLSC(Mat img, Int regionSize = 10, Number ratio = 10)
```

## Methods

<a name="iterate"></a>

### iterate
``` javascript
lsc.iterate(Uint iterations = 10)
```