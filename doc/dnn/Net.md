# Net (v3.3+)

<a name="setInput"></a>

### setInput
``` javascript
net.setInput(Mat blob, String inputName = '')
```

<a name="setInputAsync"></a>

### setInputAsync
``` javascript
net.setInputAsync(callback(Error err))
net.setInputAsync(String inputName = '', callback(Error err))
```

<a name="forward"></a>

### forward
``` javascript
Mat : forward(String inputName = '')
```

<a name="forwardAsync"></a>

### forwardAsync
``` javascript
forwardAsync(callback(Error err, Mat result))
forwardAsync(String inputName, callback(Error err, Mat result))
```