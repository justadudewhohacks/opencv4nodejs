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
Mat : new Mat(Uint rows, Uint cols, Uint type,  [ 2 Number ])
Mat : new Mat(Uint rows, Uint cols, Uint type,  [ 3 Number ])
Mat : new Mat(Uint rows, Uint cols, Uint type,  [ 4 Number ])
Mat : new Mat([ [ Number ] ] dataArray)
Mat : new Mat([ [ [ 2 Number ] ] ] dataArray)
Mat : new Mat([ [ [ 3 Number ] ] ] dataArray)
Mat : new Mat([ [ [ 4 Number ] ] ] dataArray)
Mat : new Mat([Uchar] data, Uint rows, Uint cols, Uint type = CV_8U)
```

<a name="operators"></a>

## Operators
``` javascript
Mat : Mat.add(Mat otherMat)
Mat : Mat.sub(Mat otherMat)
Mat : Mat.mul(Number s)
Mat : Mat.div(Number s)

Mat : Mat.hMul(Mat otherMat)
Mat : Mat.hDiv(Mat otherMat)
Mat : Mat.absdiff(Mat otherMat)

Mat : Mat.exp()
Mat : Mat.mean()
Mat : Mat.sqrt()
Mat : Mat.dot()

Mat : Mat.and(Mat otherMat)
Mat : Mat.or(Mat otherMat)
Mat : Mat.bitwiseAnd(Mat otherMat)
Mat : Mat.bitwiseOr(Mat otherMat)
Mat : Mat.bitwiseXor(Mat otherMat)
Mat : Mat.bitwiseNot()

Mat : Mat.abs()
Number : Mat.determinant()
Mat : Mat.transpose()
```

## Methods

<a name="at"></a>

### at
``` javascript
Number : Mat.at(Uint row, Uint col)
Vec2 : Mat.at(Uint row, Uint col)
Vec3 : Mat.at(Uint row, Uint col)
Vec4 : Mat.at(Uint row, Uint col)
```

<a name="atRaw"></a>

### atRaw
``` javascript
Number : Mat.atRaw(Uint row, Uint col)
[ 2 Number ] : Mat.atRaw(Uint row, Uint col)
[ 3 Number ] : Mat.atRaw(Uint row, Uint col)
[ 4 Number ] : Mat.atRaw(Uint row, Uint col)
```

<a name="set"></a>

### set
``` javascript
Mat.set(Uint row, Uint col, Number)
Mat.set(Uint row, Uint col, [ 2 Number ])
Mat.set(Uint row, Uint col, [ 3 Number ])
Mat.set(Uint row, Uint col, [ 4 Number ])
Mat.set(Uint row, Uint col, Vec2)
Mat.set(Uint row, Uint col, Vec3)
Mat.set(Uint row, Uint col, Vec4)
```

<a name="getData"></a>

### getData
``` javascript
[ Uchar ] : Mat.getData()
```

<a name="getDataAsArray"></a>

### getDataAsArray
``` javascript
[ [ Number ] ] : Mat.getDataAsArray()
[ [ [ 2 Number ] ] ] : Mat.getDataAsArray()
[ [ [ 3 Number ] ] ] : Mat.getDataAsArray()
[ [ [ 4 Number ] ] ] : Mat.getDataAsArray()
```

<a name="getRegion"></a>

### getRegion
``` javascript
Mat : Mat.getRegion(Rect region)
```

<a name="copy"></a>

### copy
``` javascript
Mat : Mat.copy(Mat mask = null)
```

<a name="copyTo"></a>

### copyTo
``` javascript
Mat : Mat.copyTo(Mat dst, : Mat mask = null)
```

<a name="convertTo"></a>

### convertTo
``` javascript
Mat : Mat.convertTo(Uint type, Number alpha = 1.0, Number beta = 0.0)
```

<a name="norm"></a>

### norm
``` javascript
Number : Mat.norm(Mat src2, Uint normType = NORM_L2, : Mat mask = noArray())
Number : Mat.norm(Uint normType = NORM_L2, : Mat mask = noArray())
```

<a name="normalize"></a>

### normalize
``` javascript
Mat : Mat.normalize(Number alpha = 1.0, Number beta = 0.0, Uint normType = NORM_L2, Int dtype = -1, : Mat mask = noArray())
[ Mat ] : Mat.splitChannels()
```

<a name="rescale"></a>

### rescale
``` javascript
Mat : Mat.rescale(Number factor)
```

<a name="rescale"></a>

### resize
``` javascript
Mat : Mat.resize(Uint rows, Uint cols)
```

<a name="resizeToMax"></a>

### resizeToMax
``` javascript
Mat : Mat.resizeToMax(Uint maxRowsOrCols)
```

<a name="threshold"></a>

### threshold
``` javascript
Mat : Mat.threshold(Number thresh, Number maxVal, Uint type)
```

<a name="inRange"></a>

### inRange
``` javascript
Mat : Mat.inRange(Vec3 lower, Vec3 upper)
```

<a name="cvtColor"></a>

### cvtColor
``` javascript
Mat : Mat.cvtColor(Uint code, Uint dstCn = 0)
```

<a name="bgrToGray"></a>

### bgrToGray
``` javascript
Mat : Mat.bgrToGray()
```

<a name="warpAffine"></a>

### warpAffine
``` javascript
Mat : Mat.warpAffine(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="warpPerspective"></a>

### warpPerspective
``` javascript
Mat : Mat.warpPerspective(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="dilate"></a>

### dilate
``` javascript
Mat : Mat.dilate(Mat kernel, Point2 anchor = new Point2(-1, -1), Uint iterations, Uint borderType = BORDER_CONSTANT)
```

<a name="erode"></a>

### erode
``` javascript
Mat : Mat.erode(Mat kernel,Point2 anchor = new Point2(-1, -1), Uint iterations, Uint borderType = BORDER_CONSTANT)
```

<a name="distanceTransform"></a>

### distanceTransform
``` javascript
Mat : Mat.distanceTransform(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
```

<a name="distanceTransformWithLabels"></a>

### distanceTransformWithLabels
``` javascript
{ labels: Mat, dist: Mat } : Mat.distanceTransformWithLabels(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
```

<a name="blur"></a>

### blur
``` javascript
Mat : Mat.blur(Size kSize, Point2 anchor = new Point2(-1, -1), Uint borderType = BORDER_CONSTANT)
```

<a name="gaussianBlur"></a>

### gaussianBlur
``` javascript
Mat : Mat.gaussianBlur(Size kSize, Number sigmaX, Number sigmaY = 0.0, Uint borderType = BORDER_CONSTANT)
```

<a name="medianBlur"></a>

### medianBlur
``` javascript
Mat : Mat.medianBlur(Uint kSize)
```

<a name="connectedComponents"></a>

### connectedComponents
``` javascript
Mat : Mat.connectedComponents(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="connectedComponentsWithStats"></a>

### connectedComponentsWithStats
``` javascript
{ labels: Mat, stats: Mat, centroids: Mat } : Mat.connectedComponentsWithStats(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="findContours"></a>

### findContours
``` javascript
[ Contour ] : Mat.findContours(Uint mode, Uint method, Point2 offset = new Point2(0, 0))
```

<a name="moments"></a>

### moments
``` javascript
Moments : Mat.moments()
```

<a name="drawContours"></a>

### drawContours
``` javascript
Mat.drawContours([ Contour ] contours,  Vec3 color, Uint contourIdx = 0, Int maxLevel = INT_MAX, Point2 offset = new Point2(0, 0), Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawLine"></a>

### drawLine
``` javascript
Mat.drawLine(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawCircle"></a>

### drawCircle
``` javascript
Mat.drawCircle(Point2 center, Uint radius, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawRectangle"></a>

### drawRectangle
``` javascript
Mat.drawRectangle(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawEllipse"></a>

### drawEllipse
``` javascript
Mat.drawEllipse(RotatedRect box, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1)
```

<a name="putText"></a>

### putText
``` javascript
Mat.putText(String text, Point2 origin, Uint fontFace, Number fontScale, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Boolean bottomLeftOrigin = false)
```
