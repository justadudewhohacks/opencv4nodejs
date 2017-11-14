---
layout: default
---

###  TrackerKCF (v3.1, v3.2, v3.3)

<a name="constructors"></a>

####  Constructors
``` ruby
TrackerKCF : new TrackerKCF()
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