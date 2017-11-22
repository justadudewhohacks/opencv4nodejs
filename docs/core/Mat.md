---
layout: default
---

###  Mat

####  Accessors
``` ruby
Mat {
  rows: Number,
  cols: Number,
  type: Number,
  channels: Number,
  depth: Number,
  dims: Number,
  empty: Boolean,
  sizes: [Number]
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
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

####  Operators
``` ruby
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

####  Methods

<a name="at"></a>

#####  at
``` ruby
Number : mat.at(Uint row, Uint col)
Vec2 : mat.at(Uint row, Uint col)
Vec3 : mat.at(Uint row, Uint col)
Vec4 : mat.at(Uint row, Uint col)
```

<a name="atRaw"></a>

#####  atRaw
``` ruby
Number : mat.atRaw(Uint row, Uint col)
[2 Number] : mat.atRaw(Uint row, Uint col)
[3 Number] : mat.atRaw(Uint row, Uint col)
[4 Number] : mat.atRaw(Uint row, Uint col)
```

<a name="set"></a>

#####  set
``` ruby
mat.set(Uint row, Uint col, Number)
mat.set(Uint row, Uint col, [2 Number])
mat.set(Uint row, Uint col, [3 Number])
mat.set(Uint row, Uint col, [4 Number])
mat.set(Uint row, Uint col, Vec2)
mat.set(Uint row, Uint col, Vec3)
mat.set(Uint row, Uint col, Vec4)
```

<a name="getData"></a>

#####  getData
``` ruby
[Uchar] : mat.getData()
```

<a name="getDataAsync"></a>

#####  getDataAsync
``` ruby
mat.getDataAsync(callback(Error err, [Uchar] buffer))
```


<a name="getDataAsArray"></a>

#####  getDataAsArray
``` ruby
[ [Number] ] : mat.getDataAsArray()
[ [ [2 Number] ] ] : mat.getDataAsArray()
[ [ [3 Number] ] ] : mat.getDataAsArray()
[ [ [4 Number] ] ] : mat.getDataAsArray()
```

<a name="getRegion"></a>

#####  getRegion
``` ruby
Mat : mat.getRegion(Rect region)
```

<a name="copy"></a>

#####  copy
``` ruby
Mat : mat.copy(Mat mask = null)
```

<a name="copyAsync"></a>

#####  copyAsync
``` ruby
mat.copyAsync(callback(Error err, Mat result))
mat.copyAsync(Mat mask, callback(Error err, Mat result))
```

<a name="copyTo"></a>

#####  copyTo
``` ruby
Mat : mat.copyTo(Mat dst, Mat mask = null)
```

<a name="copyToAsync"></a>

#####  copyToAsync
``` ruby
mat.copyToAsync(Mat dst, callback(Error err, Mat result))
mat.copyToAsync(Mat dst, Mat mask, callback(Error err, Mat result))
```

<a name="convertTo"></a>

#####  convertTo
``` ruby
Mat : mat.convertTo(Uint type, Number alpha = 1.0, Number beta = 0.0)
```

<a name="convertToAsync"></a>

#####  convertToAsync
``` ruby
mat.convertToAsync(Uint type, callback(Error err, Mat result))
mat.convertToAsync(Uint type, ...opts, callback(Error err, Mat result))
mat.convertToAsync(Uint type, { opts }, callback(Error err, Mat result))
```

<a name="norm"></a>

#####  norm
``` ruby
Number : mat.norm(Mat src2, Uint normType = NORM_L2, Mat mask = noArray())
Number : mat.norm(Uint normType = NORM_L2, Mat mask = noArray())
```

<a name="normalize"></a>

#####  normalize
``` ruby
Mat : mat.normalize(Number alpha = 1.0, Number beta = 0.0, Uint normType = NORM_L2, Int dtype = -1, Mat mask = noArray())
```

<a name="splitChannels"></a>

#####  splitChannels
``` ruby
[Mat] : mat.splitChannels()
```

<a name="splitChannelsAsync"></a>

#####  splitChannelsAsync
``` ruby
mat.splitChannelsAsync(callback(Error err, [Mat] result))
```

<a name="addWeighted"></a>

#####  addWeighted
``` ruby
Mat : mat.addWeighted(Number alpha, Mat mat2, Number beta, Number gamma, Int dtype = -1)
```

<a name="addWeightedAsync"></a>

#####  addWeightedAsync
``` ruby
mat.addWeightedAsync(Number alpha, Mat mat2, Number beta, Number gamma, callback(Error err, Mat result))
mat.addWeightedAsync(Number alpha, Mat mat2, Number beta, Number gamma, Int dtype, callback(Error err, Mat result))
```

<a name="minMaxLoc"></a>

#####  minMaxLoc
``` ruby
{ minVal: Number, maxVal: Number, minLoc: Point2, maxLoc: Point2 } : mat.minMaxLoc(Mat mask = noArray())
```

<a name="minMaxLocAsync"></a>

#####  minMaxLocAsync
``` ruby
mat.minMaxLocAsync(callback(Error err, { minVal: Number, maxVal: Number, minLoc: Point2, maxLoc: Point2 } result))
mat.minMaxLocAsync(Mat mask, callback(Error err, { minVal: Number, maxVal: Number, minLoc: Point2, maxLoc: Point2 } result))
```

<a name="dct"></a>

#####  dct
``` ruby
Mat : mat.dct(Int flags = 0)
```

<a name="dctAsync"></a>

#####  dctAsync
``` ruby
mat.dctAsync(Int flags = 0, callback(Error err, Mat result))
```

<a name="idct"></a>

#####  idct
``` ruby
Mat : mat.idct(Int flags = 0)
```

<a name="idctAsync"></a>

#####  idctAsync
``` ruby
mat.idctAsync(Int flags = 0, callback(Error err, Mat result))
```

<a name="dft"></a>

#####  dft
``` ruby
Mat : mat.dft(Int flags = 0, Int nonzeroRows = 0)
```

<a name="dftAsync"></a>

#####  dftAsync
``` ruby
mat.dftAsync(...opts, callback(Error err, Mat result))
mat.dftAsync({ opts }, callback(Error err, Mat result))
```

<a name="idft"></a>

#####  idft
``` ruby
Mat : mat.idft(Int flags = 0, Int nonzeroRows = 0)
```

<a name="idftAsync"></a>

#####  idftAsync
``` ruby
mat.idftAsync(...opts, callback(Error err, Mat result))
mat.idftAsync({ opts }, callback(Error err, Mat result))
```

<a name="mulSpectrums"></a>

#####  mulSpectrums
``` ruby
Mat : mat.mulSpectrums(Mat mat2, Bool dftRows = false, Bool conjB = false)
```

<a name="mulSpectrumsAsync"></a>

#####  mulSpectrumsAsync
``` ruby
mat.mulSpectrumsAsync(Mat mat2, ...opts, callback(Error err, Mat result))
mat.mulSpectrumsAsync(Mat mat2, { opts }, callback(Error err, Mat result))
```

<a name="rescale"></a>

#####  rescale
``` ruby
Mat : mat.rescale(Number factor)
```

<a name="rescaleAsync"></a>

#####  rescaleAsync
``` ruby
mat.rescaleAsync(Number factor, callback(Error err, Mat result))
```

<a name="resize"></a>

#####  resize
``` ruby
Mat : mat.resize(Uint rows, Uint cols)
```

<a name="resizeAsync"></a>

#####  resizeAsync
``` ruby
mat.resizeAsync(Uint rows, Uint cols, callback(Error err, Mat result))
```

<a name="resizeToMax"></a>

#####  resizeToMax
``` ruby
Mat : mat.resizeToMax(Uint maxRowsOrCols)
```

<a name="resizeToMaxAsync"></a>

#####  resizeToMaxAsync
``` ruby
mat.resizeToMaxAsync(Uint maxRowsOrCols, callback(Error err, Mat result))
```

<a name="threshold"></a>

#####  threshold
``` ruby
Mat : mat.threshold(Number thresh, Number maxVal, Uint type)
```

<a name="thresholdAsync"></a>

#####  thresholdAsync
``` ruby
mat.thresholdAsync(Number thresh, Number maxVal, Uint type, callback(Error err, Mat result))
```

<a name="adaptiveThreshold"></a>

#####  adaptiveThreshold
``` ruby
Mat : mat.adaptiveThreshold(Number maxVal, Int adaptiveMethod, Int thresholdType, Int blockSize, Number C)
```

<a name="adaptiveThresholdAsync"></a>

#####  adaptiveThresholdAsync
``` ruby
mat.adaptiveThresholdAsync(Number maxVal, Int adaptiveMethod, Int thresholdType, Int blockSize, Number C, callback(Error err, Mat result))
```

<a name="inRange"></a>

#####  inRange
``` ruby
Mat : mat.inRange(Vec3 lower, Vec3 upper)
```

<a name="inRangeAsync"></a>

#####  inRangeAsync
``` ruby
mat.inRangeAsync(Vec3 lower, Vec3 upper, callback(Error err, Mat result))
```

<a name="cvtColor"></a>

#####  cvtColor
``` ruby
Mat : mat.cvtColor(Uint code, Uint dstCn = 0)
```

<a name="cvtColorAsync"></a>

#####  cvtColorAsync
``` ruby
mat.cvtColorAsync(Uint code, callback(Error err, Mat result))
mat.cvtColorAsync(Uint code, Uint dstCn, callback(Error err, Mat result))
```

<a name="bgrToGray"></a>

#####  bgrToGray
``` ruby
Mat : mat.bgrToGray()
```

<a name="bgrToGrayAsync"></a>

#####  bgrToGrayAsync
``` ruby
mat.bgrToGrayAsync(callback(Error err, Mat result))
```

<a name="warpAffine"></a>

#####  warpAffine
``` ruby
Mat : mat.warpAffine(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="warpAffineAsync"></a>

#####  warpAffineAsync
``` ruby
mat.warpAffineAsync(Mat transforMationMatrix, callback(Error err, Mat result))
mat.warpAffineAsync(Mat transforMationMatrix, ...opts, callback(Error err, Mat result))
mat.warpAffineAsync(Mat transforMationMatrix, { opts }, callback(Error err, Mat result))
```

<a name="warpPerspective"></a>

#####  warpPerspective
``` ruby
Mat : mat.warpPerspective(Mat transforMationMatrix, Size size = new Size(this.cols, this.rows), Uint flags = INTER_LINEAR, Uint borderMode = BORDER_CONSTANT)
```

<a name="warpPerspectiveAsync"></a>

#####  warpPerspectiveAsync
``` ruby
mat.warpPerspectiveAsync(Mat transforMationMatrix, callback(Error err, Mat result))
mat.warpPerspectiveAsync(Mat transforMationMatrix, ...opts, callback(Error err, Mat result))
mat.warpPerspectiveAsync(Mat transforMationMatrix, { opts }, callback(Error err, Mat result))
```

<a name="dilate"></a>

#####  dilate
``` ruby
Mat : mat.dilate(Mat kernel, Point2 anchor = new Point2(-1, -1), Uint iterations = 1, Uint borderType = BORDER_CONSTANT)
```

<a name="dilateAsync"></a>

#####  dilateAsync
``` ruby
mat.dilateAsync(Mat kernel, callback(Error err, Mat result))
mat.dilateAsync(Mat kernel, ...opts, callback(Error err, Mat result))
mat.dilateAsync(Mat kernel, { opts }, callback(Error err, Mat result))
```

<a name="erode"></a>

#####  erode
``` ruby
Mat : mat.erode(Mat kernel, Point2 anchor = new Point2(-1, -1), Uint iterations = 1, Uint borderType = BORDER_CONSTANT)
```

<a name="erodeAsync"></a>

#####  erodeAsync
``` ruby
mat.erodeAsync(Mat kernel, callback(Error err, Mat result))
mat.erodeAsync(Mat kernel, ...opts, callback(Error err, Mat result))
mat.erodeAsync(Mat kernel, { opts }, callback(Error err, Mat result))
```

<a name="morphologyEx"></a>

#####  morphologyEx
``` ruby
Mat : mat.morphologyEx(Mat kernel, Int morphType, Point2 anchor = new Point2(-1, -1), Uint iterations = 1, Uint borderType = BORDER_CONSTANT)
```

<a name="morphologyExAsync"></a>

#####  morphologyExAsync
``` ruby
mat.morphologyExAsync(Mat kernel, Int morphType, callback(Error err, Mat result))
mat.morphologyExAsync(Mat kernel, Int morphType, ...opts, callback(Error err, Mat result))
mat.morphologyExAsync(Mat kernel, Int morphType, { opts }, callback(Error err, Mat result))
```

<a name="distanceTransform"></a>

#####  distanceTransform
``` ruby
Mat : mat.distanceTransform(Uint distanceType, Uint maskSize, Uint dstType = CV_32F)
```

<a name="distanceTransformAsync"></a>

#####  distanceTransformAsync
``` ruby
mat.distanceTransformAsync(Uint distanceType, Uint maskSize, callback(Error err, Mat result))
mat.distanceTransformAsync(Uint distanceType, Uint maskSize, Uint dstType, callback(Error err, Mat result))
```

<a name="distanceTransformWithLabels"></a>

#####  distanceTransformWithLabels
``` ruby
{ labels: Mat, dist: Mat } : mat.distanceTransformWithLabels(Uint distanceType, Uint maskSize, Uint labelType = DIST_LABEL_CCOMP)
```

<a name="distanceTransformWithLabelsAsync"></a>

#####  distanceTransformWithLabelsAsync
``` ruby
mat.distanceTransformWithLabelsAsync(Uint distanceType, Uint maskSize, callback(Error err, { labels: Mat, dist: Mat } result))
mat.distanceTransformWithLabelsAsync(Uint distanceType, Uint maskSize, Uint labelType, callback(Error err, { labels: Mat, dist: Mat } result))
```

<a name="blur"></a>

#####  blur
``` ruby
Mat : mat.blur(Size kSize, Point2 anchor = new Point2(-1, -1), Uint borderType = BORDER_CONSTANT)
```

<a name="blurAsync"></a>

#####  blurAsync
``` ruby
mat.blurAsync(Size kSize, callback(Error err, Mat result))
mat.blurAsync(Size kSize, ...opts, callback(Error err, Mat result))
mat.blurAsync(Size kSize, { opts }, callback(Error err, Mat result))
```

<a name="gaussianBlur"></a>

#####  gaussianBlur
``` ruby
Mat : mat.gaussianBlur(Size kSize, Number sigmaX, Number sigmaY = 0.0, Uint borderType = BORDER_CONSTANT)
```

<a name="gaussianBlurAsync"></a>

#####  gaussianBlurAsync
``` ruby
mat.gaussianBlurAsync(Size kSize, Number sigmaX, callback(Error err, Mat result))
mat.gaussianBlurAsync(Size kSize, Number sigmaX, ...opts, callback(Error err, Mat result))
mat.gaussianBlurAsync(Size kSize, Number sigmaX, { opts }, callback(Error err, Mat result))
```

<a name="medianBlur"></a>

#####  medianBlur
``` ruby
Mat : mat.medianBlur(Int kSize)
```

<a name="medianBlurAsync"></a>

#####  medianBlurAsync
``` ruby
mat.medianBlurAsync(Int kSize, callback(Error err, Mat result))
```

<a name="connectedComponents"></a>

#####  connectedComponents
``` ruby
Mat : mat.connectedComponents(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="connectedComponentsAsync"></a>

#####  connectedComponentsAsync
``` ruby
mat.connectedComponentsAsync(callback(Error err, Mat result))
mat.connectedComponentsAsync(Uint connectivity, callback(Error err, Mat result))
mat.connectedComponentsAsync(Uint connectivity, Uint ltype, callback(Error err, Mat result))
```

<a name="connectedComponentsWithStats"></a>

#####  connectedComponentsWithStats
``` ruby
{ labels: Mat, stats: Mat, centroids: Mat } : mat.connectedComponentsWithStats(Uint connectivity = 8, Uint ltype = CV_32S)
```

<a name="connectedComponentsWithStatsAsync"></a>

#####  connectedComponentsWithStatsAsync
``` ruby
mat.connectedComponentsWithStatsAsync(callback(Error err, { labels: Mat, stats: Mat, centroids: Mat } result))
mat.connectedComponentsWithStatsAsync(Uint connectivity, callback(Error err, { labels: Mat, stats: Mat, centroids: Mat } result))
mat.connectedComponentsWithStatsAsync(Uint connectivity, Uint ltype, callback(Error err, { labels: Mat, stats: Mat, centroids: Mat } result))
```

<a name="grabCut"></a>

#####  grabCut
``` ruby
mat.grabCut(Mat mask, Rect rect, Mat bgdModel, Mat fgdModel, Int iterCount, Int mode)
```

<a name="grabCutAsync"></a>

#####  grabCutAsync
``` ruby
mat.grabCutAsync(Mat mask, Rect rect, Mat bgdModel, Mat fgdModel, Int iterCount, Int mode, callback(Error err))
```

<a name="findContours"></a>

#####  findContours
``` ruby
[Contour] : mat.findContours(Uint mode, Uint method, Point2 offset = new Point2(0, 0))
```

<a name="findContoursAsync"></a>

#####  findContoursAsync
``` ruby
mat.findContoursAsync(Uint mode, Uint method, callback(Error err, [Contour] result))
mat.findContoursAsync(Uint mode, Uint method, Point2 offset, callback(Error err, [Contour] result))
```

<a name="moments"></a>

#####  moments
``` ruby
Moments : mat.moments()
```

<a name="momentsAsync"></a>

#####  momentsAsync
``` ruby
mat.momentsAsync(callback(Error err, Moments result))
```

<a name="drawContours"></a>

#####  drawContours
``` ruby
mat.drawContours([ Contour ] contours,  Vec3 color, Uint contourIdx = 0, Int maxLevel = INT_MAX, Point2 offset = new Point2(0, 0), Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawLine"></a>

#####  drawLine
``` ruby
mat.drawLine(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawCircle"></a>

#####  drawCircle
``` ruby
mat.drawCircle(Point2 center, Uint radius, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawRectangle"></a>

#####  drawRectangle
``` ruby
mat.drawRectangle(Point2 pt0, Point2 pt1, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="drawEllipse"></a>

#####  drawEllipse
``` ruby
mat.drawEllipse(RotatedRect box, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1)
```

<a name="putText"></a>

#####  putText
``` ruby
mat.putText(String text, Point2 origin, Uint fontFace, Number fontScale, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Boolean bottomLeftOrigin = false)
```

<a name="matchTemplate"></a>

#####  matchTemplate
``` ruby
Mat : mat.matchTemplate(Mat template, Int method, Mat mask = noArray())
```

<a name="matchTemplateAsync"></a>

#####  matchTemplateAsync
``` ruby
mat.matchTemplateAsync(Mat template, Int method, callback(Error err, Mat result))
mat.matchTemplateAsync(Mat template, Int method, Mat mask, callback(Error err, Mat result))
```

<a name="canny"></a>

#####  canny
``` ruby
Mat : mat.canny(Number threshold1, Number threshold2, Int apertureSize = 3, Boolean L2gradient = false)
```

<a name="cannyAsync"></a>

#####  cannyAsync
``` ruby
mat.cannyAsync(Number threshold1, Number threshold2, callback(Error err, Mat result))
mat.cannyAsync(Number threshold1, Number threshold2, ...opts, callback(Error err, Mat result))
mat.cannyAsync(Number threshold1, Number threshold2, { opts }, callback(Error err, Mat result))
```

<a name="sobel"></a>

#####  sobel
``` ruby
Mat : mat.sobel(Int ddepth, Int dx, Int dy, Int ksize = 3, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="sobelAsync"></a>

#####  sobelAsync
``` ruby
mat.sobelAsync(Int ddepth, Int dx, Int dy, callback(Error err, Mat result))
mat.sobelAsync(Int ddepth, Int dx, Int dy, ...opts, callback(Error err, Mat result))
mat.sobelAsync(Int ddepth, Int dx, Int dy, { opts }, callback(Error err, Mat result))
```

<a name="scharr"></a>

#####  scharr
``` ruby
Mat : mat.scharr(Int ddepth, Int dx, Int dy, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="scharrAsync"></a>

#####  scharrAsync
``` ruby
mat.scharrAsync(Int ddepth, Int dx, Int dy, callback(Error err, Mat result))
mat.scharrAsync(Int ddepth, Int dx, Int dy, ...opts, callback(Error err, Mat result))
mat.scharrAsync(Int ddepth, Int dx, Int dy, { opts }, callback(Error err, Mat result))
```

<a name="laplacian"></a>

#####  laplacian
``` ruby
Mat : mat.laplacian(Int ddepth, Int ksize = 1, Number scale = 1.0, Number delta = 0.0, Int borderType = BORDER_DEFAULT)
```

<a name="laplacianAsync"></a>

#####  laplacianAsync
``` ruby
mat.laplacianAsync(Int ddepth, callback(Error err, Mat result))
mat.laplacianAsync(Int ddepth, ...opts, callback(Error err, Mat result))
mat.laplacianAsync(Int ddepth, { opts }, callback(Error err, Mat result))
```

<a name="pyrDown"></a>

#####  pyrDown
``` ruby
Mat : mat.pyrDown(Size size = Size(), Int borderType = BORDER_DEFAULT)
```

<a name="pyrDownAsync"></a>

#####  pyrDownAsync
``` ruby
mat.pyrDownAsync(callback(Error err, Mat result))
mat.pyrDownAsync(...opts, callback(Error err, Mat result))
mat.pyrDownAsync({ opts }, callback(Error err, Mat result))
```

<a name="pyrUp"></a>

#####  pyrUp
``` ruby
Mat : mat.pyrUp(Size size = Size(), Int borderType = BORDER_DEFAULT)
```

<a name="pyrUpAsync"></a>

#####  pyrUpAsync
``` ruby
mat.pyrUpAsync(callback(Error err, Mat result))
mat.pyrUpAsync(...opts, callback(Error err, Mat result))
mat.pyrUpAsync({ opts }, callback(Error err, Mat result))
```

<a name="buildPyramid"></a>

#####  buildPyramid
``` ruby
[Mat] : mat.buildPyramid(Int maxLevel, Int borderType = BORDER_DEFAULT)
```

<a name="buildPyramidAsync"></a>

#####  buildPyramidAsync
``` ruby
mat.buildPyramidAsync(Int maxLevel, callback(Error err, [Mat] result))
mat.buildPyramidAsync(Int maxLevel, Int borderType, callback(Error err, [Mat] result))
```

<a name="houghLines"></a>

#####  houghLines
``` ruby
[Vec2] : mat.houghLines(Number rho, Number theta, Int threshold, Number srn = 0.0, Number stn = 0.0, Number min_theta = 0.0, Number max_theta = PI)
```

<a name="houghLinesAsync"></a>

#####  houghLinesAsync
``` ruby
mat.houghLinesAsync(Number rho, Number theta, Int threshold, callback(Error err, [Vec2] result))
mat.houghLinesAsync(Number rho, Number theta, Int threshold, ...opts, callback(Error err, [Vec2] result))
mat.houghLinesAsync(Number rho, Number theta, Int threshold, { opts }, callback(Error err, [Vec2] result))
```

<a name="houghLinesP"></a>

#####  houghLinesP
``` ruby
[Vec4] : mat.houghLinesP(Number rho, Number theta, Int threshold, Number minLineLength = 0.0, Number maxLineGap = 0.0)
```

<a name="houghLinesPAsync"></a>

#####  houghLinesPAsync
``` ruby
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, callback(Error err, [Vec4] result))
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, ...opts, callback(Error err, [Vec4] result))
mat.houghLinesPAsync(Number rho, Number theta, Int threshold, { opts }, callback(Error err, [Vec4] result))
```

<a name="houghCircles"></a>

#####  houghCircles
``` ruby
[Vec3] : mat.houghCircles(Int method, Number dp, Number minDist, Number param1 = 100.0, Number param2 = 100.0, Int minRadius = 0, Int maxRadius = 0)
```

<a name="houghCirclesAsync"></a>

#####  houghCirclesAsync
``` ruby
mat.houghCirclesAsync(Int method, Number dp, Number minDist, callback(Error err, [Vec3] result))
mat.houghCirclesAsync(Int method, Number dp, Number minDist ...opts, callback(Error err, [Vec3] result))
mat.houghCirclesAsync(Int method, Number dp, Number minDist, { opts }, callback(Error err, [Vec3] result))
```

<a name="rodrigues"></a>

#####  rodrigues
``` ruby
{ dst: Mat, jacobian: Mat } : mat.rodrigues()
```

<a name="rodriguesAsync"></a>

#####  rodriguesAsync
``` ruby
mat.rodriguesAsync(callback(Error err, { dst: Mat, jacobian: Mat } result))
```

<a name="rqDecomp3x3"></a>

#####  rqDecomp3x3
``` ruby
{ returnValue: Vec3, mtxR: Mat, mtxQ: Mat, Qx: Mat, Qy: Mat, Qz: Mat } : mat.rqDecomp3x3()
```

<a name="rqDecomp3x3Async"></a>

#####  rqDecomp3x3Async
``` ruby
mat.rqDecomp3x3Async(callback(Error err, { returnValue: Vec3, mtxR: Mat, mtxQ: Mat, Qx: Mat, Qy: Mat, Qz: Mat } result))
```

<a name="decomposeProjectionMatrix"></a>

#####  decomposeProjectionMatrix
``` ruby
{ cameraMatrix: Mat, rotMatrix: Mat, transVect: Vec4, rotMatrixX: Mat, rotMatrixY: Mat, rotMatrixZ: Mat, eulerAngles: Mat } : mat.decomposeProjectionMatrix()
```

<a name="decomposeProjectionMatrixAsync"></a>

#####  decomposeProjectionMatrixAsync
``` ruby
mat.decomposeProjectionMatrixAsync(callback(Error err, { cameraMatrix: Mat, rotMatrix: Mat, transVect: Vec4, rotMatrixX: Mat, rotMatrixY: Mat, rotMatrixZ: Mat, eulerAngles: Mat } result))
```

<a name="matMulDeriv"></a>

#####  matMulDeriv
``` ruby
{ dABdA: Mat, dABdB: Mat } : mat.matMulDeriv(Mat B)
```

<a name="matMulDerivAsync"></a>

#####  matMulDerivAsync
``` ruby
mat.matMulDerivAsync(Mat B, callback(Error err, { dABdA: Mat, dABdB: Mat } result))
```

<a name="findChessboardCorners"></a>

#####  findChessboardCorners
``` ruby
{ returnValue: Boolean, corners: [Point2] } : mat.findChessboardCorners(Size patternSize, Int flags = cv.CALIB_CB_ADAPTIVE_THRESH + cv.CALIB_CB_NORMALIZE_IMAGE)
```

<a name="findChessboardCornersAsync"></a>

#####  findChessboardCornersAsync
``` ruby
mat.findChessboardCornersAsync(Size patternSize, callback(Error err, { returnValue: Boolean, corners: [Point2] } result))
mat.findChessboardCornersAsync(Size patternSize, Int flags, callback(Error err, { returnValue: Boolean, corners: [Point2] } result))
```

<a name="drawChessboardCorners"></a>

#####  drawChessboardCorners
``` ruby
mat.drawChessboardCorners(Size patternSize, [Point2] corners, Boolean patternWasFound)
```

<a name="drawChessboardCornersAsync"></a>

#####  drawChessboardCornersAsync
``` ruby
mat.drawChessboardCornersAsync(Size patternSize, [Point2] corners, Boolean patternWasFound, callback(Error err))
```

<a name="find4QuadCornerSubpix"></a>

#####  find4QuadCornerSubpix
``` ruby
Boolean : mat.find4QuadCornerSubpix([Point2] corners, Size regionSize)
```

<a name="find4QuadCornerSubpixAsync"></a>

#####  find4QuadCornerSubpixAsync
``` ruby
mat.find4QuadCornerSubpixAsync([Point2] corners, Size regionSize, callback(Error err, Boolean result))
```

<a name="calibrationMatrixValues"></a>

#####  calibrationMatrixValues
``` ruby
{ fovx: Number, fovy: Number, focalLength: Number, principalPoint: Point2, aspectRatio: Number } : mat.calibrationMatrixValues(Size imageSize, Number apertureWidth, Number apertureHeight)
```

<a name="calibrationMatrixValuesAsync"></a>

#####  calibrationMatrixValuesAsync
``` ruby
mat.calibrationMatrixValuesAsync(Size imageSize, Number apertureWidth, Number apertureHeight, callback(Error err, { fovx: Number, fovy: Number, focalLength: Number, principalPoint: Point2, aspectRatio: Number } result))
```

<a name="stereoRectify"></a>

#####  stereoRectify
``` ruby
{ R1: Mat, R2: Mat, P1: Mat, P2: Mat, Q: Mat, roi1: Rect, roi2: Rect } : mat.stereoRectify([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, Mat R, Vec3 T, Int flags = cv.CALIB_ZERO_DISPARITY, Number alpha = -1, Size newImageSize = new Size())
```

<a name="stereoRectifyAsync"></a>

#####  stereoRectifyAsync
``` ruby
mat.stereoRectifyAsync([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, Mat R, Vec3 T, callback(Error err, { R1: Mat, R2: Mat, P1: Mat, P2: Mat, Q: Mat, roi1: Rect, roi2: Rect } result))
mat.stereoRectifyAsync([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, Mat R, Vec3 T, ...opts, callback(Error err, { R1: Mat, R2: Mat, P1: Mat, P2: Mat, Q: Mat, roi1: Rect, roi2: Rect } result))
mat.stereoRectifyAsync([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, Mat R, Vec3 T, { opts }, callback(Error err, { R1: Mat, R2: Mat, P1: Mat, P2: Mat, Q: Mat, roi1: Rect, roi2: Rect } result))
```

<a name="rectify3Collinear"></a>

#####  rectify3Collinear
``` ruby
{ returnValue: Number, R1: Mat, R2: Mat, R3: Mat, P1: Mat, P2: Mat, P3: Mat, Q: Mat, roi1: Rect, roi2: Rect } : mat.rectify3Collinear([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, at cameraMatrix3,  [Number] distCoeffs3, Size imageSize, Mat R12, Vec3 T12, Mat R13, Vec3 T13, Number alpha, Size newImageSize, Int flags)
```

<a name="rectify3CollinearAsync"></a>

#####  rectify3CollinearAsync
``` ruby
mat.rectify3CollinearAsync([Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, at cameraMatrix3,  [Number] distCoeffs3, Size imageSize, Mat R12, Vec3 T12, Mat R13, Vec3 T13, Number alpha, Size newImageSize, Int flags, callback(Error err, { returnValue: Number, R1: Mat, R2: Mat, R3: Mat, P1: Mat, P2: Mat, P3: Mat, Q: Mat, roi1: Rect, roi2: Rect } result))
```

<a name="getOptimalNewCameraMatrix"></a>

#####  getOptimalNewCameraMatrix
``` ruby
{ out: Mat, validPixROI: Rect } : mat.getOptimalNewCameraMatrix([Number] distCoeffs, Size imageSize, Number alpha, Size newImageSize = new Size(), Boolean centerPrincipalPoint = false)
```

<a name="getOptimalNewCameraMatrixAsync"></a>

#####  getOptimalNewCameraMatrixAsync
``` ruby
mat.getOptimalNewCameraMatrixAsync([Number] distCoeffs, Size imageSize, Number alpha, callback(Error err, { out: Mat, validPixROI: Rect } result)
mat.getOptimalNewCameraMatrixAsync([Number] distCoeffs, Size imageSize, Number alpha, ...opts, callback(Error err, { out: Mat, validPixROI: Rect } result)
mat.getOptimalNewCameraMatrixAsync([Number] distCoeffs, Size imageSize, Number alpha, { opts }, callback(Error err, { out: Mat, validPixROI: Rect } result)
```

<a name="decomposeEssentialMat"></a>

#####  decomposeEssentialMat
``` ruby
{ R1: Mat, R2: Mat, T: Vec3 } : mat.decomposeEssentialMat()
```

<a name="decomposeEssentialMatAsync"></a>

#####  decomposeEssentialMatAsync
``` ruby
mat.decomposeEssentialMatAsync(callback(Error err, { R1: Mat, R2: Mat, T: Vec3 } result))
```

<a name="triangulatePoints"></a>

#####  triangulatePoints
``` ruby
{ points4D: Mat } : mat.triangulatePoints([Point2] projPoints1, [Point2] projPoints2)
```

<a name="triangulatePointsAsync"></a>

#####  triangulatePointsAsync
``` ruby
mat.triangulatePointsAsync([Point2] projPoints1, [Point2] projPoints2, callback(Error err, { points4D: Mat } result))
```

<a name="correctMatches"></a>

#####  correctMatches
``` ruby
{ newPoints1: [Point2], newPoints2: [Point2] } : mat.correctMatches([Point2] points1, [Point2] points2)
```

<a name="correctMatchesAsync"></a>

#####  correctMatchesAsync
``` ruby
mat.correctMatchesAsync([Point2] points1, [Point2] points2, callback(Error err, { newPoints1: [Point2], newPoints2: [Point2] } result))
```

<a name="filterSpeckles"></a>

#####  filterSpeckles
``` ruby
{ newPoints1: [Point2], newPoints2: [Point2] } : mat.filterSpeckles(Number newVal, Int maxSpeckleSize, Number maxDiff)
```

<a name="filterSpecklesAsync"></a>

#####  filterSpecklesAsync
``` ruby
mat.filterSpecklesAsync(Number newVal, Int maxSpeckleSize, Number maxDiff, callback(Error err, { newPoints1: [Point2], newPoints2: [Point2] } result))
```

<a name="validateDisparity"></a>

#####  validateDisparity
``` ruby
mat.validateDisparity(Mat cost, Int minDisparity, Int numberOfDisparities, Int disp12MaxDisp = 1)
```

<a name="validateDisparityAsync"></a>

#####  validateDisparityAsync
``` ruby
mat.validateDisparityAsync(Mat cost, Int minDisparity, Int numberOfDisparities, callback(Error err))
mat.validateDisparityAsync(Mat cost, Int minDisparity, Int numberOfDisparities, Int disp12MaxDisp, callback(Error err))
```

<a name="reprojectImageTo3D"></a>

#####  reprojectImageTo3D
``` ruby
Mat : mat.reprojectImageTo3D(Mat Q, Boolean handleMissingValues = false, Int ddepth = -1)
```

<a name="reprojectImageTo3DAsync"></a>

#####  reprojectImageTo3DAsync
``` ruby
Mat : mat.reprojectImageTo3DAsync(Mat Q, callback(Error err, Mat result))
Mat : mat.reprojectImageTo3DAsync(Mat Q, ...opts, callback(Error err, Mat result))
Mat : mat.reprojectImageTo3DAsync(Mat Q, { opts }, callback(Error err, Mat result))
```

<a name="decomposeHomographyMat"></a>

#####  decomposeHomographyMat
``` ruby
{ returnValue: Int, rotations: [Mat], translations: [Mat], normals: [Mat] } : mat.decomposeHomographyMat(Mat K)
```

<a name="decomposeHomographyMatAsync"></a>

#####  decomposeHomographyMatAsync
``` ruby
mat.decomposeHomographyMatAsync(Mat K, callback(Error err, { returnValue: Int, rotations: [Mat], translations: [Mat], normals: [Mat] } result))
```

<a name="findEssentialMat"></a>

#####  findEssentialMat (v3.1+)
``` ruby
{ E: Mat, mask: Mat } : mat.findEssentialMat([Point2] points1, [Point2] points2, Int method = cv.RANSAC, Number prob = 0.999, Number threshold = 1.0)
```

<a name="findEssentialMatAsync"></a>

#####  findEssentialMatAsync (v3.1+)
``` ruby
mat.findEssentialMatAsync([Point2] points1, [Point2] points2, callback(Error err, { E: Mat, mask: Mat } result))
mat.findEssentialMatAsync([Point2] points1, [Point2] points2, ...opts, callback(Error err, { E: Mat, mask: Mat } result))
mat.findEssentialMatAsync([Point2] points1, [Point2] points2, { opts }, callback(Error err, { E: Mat, mask: Mat } result))
```

<a name="recoverPose"></a>

#####  recoverPose (v3.1+)
``` ruby
{ returnValue: Int, R: Mat, T: Vec3 } : mat.recoverPose(Mat E, [Point2] points1, [Point2] points2, Mat mask = noArray())
```

<a name="recoverPoseAsync"></a>

#####  recoverPoseAsync (v3.1+)
``` ruby
mat.recoverPoseAsync(Mat E, [Point2] points1, [Point2] points2, callback(Error err, { returnValue: Int, R: Mat, T: Vec3 } result))
mat.recoverPoseAsync(Mat E, [Point2] points1, [Point2] points2, Mat mask = noArray(), callback(Error err, { returnValue: Int, R: Mat, T: Vec3 } result))
```
