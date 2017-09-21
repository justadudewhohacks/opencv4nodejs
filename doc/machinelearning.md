# machinelearning

<a name="ParamGrid"></a>

# ParamGrid

## Accessors
``` javascript
ParamGrid {
  minVal: Number, 
  maxVal: Number, 
  logStep: Number
}
```

<a name="ParamGrid.constructors"></a>

## Constructors
``` javascript
ParamGrid : new ParamGrid(Uint paramId)
ParamGrid : new ParamGrid(Number minVal, Number maxVal, Number logStep)
```


<a name="TrainData"></a>

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

<a name="TrainData.constructors"></a>

## Constructors
``` javascript
TrainData : new TrainData(Mat samples, Uint layout, Mat responses, [Int] varIdx = [], [Int] sampleIdx = [], [Number] sampleWeights = [], [Uchar] varType = [])
```


<a name="SVM"></a>

# SVM

## Accessors
``` javascript
SVM {
  c: Number,
  coef0: Number,
  degree: Number,
  gamma: Number,
  nu: Number,
  p: Number,
  kernelType: Uint,
  classWeights: Mat,
  varCount: Uint,
  isTrained: Boolean
}
```

<a name="SVM.constructors"></a>

## Constructors
``` javascript
SVM : new SVM({
  c: Number = 0,
  coef0: Number = 0,
  degree: Number = 0,
  gamma: Number = 0,
  nu: Number = 0,
  p: Number = 0,
  kernelType: Uint = 0,
  classWeights: Mat = Mat()
})
```
## Methods

<a name="SVM.setParams"></a>

### setParams
``` javascript
setParams({
  c: Number = this.c,
  coef0: Number = this.coef0,
  degree: Number = this.degree,
  gamma: Number = this.gamma,
  nu: Number = this.nu,
  p: Number = this.p,
  kernelType: Uint = this.kernelType,
  classWeights: Mat = this.classWeights
})
```

<a name="SVM.train"></a>

### train
``` javascript
Boolean : train(TrainData trainData, Uint flags = 0)
Boolean : train(Mat samples, Uint layout, Mat responses)
```

<a name="SVM.trainAuto"></a>

### trainAuto
``` javascript
Mat : trainAuto(TrainData trainData, Uint kFold = 10, ParamGrid cGrid = ParamGrid(SVM.C), ParamGrid gammaGrid = ParamGrid(SVM.GAMMA), ParamGrid pGrid = ParamGrid(SVM.P), ParamGrid nuGrid = ParamGrid(SVM.NU), ParamGrid coeffGrid = ParamGrid(SVM.COEF), ParamGrid degreeGrid = ParamGrid(SVM.DEGREE), Boolean balanced = false)
```

<a name="SVM.predict"></a>

### predict
``` javascript
Uint : predict([Number] sample, Uint flags = 0)
[Uint] : predict(Mat samples, Uint flags = 0)
```

<a name="SVM.save"></a>

### save
``` javascript
save(String file)
```

<a name="SVM.load"></a>

### load
``` javascript
load(String file)
```

<a name="SVM.getSupportVectors"></a>

### getSupportVectors
``` javascript
Mat : getSupportVectors()
```

<a name="SVM.calcError"></a>

### calcError
``` javascript
{ error: Number, responses: Mat } : calcError(TrainData trainData, Boolean test)
```