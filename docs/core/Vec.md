---
layout: default
---

###  Vec

####  Accessors
``` ruby
// Vec2
{
  x: Number,
  y: Number
}

// Vec3
{
  x: Number,
  y: Number,
  z: Number
}

// Vec4
{
  w: Number,
  x: Number,
  y: Number,
  z: Number
}
```

<a name="constructors"></a>

####  Constructors
``` ruby
Vec2 : new Vec(Number x, Number y)
Vec3 : new Vec(Number x, Number y, Number z
Vec4 : new Vec(Number x, Number y, Number z, Number w)
```

<a name="operators"></a>

####  Operators
``` ruby
Vec : vec.add(Vec otherVec)
Vec : vec.sub(Vec otherVec)
Vec : vec.mul(Number s)
Vec : vec.div(Number s)

Vec : vec.hMul(Vec otherVec)
Vec : vec.hDiv(Vec otherVec)
Vec : vec.absdiff(Vec otherVec)

Vec : vec.exp()
Vec : vec.mean()
Vec : vec.sqrt()
Number : Vec.norm()

Vec3 : vec3.cross()
```

####  Methods

<a name="at"></a>

#####  at
``` ruby
Number : vec.at(Uint index)
```