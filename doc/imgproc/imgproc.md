# imgproc

<a name="getStructuringElement"></a>

### getStructuringElement
``` javascript
Mat : getStructuringElement(Uint shape, Size kernelSize, Point2 anchor = new Point(-1, -1))
```

<a name="getRotationMatrix2D"></a>

### getRotationMatrix2D
``` javascript
Mat : getRotationMatrix2D(Point2 center, Number angle, Number scale = 1.0)
```

<a name="calcHist"></a>

### calcHist
``` javascript
Mat : calcHist(Mat img, [{ channel: Uint, bins: Uint, ranges: [2 Number] }] histAxes, Mat mask = noArray())
```

<a name="plot1DHist"></a>

### plot1DHist
``` javascript
Mat : plot1DHist(Mat hist, Mat plotImg, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="fitLine"></a>

### fitLine
``` javascript
[4 Number] : fitLine([Point2] points, Uint distType, Number param, Number reps, Number aeps)
[6 Number] : fitLine([Point3] points, Uint distType, Number param, Number reps, Number aeps)
```

