# video

<a name="BackgroundSubtractorMOG2"></a>

# BackgroundSubtractorMOG2

## Accessors
``` javascript
BackgroundSubtractorMOG2 {
  history: Uint,
  varThreshold: Number,
  detectShadows: Boolean
}
```

<a name="BackgroundSubtractorMOG2.constructors"></a>

## Constructors
``` javascript
BackgroundSubtractorMOG2 : new BackgroundSubtractorMOG2(Uint history = 500, Number varThreshold = 16, Boolean detectShadows = true)
```
## Methods

<a name="BackgroundSubtractorMOG2.apply"></a>

### apply
``` javascript
Mat : apply(Mat frame, Number learningRate = -1)
```

<a name="BackgroundSubtractorKNN"></a>

# BackgroundSubtractorKNN

## Accessors
``` javascript
BackgroundSubtractorKNN {
  history: Uint,
  dist2Threshold: Number,
  detectShadows: Boolean
}
```

<a name="BackgroundSubtractorKNN.constructors"></a>

## Constructors
``` javascript
BackgroundSubtractorKNN : new BackgroundSubtractorKNN(Uint history = 500, Number varThreshold = 400, Boolean detectShadows = true)
```
## Methods

<a name="BackgroundSubtractorKNN.apply"></a>

### apply
``` javascript
Mat : apply(Mat frame, Number learningRate = -1)
```