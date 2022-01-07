# build tests

## windows build Test

| openCV   |node v16 + VS2017 + VS2019|
|----------|------|
| V 3.4.6  | Pass |
| V 3.4.7  | Pass |
| V 3.4.8  | Pass |
| V 3.4.9  | Pass |
| V 3.4.10 | Pass |
| V 3.4.11 | Fail |
| V 3.4.12 | Fail |
| V 3.4.13 | Fail |
| V 3.4.14 | Fail |
| V 3.4.15 | Fail |
| V 3.4.16 | Fail |
| V 4.5.2  | Pass |
| V 4.5.3  | Pass |
| V 4.5.4  | Pass |
| V 4.5.5  | Pass |

## examples

| name               | status | desc                                 |
|-------------------|--------|---------------------------------------|
|applyColorMap      | Pass   | apply applyColorMap an an photo       |
|asyncMatchFeatures | Pass   | detectAndComputeAsync and match 2 img |
|dnnDarknetYOLORealTimeObjectDetection| Pass| apply [YOLO object detection](https://pjreddie.com/darknet/yolo/) to webcam stream |
|dnnSSDCoco         | Pass  |  apply COCO-SSD model to an image |
|dnnTensorflowInception| pass | apply inception model to images |
|dnnTensorflowObjectDetection| Fail | |
|EASTTextDetection  | Pass | text detection in photo using [EAST](https://github.com/argman/EAST) |
|facemark           | Fail | |
|faceRecognition0   | Pass | face recognition using CascadeClassifier + {Eigen,Fisher,LBPH}FaceRecognizer |
|faceRecognition1   | Pass | face recognition using CascadeClassifier + detectMultiScale + LBPHFaceRecognizer |
|getStructureSimilarity | Pass | similarity computaion |
|guidedFilter           | Pass | guidedFilter |
|handGestureRecognition0| Buggy | hand detection + contour |
|machineLearningOCR | Pass | OCR |
|makeDataSetOCR     | Pass | Train OCR model |
|matchFeatures      | Pass | Feature Matching |
|ocrHMMCharacters   | Pass | OCRHMMClassifier on chars |
|ocrHMMWords        | Pass | OCRHMMClassifier on word |
|plotHist           | Pass | plot Histograme from image |
|simpleTracking0    | Pass | Object Tracking |
|simpleTracking1    | Pass | Background supression in video (with cars) frames by frames |
|templateMatching   | Pass | Where is waldo |
