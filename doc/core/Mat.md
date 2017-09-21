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
Mat : mat.copyTo(Mat dst, : Mat mask = null)
```

<a name="convertTo"></a>

### convertTo
``` javascript
Mat : mat.convertTo(Uint type, Number alpha = 1.0, Number beta = 0.0)
```

<a name="norm"></a>

### norm
``` javascript
Number : mat.norm(Mat src2, Uint normType = NORM_L2, : Mat mask = noArray())
Number : mat.norm(Uint normType = NORM_L2, : Mat mask = noArray())
```

<a name="normalize"></a>

### normalize
``` javascript
Mat : mat.normalize(Number alpha = 1.0, Number beta = 0.0, Uint normType = NORM_L2, Int dtype = -1, : Mat mask = noArray())
[Mat] : mat.splitChannels()
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

<a name="inRange"></a>

### inRange
``` javascript
Mat : mat.inRange(Vec3 lower, Vec3 upper)
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

<a name="warpPerspective"></a>

### warpPerspective
``` javascript
Mat : mat.warpPerspective(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="dilate"></a>

### dilate
``` javascript
Mat : mat.dilate(Mat kernel, Point2 anchor = new Point2(-1, -1), Uint iterations, Uint borderType = BORDER_CONSTANT)
```

<a name="erode"></a>

### erode
``` javascript
Mat : mat.erode(Mat kernel,Point2 anchor = new Point2(-1, -1), Uint iterations, Uint borderType = BORDER_CONSTANT)
```

<a name="distanceTransform"></a>

### distanceTransform
``` javascript
Mat : mat.distanceTransform(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
```

<a name="distanceTransformWithLabels"></a>

### distanceTransformWithLabels
``` javascript
{ labels: Mat, dist: Mat } : mat.distanceTransformWithLabels(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
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
