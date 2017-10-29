# OCRHMMClassifier

<a name="constructors"></a>

## Constructors
``` javascript
OCRHMMClassifier : new OCRHMMClassifier(OCRHMMClassifier classifier, String vocabulary, Mat transitionPropabilitiesTable, Mat emissionPropabilitiesTable, Int mode = OCR_DECODER_VITERBI)
```

## Methods

<a name="eval"></a>

### eval
``` javascript
{ classes: [Int], confidences: [Number] } : classifier.eval(Mat img)
```

<a name="evalAsync"></a>

### evalAsync
``` javascript
classifier.evalAsync(Mat img, callback(Error err, { classes: [Int], confidences: [Number] } result))
```