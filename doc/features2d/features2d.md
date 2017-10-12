# features2d

<a name="matchFlannBased"></a>

### matchFlannBased
``` javascript
[DescriptorMatch] : matchFlannBased(Mat descriptors1, Mat descriptors2)
```

<a name="matchFlannBasedAsync"></a>

### matchFlannBasedAsync
``` javascript
matchFlannBasedAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForce"></a>

### matchBruteForce
``` javascript
[DescriptorMatch] : matchBruteForce(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceAsync"></a>

### matchBruteForceAsync
``` javascript
matchBruteForceAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceL1"></a>

### matchBruteForceL1
``` javascript
[DescriptorMatch] : matchBruteForceL1(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceL1Async"></a>

### matchBruteForceL1Async
``` javascript
matchBruteForceL1Async(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceHamming"></a>

### matchBruteForceHamming
``` javascript
[DescriptorMatch] : matchBruteForceHamming(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceHammingAsync"></a>

### matchBruteForceHammingAsync
``` javascript
matchBruteForceHammingAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceHammingLut"></a>

### matchBruteForceHammingLut (v3.2, v3.3)
``` javascript
[DescriptorMatch] : matchBruteForceHammingLut(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceHammingLutAsync"></a>

### matchBruteForceHammingLutAsync
``` javascript
matchBruteForceHammingLutAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceSL2"></a>

### matchBruteForceSL2 (v3.2, v3.3)
``` javascript
[DescriptorMatch] : matchBruteForceSL2(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceSL2Async"></a>

### matchBruteForceSL2Async
``` javascript
matchBruteForceSL2Async(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="drawKeyPoints"></a>

### drawKeyPoints
``` javascript
Mat : drawKeyPoints(Mat img, [KeyPoint] keyPoints)
```

<a name="drawMatches"></a>

### drawMatches
``` javascript
Mat : drawMatches(Mat img1, Mat img2, [KeyPoint] keyPoints1, [KeyPoint] keyPoints2, [DescriptorMatch] matches)
```