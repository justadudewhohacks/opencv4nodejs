# Contribution Guide

First of all, any kind of contribution is highly appreciated, you don't have to be a pro in C++, neither am I. If you are totally new to native Node.js development and would like to get started, you can have a look at my article series as a quick introduction:
<a href="https://medium.com/netscape/tutorial-building-native-c-modules-for-node-js-using-nan-part-1-755b07389c7c"><b>Tutorial to Native Node.js Modules with C++</b></a>

Oftentimes adding bindings is done similarly to what already exists in the codebase. Thus, you can take the existing stuff as an example to help you to get started. In the following, you can find some basic guidelines for adding new OpenCV function bindings to the package.

## API Design

The API is designed such that

A: Parameters passed to a function call are type checked and appropriate messages are displayed to the user in case an error occured. Nobody wants passing garbage to a function by coincidence to fail silently, which may produce unexpected results.

B: A function, which takes more than a single parameter with default values, can conveniently be invoked by passing a JSON object with named parameters in substitution of the optional parameters. For example consider the following function signature from the official OpenCV 3 docs:

``` c++
void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT)
```

The function should be invokable in the following ways:

``` javascript
const mat = new cv.Mat(...)

// required arguments
const size = new cv.Size(...)
const sigmaX = 1.2

// optional arguments
const sigmaY = 1.2
const borderType = cv.BORDER_CONSTANT

let dst

// with required arguments
dst = mat.gaussianBlur(size, sigmaX)

// with optional arguments
dst = mat.gaussianBlur(size, sigmaX, sigmaY)
dst = mat.gaussianBlur(size, sigmaX, sigmaY, borderType)

// with named optional arguments as JSON object
dst = mat.gaussianBlur(size, sigmaX, { sigmaY: 1.2 })
dst = mat.gaussianBlur(size, sigmaX, { borderType: cv.BORDER_CONSTANT })
dst = mat.gaussianBlur(size, sigmaX, { sigmaY: 1.2, borderType: cv.BORDER_CONSTANT })
```

Passing optional arguments as named parameters shall provide the convenience of being able to pass single optional parameters without having to pass every other optional paramater.

## Adding Function Bindings

With the Worker struct you can easily implement the sync and async bindings for a function. If you go conform with the struct pattern, it will automatically handle any typechecking of arguments and unwrapping them via Converters for you so you don't have to worry about checking them manually.

In the .h file add the declaration of the bindings its' worker to the class definition:

``` c++
class Mat : public Nan::ObjectWrap {

  ...

  struct GaussianBlurWorker;
  NAN_METHOD(GaussianBlur);
  NAN_METHOD(GaussianBlurAsync);

}

```

In the .cc file add the implementation of the worker:

``` c++
struct Mat::GaussianBlurWorker : public SimpleWorker {
public:
  // instance of the class exposing the method
  cv::Mat mat;
  GaussianBlurWorker(cv::Mat mat) {
    this->mat = mat;
  }

  // required function arguments
  cv::Size2d kSize;
  double sigmaX;
  // optional function arguments
  double sigmaY = 0;
  int borderType = cv::BORDER_CONSTANT;

  // function return value
  cv::Mat blurMat;

  // here the main work is performed, the async worker will execute
  // this in a different thread
  const char* execute() {
    cv::GaussianBlur(mat, blurMat, kSize, sigmaX, sigmaY, borderType);
    // if you need to handle errors, you can return an error message here, which
    // will trigger the error callback if message is not empty
    return "";
  }

  // return the native objects, handle all object wrapping stuff here
  v8::Local<v8::Value> getReturnValue() {
    return Mat::Converter::wrap(blurMat);
  }

  // implement this method if function takes any required arguments
  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (
      Size::Converter::arg(0, &kSize, info) ||
      DoubleConverter::arg(1, &sigmaX, info)
    );
  }

  // implement this method if function takes any optional arguments
  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (
      DoubleConverter::optArg(2, &sigmaY, info) ||
      IntConverter::optArg(3, &borderType, info)
     );
  }

  // implement the following methods if function takes more than a single optional parameter

  // check if a JSON object as the first argument after the required arguments
  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
    return FF_ARG_IS_OBJECT(2);
  }

  // get the values from named properties of the JSON object
  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
    FF_OBJ opts = info[2]->ToObject();
    return (
      DoubleConverter::optProp(&sigmaY, "sigmaY", opts) ||
      IntConverter::optProp(&borderType, "borderType", opts)
    );
  }
};
```

After you have set up the worker, implementing the bindings is as easy as follows:

``` c++
NAN_METHOD(Mat::GaussianBlur) {
  GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
  FF_WORKER_SYNC("Mat::GaussianBlur", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::GaussianBlurAsync) {
  GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
  FF_WORKER_ASYNC("Mat::GaussianBlurAsync", GaussianBlurWorker, worker);
}
```

## Using converters

For converting native types to v8 types and unwrapping/ wrapping objects and instances you can use the Converters. A Converter will perform type checking and throw an error if converting a value or unwrapping an object failed. If a converter returns true, an error was thrown. You should use the Converters in conjunction with a worker struct. Otherwise you will have to handle rethrowing the error manually. There are Converters for conversion of primitive types, for unwrapping/ wrapping class instances as well as arrays of primitive types and arrays of instances. For representation of a JS array in c++ we are using std::vector.

Some Usage examples:

``` c++
// require arg 0 to be a Mat
cv::Mat img;
Mat::Converter::arg(0, &img, info);

// require arg 0 to be a Mat if arg is passed to the function
cv::Mat img = // some default value
Mat::Converter::optArg(0, &img, info);

// get the the property "image" of an object and convert its value to Mat
cv::Mat img = // some default value
Mat::Converter::optProp(&img, "image", optPropsObject);

// wrapping the Mat object
cv::Mat img = // some mat
v8::Local<v8::Value> jsMat = Mat::Converter::wrap(img);

// primitive type converters
bool aBool;
BoolConverter::arg(0, &aBool, info);
double aDouble;
DoubleConverter::arg(0, &aDouble, info);
float aFloat;
FloatConverter::arg(0, &aFloat, info);
int anInt;
IntConverter::arg(0, &anInt, info);
uint anUint;
UintConverter::arg(0, &anUint, info);
std::string aString;
StringConverter::arg(0, &aString, info);

// converting a std::vector of Points to a JS Array
std::vector<cv::Point2d> points;
v8::Local<v8::Array> jsPoints = ObjectArrayConverter<Point2, cv::Point2d>::wrap(points);

// for simplicity the Point2 class stores cv Points as cv::Point2d, in case you need to wrap a
// std::vector<cv::Point2i> you can use the third template parameter to specify a conversion type
std::vector<cv::Point2i> points;
v8::Local<v8::Array> jsPoints = ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::wrap(points);
```

A class can be made convertable if you you add the typedef for an InstanceConverter the class definition. Example for the Mat class wrapper:

``` c++
class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;

  ...

  cv::Mat* getNativeObjectPtr() { return &mat; }
  cv::Mat getNativeObject() { return mat; }

  typedef InstanceConverter<Mat, cv::Mat> Converter;

  static const char* getClassName() {
    return "Mat";
  }
};
```

## Unit Tests

We test the bindings directly from JS with a classic mocha + chai setup. The purpose of unit testing is not to ensure correct behaviour of OpenCV function calls as OpenCV functionality is tested and none of our business. However, we want to ensure that our bindings can be called without crashing, that all parameters are passed and objects unwrapped correctly and that the function call returns what we expect it to.

You can use 'generateAPITests' to easily generate default tests for a function binding that is implemented sync and async. This will generate the tests which ensure that the synchronous as well as the callbacked and promisified async bindings are called correctly. However, you are welcome to write additional tests. For the 'gaussianBlur' example generating unit tests can be done as follows:

``` javascript
describe('gaussianBlur', () => {
  const matData = [
    [0, 0, 128],
    [0, 128, 255],
    [128, 255, 255]
  ]
  const mat = new cv.Mat(matData, cv.CV_8U)

  const expectOutput = (blurred) => {
    assertMetaData(blurred)(mat.rows, mat.cols, mat.type);
    expect(dangerousDeepEquals(blurred.getDataAsArray(), matData)).to.be.false;
  };

  const kSize = new cv.Size(3, 3);
  const sigmaX = 1.2;

  generateAPITests({
    getDut: () => rgbMat,
    methodName: 'gaussianBlur',
    methodNameSpace: 'Mat',
    getRequiredArgs: () => ([
      kSize,
      sigmaX
    ]),
    getOptionalArgsMap: () => ([
      ['sigmaY', 1.2],
      ['borderType', cv.BORDER_CONSTANT]
    ]),
    expectOutput
  });
});
```

## CI

For continous integration we use Travis CI, which will run a rebuild of the package and run the unit tests for each of the different OpenCV minor versions with and without contrib (opencv3.0, opencv3.1, opencv3.2, opencv3.3, opencv3.3.1, opencv3.0-contrib, opencv3.1-contrib, opencv3.2-contrib, opencv3.3-contrib, opencv3.3.1-contrib). This ensures compatibility across the OpenCV 3 versions as in some minor cases the OpenCV interface may have changed or new features have been added.

The build task will be executed on every push to your working branch as well as every pull request before merging to the master branch. If you have docker set up on your local machine you can run the build tasks on your local machine via the provided npm scripts. For example from the root directory run:

``` bash
npm run build-opencv3.0
# or
npm run build-opencv3.0-contrib
```

## Docs

In the corresponding markdown file in the doc folder add some docs, so that people know how to use the new binding:

<a name="gaussianBlur"></a>

### gaussianBlur

``` javascript
Mat : mat.gaussianBlur(Size kSize, Number sigmaX, Number sigmaY = 0.0, Uint borderType = BORDER_CONSTANT)
```

<a name="gaussianBlurAsync"></a>

### gaussianBlurAsync

``` javascript
mat.gaussianBlurAsync(Size kSize, Number sigmaX, callback(Error err, Mat result))
mat.gaussianBlurAsync(Size kSize, Number sigmaX, ...opts, callback(Error err, Mat result))
mat.gaussianBlurAsync(Size kSize, Number sigmaX, { opts }, callback(Error err, Mat result))
```
