# TrainData

## Accessors
``` javascript
TrainData {
 samples: Mat,
 layout: Uint,
 responses: Mat,
 varIdx = [Int],
 sampleWeights = [Number],
 varType: [Uchar]
}
```

<a name="constructors"></a>

## Constructors
``` javascript
TrainData : new TrainData(Mat samples, Uint layout, Mat responses, [Int] varIdx = [], [Int] sampleIdx = [], [Number] sampleWeights = [], [Uchar] varType = [])
```