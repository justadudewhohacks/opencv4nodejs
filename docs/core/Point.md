---
layout: default
---

###  Point

####  Accessors
``` ruby
// Point2
{
  x: Number,
  y: Number
}

// Point3
{
  x: Number,
  y: Number,
  z: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
Point2 : new Vec(Number x, Number y)
Point3 : new Vec(Number x, Number y, Number z
```

<a name="operators"></a>

####  Operators
``` ruby
Point : point.add(Point otherPt)
Point : point.sub(Point otherPt)
Point : point.mul(Number s)
Point : point.div(Number s)

Point : point.norm()
```

####  Methods

<a name="at"></a>

#####  at
``` ruby
Number : point.at(Uint index)
```