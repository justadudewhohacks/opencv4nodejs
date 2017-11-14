---
layout: default
---

###  Net (v3.3+)

<a name="setInput"></a>

#####  setInput
``` ruby
net.setInput(Mat blob, String inputName = '')
```

<a name="setInputAsync"></a>

#####  setInputAsync
``` ruby
net.setInputAsync(callback(Error err))
net.setInputAsync(String inputName = '', callback(Error err))
```

<a name="forward"></a>

#####  forward
``` ruby
Mat : forward(String inputName = '')
```

<a name="forwardAsync"></a>

#####  forwardAsync
``` ruby
forwardAsync(callback(Error err, Mat result))
forwardAsync(String inputName, callback(Error err, Mat result))
```