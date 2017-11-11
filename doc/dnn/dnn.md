# dnn (v3.3+)

<a name="readNetFromTensorflow"></a>

### readNetFromTensorflow
``` javascript
Net : readNetFromTensorflow(String modelPath)
```

<a name="readNetFromTensorflowAsync"></a>

### readNetFromTensorflowAsync
``` javascript
readNetFromTensorflowAsync(String modelPath, callback(Error err, Net net))
```

<a name="blobFromImage"></a>

### blobFromImage
``` javascript
Mat : blobFromImage(Mat image, Number scaleFactor = 1.0, Size size = Size(), Vec3 mean = Vec3(), Boolean swapRB = true)
```

<a name="blobFromImageAsync"></a>

### blobFromImageAsync
``` javascript
blobFromImageAsync(Mat image, callback(Error err, Mat blob))
blobFromImageAsync(Mat image, ...opts, callback(Error err, Mat blob))
blobFromImageAsync(Mat image, { opts }, callback(Error err, Mat blob))
```

<a name="blobFromImages"></a>

### blobFromImages
``` javascript
Mat : blobFromImages([Mat] image, Number scaleFactor = 1.0, Size size = Size(), Vec3 mean = Vec3(), Boolean swapRB = true)
```

<a name="blobFromImagesAsync"></a>

### blobFromImagesAsync
``` javascript
blobFromImagesAsync([Mat] images, callback(Error err, Mat blob))
blobFromImagesAsync([Mat] images, ...opts, callback(Error err, Mat blob))
blobFromImagesAsync([Mat] images, { opts }, callback(Error err, Mat blob))
```
