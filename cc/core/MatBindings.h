#include "Mat.h"

#ifndef __FF_MATBINDINGS_H__
#define __FF_MATBINDINGS_H__

namespace MatBindings {

  struct SetToWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    SetToWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat mask = cv::noArray().getMat();

    double newVal1;
    cv::Vec2d newVal2;
    cv::Vec3d newVal3;
    cv::Vec4d newVal4;

    cv::Mat returnValue;

    std::string executeCatchCvExceptionWorker() {
      switch (self.channels()) {
        case 2:
          returnValue = self.setTo(newVal2, mask);
          break;
        case 3:
          returnValue = self.setTo(newVal3, mask);
          break;
        case 4:
          returnValue = self.setTo(newVal4, mask);
          break;
        default:
          returnValue = self.setTo(newVal1, mask);
          break;
      }

      return "";
    }

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      switch (self.channels()) {
        case 2:
          return (Vec2::Converter::arg(0, &newVal2, info));
          break;
        case 3:
          return (Vec3::Converter::arg(0, &newVal3, info));
          break;
        case 4:
          return (Vec4::Converter::arg(0, &newVal4, info));
          break;
        default:
          return (DoubleConverter::arg(0, &newVal1, info));
          break;
      }
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(1, &mask, info)
      );
    }
  };

  struct PushBackWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    PushBackWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat mat;

    std::string executeCatchCvExceptionWorker() {
      self.push_back(mat);
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &mat, info)
      );
    }

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(self);
    }
  };

  struct PopBackWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    PopBackWorker(cv::Mat self) {
      this->self = self;
    }

    int num = 1;

    std::string executeCatchCvExceptionWorker() {
      self.pop_back(num);
      return "";
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(0, &num, info)
      );
    }

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(self);
    }
  };

  struct GetDataWorker : CatchCvExceptionWorker {
  public:
    cv::Mat mat;

    GetDataWorker(cv::Mat mat) {
      this->mat = mat;
    }

    size_t size;
    char *data;

    std::string executeCatchCvExceptionWorker() {
      size = mat.rows * mat.cols * mat.elemSize();
      data = static_cast<char *>(malloc(size));
      memcpy(data, mat.data, size);
      return "";
    }

    static void freeBufferCallback(char* data, void* hint) {
      free(data);
    }

    FF_VAL getReturnValue() {
      return Nan::NewBuffer(data, size, freeBufferCallback, 0).ToLocalChecked();
    }
  };

  struct CopyWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    CopyWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat dst;
    cv::Mat mask = cv::noArray().getMat();

    std::string executeCatchCvExceptionWorker() {
      self.copyTo(dst, mask);
      return "";
    }

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(0, &mask, info)
      );
    }
  };

  struct CopyToWorker : public CopyWorker {
  public:
    CopyToWorker(cv::Mat self) : CopyWorker(self){
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &dst, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(1, &mask, info)
      );
    }
  };

  struct ConvertToWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    ConvertToWorker(cv::Mat self) {
      this->self = self;
    }

    int rtype;
    double alpha = 1.0;
    double beta = 0.0;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      self.convertTo(dst, rtype, alpha, beta);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::arg(0, &rtype, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &alpha, info) ||
        DoubleConverter::optArg(2, &beta, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject();
      return (
        DoubleConverter::optProp(&alpha, "alpha", opts) ||
        DoubleConverter::optProp(&beta, "beta", opts)
      );
    }
  };

  struct SplitChannelsWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    SplitChannelsWorker(cv::Mat self) {
      this->self = self;
    }


    std::vector<cv::Mat> mv;

    std::string executeCatchCvExceptionWorker() {
      cv::split(self, mv);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return ObjectArrayConverter<Mat, cv::Mat> ::wrap(mv);
    }
  };

  struct AddWeightedWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    AddWeightedWorker(cv::Mat self) {
      this->self = self;
    }

    double alpha;
    cv::Mat src2;
    double beta;
    double gamma;
    int dtype = -1;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      cv::addWeighted(self, alpha, src2, beta, gamma, dst, dtype);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::arg(0, &alpha, info) ||
        Mat::Converter::arg(1, &src2, info) ||
        DoubleConverter::arg(2, &beta, info) ||
        DoubleConverter::arg(3, &gamma, info)
        );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(4, &dtype, info)
      );
    }
  };

  struct MinMaxLocWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    MinMaxLocWorker(cv::Mat self) {
      this->self = self;
    }

    double minVal, maxVal;
    cv::Point2i minLoc, maxLoc;
    cv::Mat mask = cv::noArray().getMat();

    std::string executeCatchCvExceptionWorker() {
      cv::minMaxLoc(self, &minVal, &maxVal, &minLoc, &maxLoc, mask);
      return "";
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::optArg(0, &mask, info);
    }

    v8::Local<v8::Value> getReturnValue() {
      FF_OBJ ret = FF_NEW_OBJ();
      Nan::Set(ret, FF_NEW_STRING("minVal"), Nan::New(minVal));
      Nan::Set(ret, FF_NEW_STRING("maxVal"), Nan::New(maxVal));
      Nan::Set(ret, FF_NEW_STRING("minLoc"), Point2::Converter::wrap(minLoc));
      Nan::Set(ret, FF_NEW_STRING("maxLoc"), Point2::Converter::wrap(maxLoc));
      return ret;
    }
  };

  struct FindNonZeroWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    FindNonZeroWorker(cv::Mat self) {
      this->self = self;
    }

    std::vector<cv::Point> idx;

    std::string executeCatchCvExceptionWorker() {
      cv::findNonZero(self, idx);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(idx);
    }
  };

  struct CountNonZeroWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    CountNonZeroWorker(cv::Mat self) {
      this->self = self;
    }

    int num;

    std::string executeCatchCvExceptionWorker() {
      num = cv::countNonZero(self);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return IntConverter::wrap(num);
    }
  };

  struct PadToSquareWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    PadToSquareWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Vec3d fillVec = cv::Vec3d();
    cv::Mat out;
    std::string executeCatchCvExceptionWorker() {
      int maxDim = (std::max)(self.cols, self.rows);
      out = cv::Mat(maxDim, maxDim, self.type(), (cv::Vec3b)fillVec);

      int offX = 0, offY = 0;
      if (self.cols > self.rows) {
        offY = (self.cols - self.rows) / 2;
      }
      else {
        offX = (self.rows - self.cols) / 2;
      }
      cv::Mat roi = out(cv::Rect(offX, offY, self.cols, self.rows));
      self.copyTo(roi);

      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(out);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Vec3::Converter::optArg(0, &fillVec, info);
    }
  };

  struct DTWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat mat;
    bool isInverse;

    DTWorker(cv::Mat mat, bool isInverse) {
      this->mat = mat;
      this->isInverse = isInverse;
    }

    int flags = 0;

    cv::Mat dst;

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return false;
    }
  };

  struct DCTWorker : public DTWorker {
    DCTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
    }

    std::string executeCatchCvExceptionWorker() {
      if (isInverse) {
        cv::idct(mat, dst, flags);
      }
      else {
        cv::dct(mat, dst, flags);
      }
      return "";
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return IntConverter::optArg(0, &flags, info);
    }
  };

  struct DFTWorker : public DTWorker {
    DFTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
    }

    int nonzeroRows = 0;

    std::string executeCatchCvExceptionWorker() {
      if (isInverse) {
        cv::idft(mat, dst, flags, nonzeroRows);
      }
      else {
        cv::dft(mat, dst, flags, nonzeroRows);
      }
      return "";
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(0, &flags, info) ||
        IntConverter::optArg(1, &nonzeroRows, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(0);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      FF_OBJ opts = info[0]->ToObject();
      return (
        IntConverter::optProp(&flags, "flags", opts) ||
        IntConverter::optProp(&nonzeroRows, "nonzeroRows", opts)
      );
    }
  };

  struct MulSpectrumsWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat mat;
    bool isInverse;

    MulSpectrumsWorker(cv::Mat mat) {
      this->mat = mat;
    }

    cv::Mat mat2;
    bool dftRows = false;
    bool conjB = false;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      int flags = (dftRows ? cv::DFT_ROWS : 0);
      cv::mulSpectrums(mat, mat2, dst, flags, conjB);
      return "";
    }

    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &mat2, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        BoolConverter::optArg(1, &dftRows, info) ||
        BoolConverter::optArg(2, &conjB, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      FF_OBJ opts = info[1]->ToObject();
      return (
        BoolConverter::optProp(&dftRows, "dftRows", opts) ||
        BoolConverter::optProp(&conjB, "conjB", opts)
      );
    }
  };

  struct TransformWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    TransformWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat m;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      cv::transform(self, dst, m);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &m, info)
      );
    }
  };

  struct PerspectiveTransformWorker : public TransformWorker {
  public:
    PerspectiveTransformWorker(cv::Mat self) : TransformWorker(self) {
    }

    std::string executeCatchCvExceptionWorker() {
      cv::perspectiveTransform(self, dst, m);
      return "";
    }
  };

  struct OpWithCodeWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    OpWithCodeWorker(cv::Mat self) {
      this->self = self;
    }

    int code;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      cv::flip(self, dst, code);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::arg(0, &code, info)
      );
    }
  };

  struct FlipWorker : public OpWithCodeWorker {
  public:
    FlipWorker(cv::Mat self) : OpWithCodeWorker(self) {
    }

    std::string executeCatchCvExceptionWorker() {
      cv::flip(self, dst, code);
      return "";
    }
  };

  struct SumWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    SumWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Scalar sum;

    std::string executeCatchCvExceptionWorker() {
      sum = cv::sum(self);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      switch (self.channels()) {
      case 1:
        return DoubleConverter::wrap(sum[0]);
      case 2:
        return Vec2::Converter::wrap(cv::Vec2f(sum[0], sum[1]));
      case 3:
        return Vec3::Converter::wrap(cv::Vec3f(sum[0], sum[1], sum[2]));
      case 4:
        return Vec4::Converter::wrap(cv::Vec4f(sum));
      default:
        return Nan::Undefined();
      }
    }
  };

  struct ConvertScaleAbsWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    ConvertScaleAbsWorker(cv::Mat self) {
      this->self = self;
    }

    double alpha = 1;
    double beta = 0;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      cv::convertScaleAbs(self, dst, alpha, beta);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(0, &alpha, info) ||
        DoubleConverter::optArg(1, &beta, info)
        );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(0);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[0]->ToObject();
      return (
        DoubleConverter::optProp(&alpha, "alpha", opts) ||
        DoubleConverter::optProp(&beta, "beta", opts)
        );
    }
  };

  struct GoodFeaturesToTrackWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    GoodFeaturesToTrackWorker(cv::Mat self) {
      this->self = self;
    }

    // required function arguments
    int maxCorners;
    double qualityLevel;
    double minDistance;

    // optional args
    cv::Mat mask = cv::noArray().getMat();
    // default values from: https://docs.opencv.org/3.4.1/dd/d1a/group__imgproc__feature.html#ga1d6bb77486c8f92d79c8793ad995d541
    int blockSize = 3;
    int gradientSize = 3;
    bool useHarrisDetector = false;
    double harrisK = 0.04;

    // function return value
    std::vector<cv::Point2f> corners;

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::arg(0, &maxCorners, info) ||
        DoubleConverter::arg(1, &qualityLevel, info) ||
        DoubleConverter::arg(2, &minDistance, info)
      );
    }
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      // if 5th arg is Boolean, then we check for the 7 param signature
      if (info[5]->IsBoolean()){
        return (
          Mat::Converter::optArg(3, &mask, info) ||
          IntConverter::optArg(4, &blockSize, info) ||
          BoolConverter::optArg(5, &useHarrisDetector, info) ||
          DoubleConverter::optArg(6, &harrisK, info)
        );

      } // else we check for the 8 param signature
      else {
        return (
          Mat::Converter::optArg(3, &mask, info) ||
          IntConverter::optArg(4, &blockSize, info) ||
          IntConverter::optArg(5, &gradientSize, info) ||
          BoolConverter::optArg(6, &useHarrisDetector, info) ||
          DoubleConverter::optArg(7, &harrisK, info)
        );
      }
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(3);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[3]->ToObject();
      return (
        Mat::Converter::optProp(&mask, "mask", opts) ||
        IntConverter::optProp(&blockSize, "blockSize", opts) ||
        IntConverter::optProp(&gradientSize, "gradientSize", opts) ||
        BoolConverter::optProp(&useHarrisDetector, "useHarrisDetector", opts) ||
        DoubleConverter::optProp(&harrisK, "harrisK", opts)
      );
    }


    std::string executeCatchCvExceptionWorker() {
  #if CV_VERSION_MINOR >= 4
      cv::goodFeaturesToTrack(
          self, corners,
          maxCorners, qualityLevel, minDistance,
          mask, blockSize, gradientSize,
          useHarrisDetector, harrisK);
  #else
      cv::goodFeaturesToTrack(
          self, corners,
          maxCorners, qualityLevel, minDistance,
          mask, blockSize,
          useHarrisDetector, harrisK);
  #endif
      return "";
    }

    FF_VAL getReturnValue() {
      return ObjectArrayConverter<Point2, cv::Point2f>::wrap(corners);
    }
  };

  struct MeanWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat self;
	  MeanWorker(cv::Mat self) {
		  this->self = self;
	  }

	  cv::Mat mask = cv::noArray().getMat();

	  cv::Scalar mean;

	  std::string executeCatchCvExceptionWorker() {
		  mean = cv::mean(self, mask);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  return Vec4::Converter::wrap(cv::Vec4d(mean));
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  Mat::Converter::optArg(0, &mask, info)
			);
	  }
  };

  struct MeanStdDevWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    MeanStdDevWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat mask = cv::noArray().getMat();

    cv::Mat mean;
    cv::Mat stddev;

    std::string executeCatchCvExceptionWorker() {
      cv::meanStdDev(self, mean, stddev, mask);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("mean").ToLocalChecked(), Mat::Converter::wrap(mean));
      Nan::Set(ret, Nan::New("stddev").ToLocalChecked(), Mat::Converter::wrap(stddev));
      return ret;
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(0, &mask, info)
      );
    }
  };

  struct CopyMakeBorderWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat self;
	  CopyMakeBorderWorker(cv::Mat self) {
		  this->self = self;
	  }

	  cv::Mat result;
	  int top, bottom, left, right;
	  int borderType = cv::BORDER_CONSTANT;
	  double v1 = 0;
	  cv::Vec2d v2 = 0;
	  cv::Vec3d v3 = 0;
	  cv::Vec4d v4 = 0;

	  std::string executeCatchCvExceptionWorker() {
		  if (self.channels() == 1)
			cv::copyMakeBorder(self, result, top, bottom, left, right, borderType, v1);
		  else if (self.channels() == 2)
			  cv::copyMakeBorder(self, result, top, bottom, left, right, borderType, v2);
		  else if (self.channels() == 3)
			  cv::copyMakeBorder(self, result, top, bottom, left, right, borderType, v3);
		  else if (self.channels() == 4)
			  cv::copyMakeBorder(self, result, top, bottom, left, right, borderType, v4);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  return Mat::Converter::wrap(result);
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  IntConverter::arg(0, &top, info) ||
			  IntConverter::arg(1, &bottom, info) ||
			  IntConverter::arg(2, &left, info) ||
			  IntConverter::arg(3, &right, info)
			);
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  IntConverter::optArg(4, &borderType, info) ||
			  (
				  self.channels() == 1 && DoubleConverter::optArg(5, &v1, info) ||
				  self.channels() == 2 && Vec2::Converter::optArg(5, &v2, info) ||
				  self.channels() == 3 && Vec3::Converter::optArg(5, &v3, info) ||
				  self.channels() == 4 && Vec4::Converter::optArg(5, &v4, info)
				)
			);
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF_ARG_IS_OBJECT(4);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[4]->ToObject();
		  return (
			  IntConverter::optProp(&borderType, "borderType", opts) ||
			  (
				self.channels() == 1 && DoubleConverter::optProp(&v1, "value", opts) ||
				self.channels() == 2 && Vec2::Converter::optProp(&v2, "value", opts) ||
				self.channels() == 3 && Vec3::Converter::optProp(&v3, "value", opts) ||
				self.channels() == 4 && Vec4::Converter::optProp(&v4, "value", opts)
				)
			);
	  }
  };

  struct ReduceWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat self;
	  ReduceWorker(cv::Mat self) {
		  this->self = self;
	  }

	  cv::Mat result;
    int dim;
    int rtype;
    int dtype = -1;

	  std::string executeCatchCvExceptionWorker() {
			cv::reduce(self, result, dim, rtype, dtype);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  return Mat::Converter::wrap(result);
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  IntConverter::arg(0, &dim, info) ||
			  IntConverter::arg(1, &rtype, info)
			);
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  IntConverter::optArg(2, &dtype, info)
			);
	  }
  };

#if CV_VERSION_MINOR > 1
  struct RotateWorker : public OpWithCodeWorker {
  public:
    RotateWorker(cv::Mat self) : OpWithCodeWorker(self) {
    }

    std::string executeCatchCvExceptionWorker() {
      cv::rotate(self, dst, code);
      return "";
    }
  };
#endif


}

#endif
