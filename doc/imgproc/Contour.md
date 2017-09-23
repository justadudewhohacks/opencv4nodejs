# Contour

## Accessors
``` javascript
{
  numPoints: Number,
  area: Number,
  isConvex: Boolean,
  hierarchy: Vec4
}
```

## Methods

<a name="getPoints"></a>

### getPoints
``` javascript
[Point2] : contour.getPoints()
```

<a name="arcLength"></a>

### arcLength
``` javascript
Number : contour.arcLength(Boolean closed = false)
```

<a name="convexHull"></a>

### convexHull
``` javascript
Contour contour.convexHull(Boolean clockwise = false)
```

<a name="convexHullIndices"></a>

### convexHullIndices
``` javascript
[Uint] contour.convexHullIndices(Boolean clockwise = false)
```

<a name="convexityDefects"></a>

### convexityDefects
``` javascript
[Vec4] contour.convexityDefects([ Uint ] hullIndices)
```

<a name="boundingRect"></a>

### boundingRect
``` javascript
Rect contour.boundingRect()
```

<a name="minEnclosingCircle"></a>

### minEnclosingCircle
``` javascript
{ center: Point2, radius: Number } contour.minEnclosingCircle()
```

<a name="minEnclosingTriangle"></a>

### minEnclosingTriangle
``` javascript
[3 Point2] contour.minEnclosingTriangle()
```

<a name="minAreaRect"></a>

### minAreaRect
``` javascript
RotatedRect contour.minAreaRect()
```

<a name="fitEllipse"></a>

### fitEllipse
``` javascript
RotatedRect contour.fitEllipse()
```

<a name="approxPolyDP"></a>

### approxPolyDP
``` javascript
[Point2] contour.approxPolyDP(Number epsilon, Boolean closed)
```

<a name="pointPolygonTest"></a>

### pointPolygonTest
``` javascript
Number contour.pointPolygonTest(Point2 pt)
```

<a name="matchShapes"></a>

### matchShapes
``` javascript
Number contour.matchShapes(Contour contour2, Uint method)
```

<a name="moments"></a>

### moments
``` javascript
Moments contour.moments()
```