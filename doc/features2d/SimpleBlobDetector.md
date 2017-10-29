# SimpleBlobDetector

<a name="constructors"></a>

## Constructors
``` javascript
SimpleBlobDetector : new SimpleBlobDetector(SimpleBlobDetectorParams params)
```
## Methods

<a name="detect"></a>

### detect
``` javascript
[KeyPoint] : detector.detect(Mat image)
```

<a name="detectAsync"></a>

### detectAsync
``` javascript
detector.detectAsync(Mat image, callback(Error err, [KeyPoint] kps))
```

<a name="compute"></a>

### compute
``` javascript
Mat : detector.compute(Mat image, [KeyPoint] keypoints)
```

<a name="computeAsync"></a>

### computeAsync
``` javascript
detector.computeAsync(Mat image, [KeyPoint] keypoints, callback(Error err, Mat descriptors))
```