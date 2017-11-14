---
layout: default
---

###  Contour

####  Accessors
``` ruby
{
  numPoints: Number,
  area: Number,
  isConvex: Boolean,
  hierarchy: Vec4
}
```

####  Methods

<a name="getPoints"></a>

#####  getPoints
``` ruby
[Point2] : contour.getPoints()
```

<a name="arcLength"></a>

#####  arcLength
``` ruby
Number : contour.arcLength(Boolean closed = false)
```

<a name="convexHull"></a>

#####  convexHull
``` ruby
Contour contour.convexHull(Boolean clockwise = false)
```

<a name="convexHullIndices"></a>

#####  convexHullIndices
``` ruby
[Uint] contour.convexHullIndices(Boolean clockwise = false)
```

<a name="convexityDefects"></a>

#####  convexityDefects
``` ruby
[Vec4] contour.convexityDefects([ Uint ] hullIndices)
```

<a name="boundingRect"></a>

#####  boundingRect
``` ruby
Rect contour.boundingRect()
```

<a name="minEnclosingCircle"></a>

#####  minEnclosingCircle
``` ruby
{ center: Point2, radius: Number } contour.minEnclosingCircle()
```

<a name="minEnclosingTriangle"></a>

#####  minEnclosingTriangle
``` ruby
[3 Point2] contour.minEnclosingTriangle()
```

<a name="minAreaRect"></a>

#####  minAreaRect
``` ruby
RotatedRect contour.minAreaRect()
```

<a name="fitEllipse"></a>

#####  fitEllipse
``` ruby
RotatedRect contour.fitEllipse()
```

<a name="approxPolyDP"></a>

#####  approxPolyDP
``` ruby
[Point2] contour.approxPolyDP(Number epsilon, Boolean closed)
```

<a name="pointPolygonTest"></a>

#####  pointPolygonTest
``` ruby
Number contour.pointPolygonTest(Point2 pt)
```

<a name="matchShapes"></a>

#####  matchShapes
``` ruby
Number contour.matchShapes(Contour contour2, Uint method)
```

<a name="moments"></a>

#####  moments
``` ruby
Moments contour.moments()
```