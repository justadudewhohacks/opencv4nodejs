#include "Mat.h"
#include "CvBinding.h"

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

    v8::Local<v8::Value> getReturnValue() {
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
          return (FF::DoubleConverter::arg(0, &newVal1, info));
          break;
      }
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(1, &mask, info)
      );
    }
  };

  class PushBack : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto mat = req<Mat::Converter>();
		  auto res = ret<Mat::Converter>("res", self);
		  executeBinding = [=]() {
			  res->ref().push_back(mat->ref());
		  };
	  };
  };

  class PopBack : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto num = opt<FF::IntConverter>("num", 1);
		  auto res = ret<Mat::Converter>("res", self);
		  executeBinding = [=]() {
			  res->ref().pop_back(num->ref());
		  };
	  };
  };

  struct GetDataWorker : CatchCvExceptionWorker {
  public:
    cv::Mat mat;

    GetDataWorker(cv::Mat mat) {
      this->mat = mat;
    }

    size_t size;
    char *data;

    cv::Size sizeTotal;
    cv::Point ofs;

    std::string executeCatchCvExceptionWorker() {
      size = mat.rows * mat.cols * mat.elemSize();
      mat.locateROI(sizeTotal, ofs);
      
      if(sizeTotal.width != mat.cols || sizeTotal.height != mat.rows){
        return "Cannot call GetData when Region of Interest is defined (i.e. after getRegion) use matrix.copyTo to copy ROI to a new matrix";
      }
      data = static_cast<char *>(malloc(size));
      memcpy(data, mat.data, size);
      return "";
    }

    static void freeBufferCallback(char* data, void* hint) {
      free(data);
    }

    v8::Local<v8::Value> getReturnValue() {
      return Nan::NewBuffer(data, size, freeBufferCallback, 0).ToLocalChecked();
    }
  };

  class Copy : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.copyTo(dst->ref(), mask->ref());
		  };
	  };
  };

  class CopyTo : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto dst = req<Mat::Converter>();
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto dstRet = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.copyTo(dst->ref(), mask->ref());
			  dstRet->ref() = dst->ref();
		  };
	  };
  };

  class ConvertTo : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto rtype = req<FF::IntConverter>();
		  auto alpha = opt<FF::DoubleConverter>("alpha", 1.0);
		  auto beta = opt<FF::DoubleConverter>("beta", 0.0);
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.convertTo(dst->ref(), rtype->ref(), alpha->ref(), beta->ref());
		  };
	  };
  };

  class PadToSquare : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto fillVec = opt<Vec3::Converter>("fillVec", cv::Vec3d());
		  auto out = ret<Mat::Converter>("out");

		  executeBinding = [=]() {
			  int maxDim = (std::max)(self.cols, self.rows);
			  out->ref() = cv::Mat(maxDim, maxDim, self.type(), (cv::Vec3b)fillVec->ref());

			  int offX = 0, offY = 0;
			  if (self.cols > self.rows) {
				  offY = (self.cols - self.rows) / 2;
			  }
			  else {
				  offX = (self.rows - self.cols) / 2;
			  }
			  cv::Mat roi = out->ref()(cv::Rect(offX, offY, self.cols, self.rows));
			  self.copyTo(roi);
		  };
	  };
  };

  // TODO
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

    v8::Local<v8::Value> getReturnValue() {
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
      return FF::IntConverter::optArg(0, &flags, info);
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
        FF::IntConverter::optArg(0, &flags, info) ||
        FF::IntConverter::optArg(1, &nonzeroRows, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 0);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::IntConverter::optProp(&flags, "flags", opts) ||
        FF::IntConverter::optProp(&nonzeroRows, "nonzeroRows", opts)
      );
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
        FF::IntConverter::arg(0, &code, info)
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
			  FF::IntConverter::arg(0, &top, info) ||
			  FF::IntConverter::arg(1, &bottom, info) ||
			  FF::IntConverter::arg(2, &left, info) ||
			  FF::IntConverter::arg(3, &right, info)
			);
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  FF::IntConverter::optArg(4, &borderType, info) ||
			  (
				  (self.channels() == 1 && FF::DoubleConverter::optArg(5, &v1, info)) ||
				  (self.channels() == 2 && Vec2::Converter::optArg(5, &v2, info)) ||
				  (self.channels() == 3 && Vec3::Converter::optArg(5, &v3, info)) ||
				  (self.channels() == 4 && Vec4::Converter::optArg(5, &v4, info))
				)
			);
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 4);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		  return (
			  FF::IntConverter::optProp(&borderType, "borderType", opts) ||
			  (
				(self.channels() == 1 && FF::DoubleConverter::optProp(&v1, "value", opts)) ||
				(self.channels() == 2 && Vec2::Converter::optProp(&v2, "value", opts)) ||
				(self.channels() == 3 && Vec3::Converter::optProp(&v3, "value", opts)) ||
				(self.channels() == 4 && Vec4::Converter::optProp(&v4, "value", opts))
				)
			);
	  }
  };

  
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
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
