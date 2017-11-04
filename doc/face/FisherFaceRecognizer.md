# FisherFaceRecognizer

<a name="constructors"></a>

## Constructors
``` javascript
FisherFaceRecognizer : new FisherFaceRecognizer({
  num_components: Int = 0,
  threshold: Number = DBL_MAX
})
```

## Methods

<a name="train"></a>

### train
``` javascript
recognizer.train([Mat] trainImages, [Int] labels)
```

<a name="trainAsync"></a>

### trainAsync
``` javascript
recognizer.trainAsync([Mat] trainImages, [Int] labels, callback(Error err))
```

<a name="predict"></a>

### predict
``` javascript
{ label: Int, confidence: Number } : recognizer.predict(Mat img)
```

<a name="predictAsync"></a>

### predictAsync
``` javascript
recognizer.predictAsync(Mat img, callback(Error err, { label: Int, confidence: Number } result))
```

<a name="save"></a>

### save
``` javascript
recognizer.save(String file)
```

<a name="load"></a>

### load
``` javascript
recognizer.load(String file)
```