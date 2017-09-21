# Point

## Accessors
``` javascript
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

## Constructors
``` javascript
Point2 : new Vec(Number x, Number y)
Point3 : new Vec(Number x, Number y, Number z
```

<a name="operators"></a>

## Operators
``` javascript
Point : point.add(Point otherPt)
Point : point.sub(Point otherPt)
Point : point.mul(Number s)
Point : point.div(Number s)

Point : point.norm()
```

## Methods

<a name="at"></a>

### at
``` javascript
Number : point.at(Uint index)
```