---
layout: default
---

###  MultiTracker (v3.1, v3.2, v3.3)

<a name="constructors"></a>

####  Constructors
``` ruby
MultiTracker : new MultiTracker()
```

####  Methods

<a name="addMil"></a>

#####  addMil
``` ruby
Boolean : tracker.addMil(Mat frame, Rect boundingBox)
```

####  Methods

<a name="addBOOSTING"></a>

#####  addBOOSTING
``` ruby
Boolean : tracker.addBOOSTING(Mat frame, Rect boundingBox)
```

<a name="addMEDIANFLOW"></a>

#####  addMEDIANFLOW
``` ruby
Boolean : tracker.addMEDIANFLOW(Mat frame, Rect boundingBox)
```

<a name="addTLD"></a>

#####  addTLD
``` ruby
Boolean : tracker.addTLD(Mat frame, Rect boundingBox)
```

<a name="addKCF"></a>

#####  addKCF
``` ruby
Boolean : tracker.addKCF(Mat frame, Rect boundingBox)
```

<a name="update"></a>

#####  update
``` ruby
Rect : tracker.update(Mat frame)
```