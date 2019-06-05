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

  class PushBackBinding : public CvBinding {
  public:
	  PushBackBinding(cv::Mat self) {
		  auto mat = req<Mat::Converter>();
		  auto res = ret<Mat::Converter>("res", self);
		  executeBinding = [=]() {
			  res->ref().push_back(mat->ref());
		  };
	  };
  };

  class PopBackBinding : public CvBinding {
  public:
	  PopBackBinding(cv::Mat self) {
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

  class CopyBinding : public CvBinding {
  public:
	  CopyBinding(cv::Mat self) {
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.copyTo(dst->ref(), mask->ref());
		  };
	  };
  };

  class CopyToBinding : public CvBinding {
  public:
	  CopyToBinding(cv::Mat self) {
		  auto dst = req<Mat::Converter>();
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto dstRet = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.copyTo(dst->ref(), mask->ref());
			  dstRet->ref() = dst->ref();
		  };
	  };
  };

  class ConvertToBinding : public CvBinding {
  public:
	  ConvertToBinding(cv::Mat self) {
		  auto rtype = req<FF::IntConverter>();
		  auto alpha = opt<FF::DoubleConverter>("alpha", 1.0);
		  auto beta = opt<FF::DoubleConverter>("beta", 0.0);
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  self.convertTo(dst->ref(), rtype->ref(), alpha->ref(), beta->ref());
		  };
	  };
  };

  class SplitChannelsBinding : public CvBinding {
  public:
	  SplitChannelsBinding(cv::Mat self) {
		  auto mv = ret<Mat::ArrayConverter>("mv");

		  executeBinding = [=]() {
			  cv::split(self, mv->ref());
		  };
	  };
  };

  class AddWeightedBinding : public CvBinding {
  public:
	  AddWeightedBinding(cv::Mat self) {

		  auto alpha = req<FF::DoubleConverter>();
		  auto src2 = req<Mat::Converter>();
		  auto beta = req<FF::DoubleConverter>();
		  auto gamma = req<FF::DoubleConverter>();
		  auto dtype = opt<FF::IntConverter>("dtype" , -1);
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  cv::addWeighted(self, alpha->ref(), src2->ref(), beta->ref(), gamma->ref(), dst->ref(), dtype->ref());
		  };
	  };
  };

  class MinMaxLocBinding : public CvBinding {
  public:
	  MinMaxLocBinding(cv::Mat self) {
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto minVal = ret<FF::DoubleConverter>("minVal");
		  auto maxVal = ret<FF::DoubleConverter>("maxVal");
		  auto minLoc = ret<Point2::WithCastConverter<cv::Point2i>>("minLoc");
		  auto maxLoc = ret<Point2::WithCastConverter<cv::Point2i>>("maxLoc");

		  executeBinding = [=]() {
			  cv::minMaxLoc(self, minVal->ptr(), maxVal->ptr(), minLoc->ptr(), maxLoc->ptr(), mask->ref());
		  };
	  };
  };

  class FindNonZeroBinding : public CvBinding {
  public:
	  FindNonZeroBinding(cv::Mat self) {
		  auto idx = ret<Point2::ArrayWithCastConverter<cv::Point2i>>("idx");

		  executeBinding = [=]() {
			  cv::findNonZero(self, idx->ref());
		  };
	  };
  };

  class CountNonZeroBinding : public CvBinding {
  public:
	  CountNonZeroBinding(cv::Mat self) {
		  auto num = ret<FF::IntConverter>("num");

		  executeBinding = [=]() {
			  num->ref() = cv::countNonZero(self);
		  };
	  };
  };

  class PadToSquareBinding : public CvBinding {
  public:
	  PadToSquareBinding(cv::Mat self) {
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

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &mat2, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::BoolConverter::optArg(1, &dftRows, info) ||
        FF::BoolConverter::optArg(2, &conjB, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::BoolConverter::optProp(&dftRows, "dftRows", opts) ||
        FF::BoolConverter::optProp(&conjB, "conjB", opts)
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

  class SumBinding : public CvBinding {
  public:
	  int channels;
	  cv::Scalar sum;
	  SumBinding(cv::Mat self): channels(self.channels()) {
		  executeBinding = [=]() {
			  sum = cv::sum(self);
		  };
	  };

	  v8::Local<v8::Value> getReturnValue() {
		  switch (channels) {
		  case 1:
			  return FF::DoubleConverter::wrap(sum[0]);
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

  class ConvertScaleAbsBinding : public CvBinding {
  public:
	  ConvertScaleAbsBinding(cv::Mat self) {
		  auto alpha = opt<FF::DoubleConverter>("alpha", 1);
		  auto beta = opt<FF::DoubleConverter>("beta", 0);
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  cv::convertScaleAbs(self, dst->ref(), alpha->ref(), beta->ref());
		  };
	  };
  };

  class GoodFeaturesToTrackBinding : public CvBinding {
  public:
	  GoodFeaturesToTrackBinding(cv::Mat self) {
		  auto maxCorners = req<FF::IntConverter>();
		  auto qualityLevel = req<FF::DoubleConverter>();
		  auto minDistance = req<FF::DoubleConverter>();
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto blockSize = opt<FF::IntConverter>("blockSize", 3);
		  auto gradientSize = opt<FF::IntConverter>("gradientSize", 3);
		  auto useHarrisDetector = opt<FF::BoolConverter>("useHarrisDetector", false);
		  auto harrisK = opt<FF::DoubleConverter>("harrisK", 0.04);
		  auto corners = ret<Point2::ArrayWithCastConverter<cv::Point2f>>("corners");

		  executeBinding = [=]() {

			  cv::goodFeaturesToTrack(
				  self, corners->ref(), maxCorners->ref(), qualityLevel->ref(), minDistance->ref(), mask->ref(), blockSize->ref(),
#if CV_VERSION_MINOR >= 4
				  gradientSize->ref(),
#endif
				  useHarrisDetector->ref(), harrisK->ref()
			  );
		  };
	  };
  };

  class MeanBinding : public CvBinding {
  public:
	  MeanBinding(cv::Mat self) {
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto mean = ret<Vec4::Converter>("mean");

		  executeBinding = [=]() {
			  mean->ref() = cv::mean(self, mask->ref());
		  };
	  };
  };

  class MeanStdDevBinding : public CvBinding {
  public:
	  MeanStdDevBinding(cv::Mat self) {
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto mean = ret<Mat::Converter>("mean");
		  auto stddev = ret<Mat::Converter>("stddev");

		  executeBinding = [=]() {
			  cv::meanStdDev(self, mean->ref(), stddev->ref(), mask->ref());
		  };
	  };
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

  class ReduceBinding : public CvBinding {
  public:
	  ReduceBinding(cv::Mat self) {
		  auto dim = req<FF::IntConverter>();
		  auto rtype = req<FF::IntConverter>();
		  auto dtype = opt<FF::IntConverter>("dtype", -1);
		  auto result = ret<Mat::Converter>("result");

		  executeBinding = [=]() {
			  cv::reduce(self, result->ref(), dim->ref(), rtype->ref(), dtype->ref());
		  };
	  };
  };

  class EigenBinding : public CvBinding {
  public:
	  EigenBinding(cv::Mat self) {
		  auto eigenvalues = ret<Mat::Converter>("eigenvalues");

		  executeBinding = [=]() {
			  cv::eigen(self, eigenvalues->ref());
		  };
	  };
  };

  class SolveBinding : public CvBinding {
  public:
	  SolveBinding(cv::Mat self) {
		  auto mat2 = req<Mat::Converter>();
		  auto flags = opt<FF::IntConverter>("flags", 0);
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  cv::solve(self, mat2->ref(), dst->ref(), flags->ref());
		  };
	  };
  };

  class NormalizeBinding : public CvBinding {
  public:
	  NormalizeBinding(cv::Mat self) {
		  auto alpha = opt<FF::DoubleConverter>("alpha", 1);
		  auto beta = opt<FF::DoubleConverter>("beta", 0);
		  auto normType = opt<FF::IntConverter>("normType", cv::NORM_L2);
		  auto dtype = opt<FF::IntConverter>("dtype", -1);
		  auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
		  auto dst = ret<Mat::Converter>("dst");

		  executeBinding = [=]() {
			  cv::normalize(self, dst->ref(), alpha->ref(), beta->ref(), normType->ref(), dtype->ref(), mask->ref());
		  };
	  };
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
