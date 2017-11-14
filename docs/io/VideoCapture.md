---
layout: default
---

###  VideoCapture

<a name="constructors"></a>

####  Constructors
``` ruby
VideoCapture : new VideoCapture(String filePath)
VideoCapture : new VideoCapture(Number devicePort)
```
####  Methods

<a name="read"></a>

#####  read
``` ruby
Mat : cap.read()
```

<a name="readAsync"></a>

#####  readAsync
``` ruby
cap.readAsync(callback(Error err, Mat frame))
```

<a name="reset"></a>

#####  reset
``` ruby
cap.reset()
```

<a name="get"></a>

#####  get
``` ruby
cap.get(Int property)
```

<a name="set"></a>

#####  set
``` ruby
cap.set(Int property, Number value)
```

<a name="release"></a>

#####  release
``` ruby
cap.release()
```