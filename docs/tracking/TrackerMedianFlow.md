---
layout: default
---

###  TrackerMedianFlow

<a name="constructors"></a>

####  Constructors
``` ruby
TrackerMedianFlow : new TrackerMedianFlow(Int pointsInGrid = null)
```

####  Methods

<a name="clear"></a>

#####  clear
``` ruby
tracker.clear()
```

<a name="init"></a>

#####  init
``` ruby
Boolean : tracker.init(Mat frame, Rect boundingBox)
```

<a name="update"></a>

#####  update
``` ruby
Rect : tracker.update(Mat frame)
```