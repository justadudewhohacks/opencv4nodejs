---
layout: default
---

###  VideoWriter

<a name="constructors"></a>

####  Constructors
``` ruby
VideoWriter : new VideoWriter(String filePath, Int fourccCode, Number fps, Size frameSize, Bool isColor = true)
```
####  Methods

<a name="fourcc"></a>

#####  fourcc
``` ruby
Int : VideoWriter.fourcc(String fourcc)
```

<a name="write"></a>

#####  write
``` ruby
writer.write(Mat img)
```

<a name="writeAsync"></a>

#####  writeAsync
``` ruby
writer.writeAsync(Mat img, callback(Error err))
```

<a name="get"></a>

#####  get
``` ruby
writer.get(Int property)
```

<a name="set"></a>

#####  set
``` ruby
writer.set(Int property, Number value)
```

<a name="release"></a>

#####  release
``` ruby
writer.release()
```