---
layout: default
---

###  imgproc

<a name="getStructuringElement"></a>

#####  getStructuringElement
``` ruby
Mat : getStructuringElement(Uint shape, Size kernelSize, Point2 anchor = new Point(-1, -1))
```

<a name="getRotationMatrix2D"></a>

#####  getRotationMatrix2D
``` ruby
Mat : getRotationMatrix2D(Point2 center, Number angle, Number scale = 1.0)
```

<a name="getAffineTransform"></a>

#####  getAffineTransform
``` ruby
Mat : getAffineTransform([Point2] srcPoints,[Point2] srcPoints)
```

<a name="getPerspectiveTransform"></a>

#####  getPerspectiveTransform
``` ruby
Mat : getPerspectiveTransform([Point2] srcPoints,[Point2] srcPoints)
```

<a name="calcHist"></a>

#####  calcHist
``` ruby
Mat : calcHist(Mat img, [{ channel: Uint, bins: Uint, ranges: [2 Number] }] histAxes, Mat mask = noArray())
```

<a name="plot1DHist"></a>

#####  plot1DHist
``` ruby
Mat : plot1DHist(Mat hist, Mat plotImg, Vec3 color, Uint lineType = LINE_8, Uint thickness = 1, Uint shift = 0)
```

<a name="fitLine"></a>

#####  fitLine
``` ruby
[4 Number] : fitLine([Point2] points, Uint distType, Number param, Number reps, Number aeps)
[6 Number] : fitLine([Point3] points, Uint distType, Number param, Number reps, Number aeps)
```

<a name="canny"></a>

#####  canny (v3.2, v3.3)
``` ruby
Mat : canny(Mat dx, Mat dy, Number threshold1, Number threshold2, Boolean L2gradient = false)
```