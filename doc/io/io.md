# io

<a name="imread"></a>

### imread
``` javascript
Mat : imread(String filePath)
```

<a name="imwrite"></a>

### imwrite
``` javascript
imwrite(String filePath, Mat img)
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
[Uchar] : imencode(String fileExt, Mat img, [Int] flags)
```

<a name="imdecode"></a>

### imdecode
``` javascript
Mat : imdecode([Uchar] buffer, Int flags)
```
