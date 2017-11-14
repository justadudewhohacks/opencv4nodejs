---
layout: default
---

###  OCRHMMDecoder

<a name="constructors"></a>

####  Constructors
``` ruby
OCRHMMDecoder : new OCRHMMDecoder(OCRHMMClassifier classifier, String vocabulary, Mat transitionPropabilitiesTable, Mat emissionPropabilitiesTable, Int mode = OCR_DECODER_VITERBI)
```

####  Methods

<a name="run"></a>

#####  run
``` ruby
String : decoder.run(Mat img, Mat mask = noArray(), componentLevel = 0)
```

<a name="runAsync"></a>

#####  runAsync
``` ruby
decoder.runAsync(Mat img, callback(Error err, String outputText))
decoder.runAsync(Mat img, ...opts, callback(Error err, String outputText))
```

<a name="runWithInfo"></a>

#####  runWithInfo
``` ruby
{ outputText: String, rects: [Rect], words: [String], confidences: [Number] } : decoder.runWithInfo(Mat img, Mat mask = noArray(), componentLevel = 0)
```

<a name="runWithInfoAsync"></a>

#####  runWithInfoAsync
``` ruby
decoder.runWithInfoAsync(Mat img, callback(Error err, { outputText: String, rects: [Rect], words: [String], confidences: [Number] } result))
decoder.runWithInfoAsync(Mat img, ...opts, callback(Error err, { outputText: String, rects: [Rect], words: [String], confidences: [Number] } result))
```
