# io

<a name="imread"></a>

### imread
``` javascript
Mat : imread(String filePath, Int flags = cv.IMREAD_COLOR)
```

<a name="imreadAsync"></a>

### imreadAsync
``` javascript
imreadAsync(String filePath, callback(Error err, Mat img))
imreadAsync(String filePath, Int flags, callback(Error err, Mat img))
```

<a name="imwrite"></a>

### imwrite
``` javascript
imwrite(String filePath, Mat img, [Int] flags = [])
```

<a name="imwriteAsync"></a>

### imwriteAsync
``` javascript
imwriteAsync(String filePath, Mat img, callback(Error err))
imwriteAsync(String filePath, Mat img,  [Int] flags, callback(Error err))
```

<a name="imshow"></a>

### imshow
``` javascript
imshow(String winName, Mat img)
```

<a name="imshowWait"></a>

### imshowWait
``` javascript
imshowWait(String winName, Mat img)
```

<a name="waitKey"></a>

### waitKey
``` javascript
// returns key pressed
Number : waitKey(Uint delay)
```

<a name="imencode"></a>

### imencode
``` javascript
[Uchar] : imencode(String fileExt, Mat img, [Int] flags = [])
```

<a name="imencodeAsync"></a>

### imencodeAsync
``` javascript
imencodeAsync(String fileExt, Mat img, callback(Error err, [Uchar] buffer))
imencodeAsync(String fileExt, Mat img, [Int] flags, callback(Error err, [Uchar] buffer))
```

<a name="imdecode"></a>

### imdecode
``` javascript
Mat : imdecode([Uchar] buffer, Int flags = IMREAD_ANYCOLOR)
```

<a name="imdecodeAsync"></a>

### imdecodeAsync
``` javascript
imdecodeAsync([Uchar] buffer, callback(Error err, [Uchar] buffer))
imdecodeAsync([Uchar] buffer, Int flags, callback(Error err, [Uchar] buffer))
```