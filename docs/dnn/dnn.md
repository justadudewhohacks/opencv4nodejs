---
layout: default
---

###  dnn (v3.3+)

<a name="readNetFromTensorflow"></a>

#####  readNetFromTensorflow
``` ruby
Net : readNetFromTensorflow(String modelPath)
```

<a name="readNetFromTensorflowAsync"></a>

#####  readNetFromTensorflowAsync
``` ruby
readNetFromTensorflowAsync(String modelPath, callback(Error err, Net net))
```

<a name="readNetFromCaffe"></a>

#####  readNetFromCaffe
``` ruby
Net : readNetFromCaffe(String prototxt, String modelPath = '')
```

<a name="readNetFromCaffeAsync"></a>

#####  readNetFromCaffeAsync
``` ruby
readNetFromCaffeAsync(String prototxt, callback(Error err, Net net))
readNetFromCaffeAsync(String prototxt, String modelPath, callback(Error err, Net net))
```

<a name="blobFromImage"></a>

#####  blobFromImage
``` ruby
Mat : blobFromImage(Mat image, Number scaleFactor = 1.0, Size size = Size(), Vec3 mean = Vec3(), Boolean swapRB = true)
```

<a name="blobFromImageAsync"></a>

#####  blobFromImageAsync
``` ruby
blobFromImageAsync(Mat image, callback(Error err, Mat blob))
blobFromImageAsync(Mat image, ...opts, callback(Error err, Mat blob))
blobFromImageAsync(Mat image, { opts }, callback(Error err, Mat blob))
```

<a name="blobFromImages"></a>

#####  blobFromImages
``` ruby
Mat : blobFromImages([Mat] image, Number scaleFactor = 1.0, Size size = Size(), Vec3 mean = Vec3(), Boolean swapRB = true)
```

<a name="blobFromImagesAsync"></a>

#####  blobFromImagesAsync
``` ruby
blobFromImagesAsync([Mat] images, callback(Error err, Mat blob))
blobFromImagesAsync([Mat] images, ...opts, callback(Error err, Mat blob))
blobFromImagesAsync([Mat] images, { opts }, callback(Error err, Mat blob))
```
