# Mat

## Accessors
``` javascript
Mat {
  rows: Number,
  cols: Number,
  type: Number,
  channels: Number,
  depth: Number,
  dims: Number,
  empty: Boolean
}
```

<a name="constructors"></a>

## Constructors
``` javascript
Mat : new Mat()
Mat : new Mat([Mat] channels)
Mat : new Mat(Uint rows, Uint cols, Uint type)
Mat : new Mat(Uint rows, Uint cols, Uint type, Number)
Mat : new Mat(Uint rows, Uint cols, Uint type,  [2 Number])
Mat : new Mat(Uint rows, Uint cols, Uint type,  [3 Number])
Mat : new Mat(Uint rows, Uint cols, Uint type,  [4 Number])
Mat : new Mat([ [Number] ] dataArray)
Mat : new Mat([ [ [2 Number] ] ] dataArray)
Mat : new Mat([ [ [3 Number] ] ] dataArray)
Mat : new Mat([ [ [4 Number] ] ] dataArray)
Mat : new Mat([Uchar] data, Uint rows, Uint cols, Uint type = CV_8U)
```

<a name="operators"></a>

## Operators
``` javascript
Mat : mat.add(Mat otherMat)
Mat : mat.sub(Mat otherMat)
Mat : mat.mul(Number s)
Mat : mat.div(Number s)

Mat : mat.hMul(Mat otherMat)
Mat : mat.hDiv(Mat otherMat)
Mat : mat.absdiff(Mat otherMat)

Mat : mat.exp()
Mat : mat.mean()
Mat : mat.sqrt()
Mat : mat.dot()

Mat : mat.and(Mat otherMat)
Mat : mat.or(Mat otherMat)
Mat : mat.bitwiseAnd(Mat otherMat)
Mat : mat.bitwiseOr(Mat otherMat)
Mat : mat.bitwiseXor(Mat otherMat)
Mat : mat.bitwiseNot()

Mat : mat.abs()
Number : mat.determinant()
Mat : mat.transpose()
```

## Methods

<a name="at"></a>

### at
``` javascript
Number : mat.at(Uint row, Uint col)
Vec2 : mat.at(Uint row, Uint col)
Vec3 : mat.at(Uint row, Uint col)
Vec4 : mat.at(Uint row, Uint col)
```

<a name="atRaw"></a>

### atRaw
``` javascript
Number : mat.atRaw(Uint row, Uint col)
[2 Number] : mat.atRaw(Uint row, Uint col)
[3 Number] : mat.atRaw(Uint row, Uint col)
[4 Number] : mat.atRaw(Uint row, Uint col)
```

<a name="set"></a>

### set
``` javascript
mat.set(Uint row, Uint col, Number)
mat.set(Uint row, Uint col, [2 Number])
mat.set(Uint row, Uint col, [3 Number])
mat.set(Uint row, Uint col, [4 Number])
mat.set(Uint row, Uint col, Vec2)
mat.set(Uint row, Uint col, Vec3)
mat.set(Uint row, Uint col, Vec4)
```

<a name="getData"></a>

### getData
``` javascript
[Uchar] : mat.getData()
```

<a name="getDataAsync"></a>

### getDataAsync
``` javascript
mat.getDataAsync(callback(Error err, [Uchar] buffer))
```


<a name="getDataAsArray"></a>

### getDataAsArray
``` javascript
[ [Number] ] : mat.getDataAsArray()
[ [ [2 Number] ] ] : mat.getDataAsArray()
[ [ [3 Number] ] ] : mat.getDataAsArray()
[ [ [4 Number] ] ] : mat.getDataAsArray()
```

<a name="getRegion"></a>

### getRegion
``` javascript
Mat : mat.getRegion(Rect region)
```

<a name="copy"></a>

### copy
``` javascript
Mat : mat.copy(Mat mask = null)
```

<a name="copyTo"></a>

### copyTo
``` javascript
Mat : mat.copyTo(Mat dst, Mat mask = null)
```

<a name="convertTo"></a>

### convertTo
``` javascript
Mat : mat.convertTo(Uint type, Number alpha = 1.0, Number beta = 0.0)
```

<a name="norm"></a>

### norm
``` javascript
Number : mat.norm(Mat src2, Uint normType = NORM_L2, Mat mask = noArray())
Number : mat.norm(Uint normType = NORM_L2, Mat mask = noArray())
```

<a name="normalize"></a>

### normalize
``` javascript
Mat : mat.normalize(Number alpha = 1.0, Number beta = 0.0, Uint normType = NORM_L2, Int dtype = -1, Mat mask = noArray())
```

<a name="splitChannels"></a>

### splitChannels
``` javascript
[Mat] : mat.splitChannels()
```

<a name="addWeighted"></a>

### addWeighted
``` javascript
Mat : mat.addWeighted(Number alpha, Mat mat2, Number beta,  Number gamma, Int dtype = -1)
```

<a name="minMaxLoc"></a>

### minMaxLoc
``` javascript
{ minVal: Number, maxVal: Number, minLoc: Point2, maxLoc: Point2 } : mat.minMaxLoc(Mat mask = noArray())
```

<a name="dct"></a>

### dct
``` javascript
Mat : mat.dct(Int flags = 0)
```

<a name="dctAsync"></a>

### dctAsync
``` javascript
mat.dctAsync(Int flags = 0, callback(Error err, Mat result))
```

<a name="idct"></a>

### idct
``` javascript
Mat : mat.idct(Int flags = 0)
```

<a name="idctAsync"></a>

### idctAsync
``` javascript
mat.idctAsync(Int flags = 0, callback(Error err, Mat result))
```

<a name="dft"></a>

### dft
``` javascript
Mat : mat.dft(Int flags = 0, Int nonzeroRows = 0)
```

<a name="dftAsync"></a>

### dftAsync
``` javascript
mat.dftAsync(...opts, callback(Error err, Mat result))
mat.dftAsync({ opts }, callback(Error err, Mat result))
```

<a name="idft"></a>

### idft
``` javascript
Mat : mat.idft(Int flags = 0, Int nonzeroRows = 0)
```

<a name="idftAsync"></a>

### idftAsync
``` javascript
mat.idftAsync(...opts, callback(Error err, Mat result))
mat.idftAsync({ opts }, callback(Error err, Mat result))
```

<a name="mulSpectrums"></a>

### mulSpectrums
``` javascript
Mat : mat.mulSpectrums(Mat mat2, Bool dftRows = false, Bool conjB = false)
```

<a name="mulSpectrumsAsync"></a>

### mulSpectrumsAsync
``` javascript
mat.mulSpectrumsAsync(Mat mat2, ...opts, callback(Error err, Mat result))
mat.mulSpectrumsAsync(Mat mat2, { opts }, callback(Error err, Mat result))
```

<a name="rescale"></a>

### rescale
``` javascript
Mat : mat.rescale(Number factor)
```

<a name="rescale"></a>

### resize
``` javascript
Mat : mat.resize(Uint rows, Uint cols)
```

<a name="resizeToMax"></a>

### resizeToMax
``` javascript
Mat : mat.resizeToMax(Uint maxRowsOrCols)
```

<a name="threshold"></a>

### threshold
``` javascript
Mat : mat.threshold(Number thresh, Number maxVal, Uint type)
```

<a name="thresholdAsync"></a>

### thresholdAsync
``` javascript
mat.thresholdAsync(Number thresh, Number maxVal, Uint type, callback(Error err, Mat result))
```

<a name="adaptiveThreshold"></a>

### adaptiveThreshold
``` javascript
Mat : mat.adaptiveThreshold(Number maxVal, Int adaptiveMethod, Int thresholdType, Int blockSize, Number C)
```

<a name="adaptiveThresholdAsync"></a>

### adaptiveThresholdAsync
``` javascript
mat.adaptiveThresholdAsync(Number maxVal, Int adaptiveMethod, Int thresholdType, Int blockSize, Number C, callback(Error err, Mat result))
```

<a name="inRange"></a>

### inRange
``` javascript
Mat : mat.inRange(Vec3 lower, Vec3 upper)
```

<a name="inRangeAsync"></a>

### inRangeAsync
``` javascript
mat.inRangeAsync(Vec3 lower, Vec3 upper, callback(Error err, Mat result))
```

<a name="cvtColor"></a>

### cvtColor
``` javascript
Mat : mat.cvtColor(Uint code, Uint dstCn = 0)
```

<a name="bgrToGray"></a>

### bgrToGray
``` javascript
Mat : mat.bgrToGray()
```

<a name="warpAffine"></a>

### warpAffine
``` javascript
Mat : mat.warpAffine(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="warpAffineAsync"></a>

### warpAffineAsync
``` javascript
mat.warpAffineAsync(Mat transforMationMatrix, callback(Error err, Mat result))
mat.warpAffineAsync(Mat transforMationMatrix, ...opts, callback(Error err, Mat result))
mat.warpAffineAsync(Mat transforMationMatrix, { opts }, callback(Error err, Mat result))
```

<a name="warpPerspective"></a>

### warpPerspective
``` javascript
Mat : mat.warpPerspective(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="warpPerspectiveAsync"></a>

### warpPerspectiveAsync
``` javascript
mat.warpPerspectiveAsync(Mat transforMationMatrix, callback(Error err, Mat result))
mat.warpPerspectiveAsync(Mat transforMationMatrix, ...opts, callback(Error err, Mat result))
mat.warpPerspectiveAsync(Mat transforMationMatrix, { opts }, callback(Error err, Mat result))
```

<a name="dilate"></a>

### dilate
``` javascript
Mat : mat.dilate(Mat kernel, Point2 anchor = new Point2(-1, -1), Uint iterations = 1, Uint borderType = BORDER_CONSTANT)
```

<a name="erode"></a>

### erode
``` javascript
Mat : mat.erode(Mat kernel,Point2 anchor = new Point2(-1, -1), Uint iterations = 1, Uint borderType = BORDER_CONSTANT)
```

<a name="distanceTransform"></a>

### distanceTransform
``` javascript
Mat : mat.distanceTransform(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
```

<a name="distanceTransformWithLabels"></a>

### distanceTransformWithLabels
``` javascript
{ labels: Mat, dist: Mat } : mat.distanceTransformWithLabels(Uint distanceType, Uint maskSize, Uint labelType = DIST_LABEL_CCOMP)
```

<a name="blur"></a>

### blur
``` javascript
Mat : mat.blur(Size kSize, Point2 anchor = new Point2(-1, -1), Uint borderType = BORDER_CONSTANT)
```

<a name="gaussianBlur"></a>

### gaussianBlur
``` javascript
Mat : mat.gaussianBlur(Size kSize, Number sigmaX, Number sigmaY = 0.0, Uint borderType = BORDER_CONSTANT)
```

<a name="medianBlur"></a>

### medianBlur
``` javascript
Mat : mat.medianBlur(Uint kSize)
```

<a name="connectedComponents"></a>

### connectedComponents
``` javascript
Mat : mat.connectedComponents(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="connectedComponentsWithStats"></a>

### connectedComponentsWithStats
``` javascript
{ labels: Mat, stats: Mat, centroids: Mat } : mat.connectedComponentsWithStats(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="grabCut"></a>

### grabCut
``` javascript
mat.grabCut(Mat mask, Rect rect, Mat bgdModel, Mat fgdModel, Int iterCount, Int mode)
```

<a name="findContours"></a>

### findContours
``` javascript
[Contour] : mat.findContours(Uint mode, Uint method, Point2 offset = new Point2(0, 0))
```

<a name="moments"></a>

### moments
``` javascript
Moments : mat.moments()
```

<a name="drawContours"></a>

### drawContours
``` javascript
mat.drawContours([ Contour ] contours,  Vec3 color, Uint contourIdx = 0, Int maxLevel = INT_MAX, Point2 offset = new Point2(0, 0), Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawLine"></a>

### drawLine
``` javascript
mat.drawLine(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawCircle"></a>

### drawCircle
``` javascript
mat.drawCircle(Point2 center, Uint radius, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawRectangle"></a>

### drawRectangle
``` javascript
mat.drawRectangle(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawEllipse"></a>

### drawEllipse
``` javascript
mat.drawEllipse(RotatedRect box, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1)
```

<a name="putText"></a>

### putText
``` javascript
mat.putText(String text, Point2 origin, Uint fontFace, Number fontScale, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Boolean bottomLeftOrigin = false)
```

<a name="matchTemplate"></a>

### matchTemplate
``` javascript
Mat : mat.matchTemplate(Mat template, Int method, Mat mask = noArray())
```

<a name="matchTemplateAsync"></a>

### matchTemplateAsync
``` javascript
mat.matchTemplateAsync(Mat template, Int method, callback(Error err, Mat result))
mat.matchTemplateAsync(Mat template, Int method, Mat mask, callback(Error err, Mat result))
```

<a name="canny"></a>

### canny
``` javascript
Mat : mat.canny(Number threshold1, Number threshold2, Int apertureSize = 3, Boolean L2gradient = false)
```

<a name="cannyAsync"></a>

### cannyAsync
``` javascript
mat.cannyAsync(Number threshold1, Number threshold2, callback(Error err, Mat result))
mat.cannyAsync(Number threshold1, Number threshold2, ...opts, callback(Error err, Mat result))
mat.cannyAsync(Number threshold1, Number threshold2, { opts }, callback(Error err, Mat result))
```

<a name="sobel"></a>

### sobel
``` javascript
Mat : mat.sobel(Int ddepth, Int dx, Int dy, Int ksize = 3, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="sobelAsync"></a>

### sobelAsync
``` javascript
mat.sobelAsync(Int ddepth, Int dx, Int dy, callback(Error err, Mat result))
mat.sobelAsync(Int ddepth, Int dx, Int dy, ...opts, callback(Error err, Mat result))
mat.sobelAsync(Int ddepth, Int dx, Int dy, { opts }, callback(Error err, Mat result))
```

<a name="scharr"></a>

### scharr
``` javascript
Mat : mat.scharr(Int ddepth, Int dx, Int dy, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="scharrAsync"></a>

### scharrAsync
``` javascript
mat.scharrAsync(Int ddepth, Int dx, Int dy, callback(Error err, Mat result))
mat.scharrAsync(Int ddepth, Int dx, Int dy, ...opts, callback(Error err, Mat result))
mat.scharrAsync(Int ddepth, Int dx, Int dy, { opts }, callback(Error err, Mat result))
```

<a name="laplacian"></a>

### laplacian
``` javascript
Mat : mat.laplacian(Int ddepth, Int ksize = 1, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="laplacianAsync"></a>

### laplacianAsync
``` javascript
mat.laplacianAsync(Int ddepth, callback(Error err, Mat result))
mat.laplacianAsync(Int ddepth, ...opts, callback(Error err, Mat result))
mat.laplacianAsync(Int ddepth, { opts }, callback(Error err, Mat result))
```

<a name="pyrDown"></a>

### pyrDown
``` javascript
Mat : mat.pyrDown(Size size = Size(), Int borderType = BORDER_DEFAULT)
```

<a name="pyrDownAsync"></a>

### pyrDownAsync
``` javascript
mat.pyrDownAsync(callback(Error err, Mat result))
mat.pyrDownAsync(...opts, callback(Error err, Mat result))
mat.pyrDownAsync({ opts }, callback(Error err, Mat result))
```

<a name="pyrUp"></a>

### pyrUp
``` javascript
Mat : mat.pyrUp(Size size = Size(), Int borderType = BORDER_DEFAULT)
```

<a name="pyrUpAsync"></a>

### pyrUpAsync
``` javascript
mat.pyrUpAsync(callback(Error err, Mat result))
mat.pyrUpAsync(...opts, callback(Error err, Mat result))
mat.pyrUpAsync({ opts }, callback(Error err, Mat result))
```

<a name="buildPyramid"></a>

### buildPyramid
``` javascript
[Mat] : mat.buildPyramid(Int maxLevel, Int borderType = BORDER_DEFAULT)
```

<a name="buildPyramidAsync"></a>

### buildPyramidAsync
``` javascript
mat.buildPyramidAsync(Int maxLevel, callback(Error err, [Mat] result))
mat.buildPyramidAsync(Int maxLevel, Int borderType, callback(Error err, [Mat] result))
```

<a name="houghLines"></a>

### houghLines
``` javascript
[Vec2] : mat.houghLines(Number rho, Number theta, Int threshold, Number srn = 0.0, Number stn = 0.0, Number min_theta = 0.0, Number max_theta = PI)
```

<a name="houghLinesAsync"></a>

### houghLinesAsync
``` javascript
mat.houghLinesAsync(Number rho, Number theta, Int threshold, callback(Error err, [Vec2] result))
mat.houghLinesAsync(Number rho, Number theta, Int threshold, ...opts, callback(Error err, [Vec2] result))
mat.houghLinesAsync(Number rho, Number theta, Int threshold, { opts }, callback(Error err, [Vec2] result))
```

<a name="houghLinesP"></a>

### houghLinesP
``` javascript
[Vec4] : mat.houghLinesP(Number rho, Number theta, Int threshold, Number minLineLength = 0.0, Number maxLineGap = 0.0)
```

<a name="houghLinesPAsync"></a>

### houghLinesPAsync
``` javascript
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, callback(Error err, [Vec4] result))
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, ...opts, callback(Error err, [Vec4] result))
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, { opts }, callback(Error err, [Vec4] result))
```

<a name="houghCircles"></a>

### houghCircles
``` javascript
[Vec3] : mat.houghCircles(Int method, Number dp, Number minDist, Number param1 = 100.0, Number param2 = 100.0, Int minRadius = 0, Int maxRadius = 0)
```

<a name="houghCirclesAsync"></a>

### houghCirclesAsync
``` javascript
mat.houghCirclesAsync(Int method, Number dp, Number minDist, callback(Error err, [Vec3] result))
mat.houghCirclesAsync(Int method, Number dp, Number minDist ...opts, callback(Error err, [Vec3] result))
mat.houghCirclesAsync(Int method, Number dp, Number minDist, { opts }, callback(Error err, [Vec3] result))
```