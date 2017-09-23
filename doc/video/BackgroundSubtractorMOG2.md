# BackgroundSubtractorMOG2

## Accessors
``` javascript
BackgroundSubtractorMOG2 {
  history: Uint,
  varThreshold: Number,
  detectShadows: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
BackgroundSubtractorMOG2 : new BackgroundSubtractorMOG2(Uint history = 500, Number varThreshold = 16, Boolean detectShadows = true)
```
## Methods

<a name="apply"></a>

### apply
``` javascript
Mat : bgsubtractor.apply(Mat frame, Number learningRate = -1)
```