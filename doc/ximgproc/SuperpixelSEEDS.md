# SuperpixelSEEDS

## Accessors
``` javascript
{
	img: Mat,
  labels: Mat,
  labelContourMask: Mat,
  numSuperpixels: Int,
  numLevels: Int,
  prior: Int,
  histogramBins: Int,
  numCalculatedSuperpixels: Int,
  doubleStep: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
SuperpixelSEEDS : new SuperpixelSEEDS(Mat img, Int numSuperpixels, Int numLevels, Int prior = 2, Int histogramBins = 5, Boolean doubleStep = false)
```

## Methods

<a name="iterate"></a>

### iterate
``` javascript
seeds.iterate(Uint iterations = 4)
```