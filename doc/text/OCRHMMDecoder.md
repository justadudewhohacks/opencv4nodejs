# OCRHMMDecoder

<a name="constructors"></a>

## Constructors
``` javascript
OCRHMMDecoder : new OCRHMMDecoder(OCRHMMClassifier classifier, String vocabulary, Mat transitionPropabilitiesTable, Mat emissionPropabilitiesTable, Int mode = OCR_DECODER_VITERBI)
```

## Methods

<a name="run"></a>

### run
``` javascript
String : decoder.run(Mat img, Mat mask = noArray(), componentLevel = 0)
```

<a name="runAsync"></a>

### runAsync
``` javascript
decoder.runAsync(Mat img, callback(Error err, String outputText))
decoder.runAsync(Mat img, ...opts, callback(Error err, String outputText))
```

<a name="runWithInfo"></a>

### runWithInfo
``` javascript
{ outputText: String, rects: [Rect], words: [String], confidences: [Number] } : decoder.runWithInfo(Mat img, Mat mask = noArray(), componentLevel = 0)
```

<a name="runWithInfoAsync"></a>

### runWithInfoAsync
``` javascript
decoder.runWithInfoAsync(Mat img, callback(Error err, { outputText: String, rects: [Rect], words: [String], confidences: [Number] } result))
decoder.runWithInfoAsync(Mat img, ...opts, callback(Error err, { outputText: String, rects: [Rect], words: [String], confidences: [Number] } result))
```
