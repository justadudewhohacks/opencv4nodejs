# core

<a name="partition"></a>

### partition
``` javascript
{ labels: [Int], Int numLabels } : partition([Point2] data, Boolean : predicate(Point2 pt1, Point2 pt2))
{ labels: [Int], Int numLabels } : partition([Point3] data, Boolean : predicate(Point3 pt1, Point3 pt2))
{ labels: [Int], Int numLabels } : partition([Vec2] data, Boolean : predicate(Vec2 vec1, Vec2 vec2))
{ labels: [Int], Int numLabels } : partition([Vec3] data, Boolean : predicate(Vec3 vec1, Vec3 vec2))
{ labels: [Int], Int numLabels } : partition([Vec4] data, Boolean : predicate(Vec4 vec1, Vec4 vec2))
{ labels: [Int], Int numLabels } : partition([Mat] data, Boolean : predicate(Mat mat1, Mat mat2))
```

<a name="kmeans"></a>

### kmeans
``` javascript
{ labels: [Int], centers: [Point2] } : kmeans([Point2] data, Int k, Int attempts, TermCriteria termCriteria, Int flags)
```


