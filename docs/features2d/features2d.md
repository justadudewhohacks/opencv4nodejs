---
layout: default
---

###  features2d

<a name="matchFlannBased"></a>

#####  matchFlannBased
``` ruby
[DescriptorMatch] : matchFlannBased(Mat descriptors1, Mat descriptors2)
```

<a name="matchFlannBasedAsync"></a>

#####  matchFlannBasedAsync
``` ruby
matchFlannBasedAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForce"></a>

#####  matchBruteForce
``` ruby
[DescriptorMatch] : matchBruteForce(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceAsync"></a>

#####  matchBruteForceAsync
``` ruby
matchBruteForceAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceL1"></a>

#####  matchBruteForceL1
``` ruby
[DescriptorMatch] : matchBruteForceL1(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceL1Async"></a>

#####  matchBruteForceL1Async
``` ruby
matchBruteForceL1Async(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceHamming"></a>

#####  matchBruteForceHamming
``` ruby
[DescriptorMatch] : matchBruteForceHamming(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceHammingAsync"></a>

#####  matchBruteForceHammingAsync
``` ruby
matchBruteForceHammingAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceHammingLut"></a>

#####  matchBruteForceHammingLut (v3.2, v3.3)
``` ruby
[DescriptorMatch] : matchBruteForceHammingLut(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceHammingLutAsync"></a>

#####  matchBruteForceHammingLutAsync
``` ruby
matchBruteForceHammingLutAsync(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="matchBruteForceSL2"></a>

#####  matchBruteForceSL2 (v3.2, v3.3)
``` ruby
[DescriptorMatch] : matchBruteForceSL2(Mat descriptors1, Mat descriptors2)
```

<a name="matchBruteForceSL2Async"></a>

#####  matchBruteForceSL2Async
``` ruby
matchBruteForceSL2Async(Mat descriptors1, Mat descriptors2, callback(Error err, [DescriptorMatch] matches))
```

<a name="drawKeyPoints"></a>

#####  drawKeyPoints
``` ruby
Mat : drawKeyPoints(Mat img, [KeyPoint] keyPoints)
```

<a name="drawMatches"></a>

#####  drawMatches
``` ruby
Mat : drawMatches(Mat img1, Mat img2, [KeyPoint] keyPoints1, [KeyPoint] keyPoints2, [DescriptorMatch] matches)
```