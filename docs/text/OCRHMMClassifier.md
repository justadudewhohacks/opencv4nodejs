---
layout: default
---

###  OCRHMMClassifier

<a name="constructors"></a>

####  Constructors
``` ruby
OCRHMMClassifier : new OCRHMMClassifier(OCRHMMClassifier classifier, String vocabulary, Mat transitionPropabilitiesTable, Mat emissionPropabilitiesTable, Int mode = OCR_DECODER_VITERBI)
```

####  Methods

<a name="eval"></a>

#####  eval
``` ruby
{ classes: [Int], confidences: [Number] } : classifier.eval(Mat img)
```

<a name="evalAsync"></a>

#####  evalAsync
``` ruby
classifier.evalAsync(Mat img, callback(Error err, { classes: [Int], confidences: [Number] } result))
```