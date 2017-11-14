---
layout: default
---

###  io

<a name="imread"></a>

#####  imread
``` ruby
Mat : imread(String filePath)
```

<a name="imreadAsync"></a>

#####  imreadAsync
``` ruby
imreadAsync(String filePath, callback(Error err, Mat img))
```

<a name="imwrite"></a>

#####  imwrite
``` ruby
imwrite(String filePath, Mat img)
```

<a name="imwriteAsync"></a>

#####  imwriteAsync
``` ruby
imwriteAsync(String filePath, Mat img, callback(Error err))
```

<a name="imshow"></a>

#####  imshow
``` ruby
imshow(String winName, Mat img)
```

<a name="imshowWait"></a>

#####  imshowWait
``` ruby
imshowWait(String winName, Mat img)
```

<a name="waitKey"></a>

#####  waitKey
``` ruby
// returns key pressed
Number : waitKey(Uint delay)
```

<a name="imencode"></a>

#####  imencode
``` ruby
[Uchar] : imencode(String fileExt, Mat img, [Int] flags = [])
```

<a name="imencodeAsync"></a>

#####  imencodeAsync
``` ruby
imencodeAsync(String fileExt, Mat img, callback(Error err, [Uchar] buffer))
imencodeAsync(String fileExt, Mat img, [Int] flags, callback(Error err, [Uchar] buffer))
```

<a name="imdecode"></a>

#####  imdecode
``` ruby
Mat : imdecode([Uchar] buffer, Int flags = IMREAD_ANYCOLOR)
```

<a name="imdecodeAsync"></a>

#####  imdecodeAsync
``` ruby
imdecodeAsync([Uchar] buffer, callback(Error err, [Uchar] buffer))
imdecodeAsync([Uchar] buffer, Int flags, callback(Error err, [Uchar] buffer))
```