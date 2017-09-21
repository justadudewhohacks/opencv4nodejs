# highgui

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
  
<a name="VideoCapture"></a>
 
# VideoCapture

<a name="VideoCapture.constructors"></a>

## Constructors
``` javascript
VideoCapture : new VideoCapture(String filePath)
VideoCapture : new VideoCapture(Number devicePort)
```
## Methods

<a name="VideoCapture.read"></a>

### read
``` javascript
Mat : read()
```

<a name="VideoCapture.reset"></a>

### reset
``` javascript
reset()
```
