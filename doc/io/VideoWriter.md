# VideoWriter

<a name="constructors"></a>

## Constructors
``` javascript
VideoWriter : new VideoWriter(String filePath, Int fourccCode, Number fps, Size frameSize, Bool isColor = true)
```
## Methods

<a name="fourcc"></a>

### fourcc
``` javascript
Int : VideoWriter.fourcc(String fourcc)
```

<a name="write"></a>

### write
``` javascript
writer.write(Mat img)
```

<a name="writeAsync"></a>

### writeAsync
``` javascript
writer.writeAsync(Mat img, callback(Error err))
```

<a name="get"></a>

### get
``` javascript
writer.get(Int property)
```

<a name="set"></a>

### set
``` javascript
writer.set(Int property, Number value)
```

<a name="release"></a>

### release
``` javascript
writer.release()
```