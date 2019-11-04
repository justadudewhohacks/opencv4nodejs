#include "imgproc.h"
#include "CvBinding.h"
#include <opencv2/imgproc.hpp>

#ifndef __FF_IMGPROCBINDINGS_H_
#define __FF_IMGPROCBINDINGS_H_

namespace ImgprocBindings {

  struct GetTextSizeWorker : public CatchCvExceptionWorker {
  public:
    std::string text;
    int fontFace;
    double fontScale;
    int thickness;

    cv::Size2d returnValue;
    int baseLine;

    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::getTextSize(text, fontFace, fontScale, thickness, &baseLine);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("size").ToLocalChecked(), Size::Converter::wrap(returnValue));
      Nan::Set(ret, Nan::New("baseLine").ToLocalChecked(), FF::IntConverter::wrap(baseLine));
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::StringConverter::arg(0, &text, info) ||
        FF::IntConverter::arg(1, &fontFace, info) ||
        FF::DoubleConverter::arg(2, &fontScale, info) ||
        FF::IntConverter::arg(3, &thickness, info)
      );
    }
  };

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  struct CannyWorker : public CatchCvExceptionWorker {
  public:

	  cv::Mat dx;
	  cv::Mat dy;
	  double threshold1;
	  double threshold2;
	  bool L2gradient = false;

	  cv::Mat returnValue;

	  std::string executeCatchCvExceptionWorker() {
		  cv::Canny(dx, dy, returnValue, threshold1, threshold2, L2gradient);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  return Mat::Converter::wrap(returnValue);
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  Mat::Converter::arg(0, &dx, info) ||
			  Mat::Converter::arg(1, &dy, info) ||
			  FF::DoubleConverter::arg(2, &threshold1, info) ||
			  FF::DoubleConverter::arg(3, &threshold2, info)
			  );
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  FF::BoolConverter::optArg(4, &L2gradient, info)
			  );
	  }
  };
#endif

  struct ApplyColorMapWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat src;
    cv::Mat dst;
    cv::Mat userColor;
    int colormap;
    bool useUserColor = 0;

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
      if (info[1]->IsNumber()) {
        return (Mat::Converter::arg(0, &src, info) ||
                FF::IntConverter::optArg(1, &colormap, info));
      }

      useUserColor = 1;

      return (Mat::Converter::arg(0, &src, info) ||
              Mat::Converter::arg(1, &userColor, info));
#else
	  return (Mat::Converter::arg(0, &src, info) ||
		  FF::IntConverter::optArg(1, &colormap, info));
#endif
    }

    std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
      if (useUserColor) {
        cv::applyColorMap(src, dst, userColor);
      } else {
        cv::applyColorMap(src, dst, colormap);
      }
#else
	  cv::applyColorMap(src, dst, colormap);
#endif
      return "";
    }

    v8::Local<v8::Value> getReturnValue() { return Mat::Converter::wrap(dst); }
  };

#if CV_VERSION_LOWER_THAN(4, 0, 0)
  // since 4.0.0 cv::undistortPoints has been moved from imgproc to calib3d
  class UndistortPoints : public CvBinding {
  public:
	  void setup() {
		  auto srcPoints = req<Point2::ArrayWithCastConverter<cv::Point2f>>();
		  auto cameraMatrix = req<Mat::Converter>();
		  auto distCoeffs = req<Mat::Converter>();
		  auto destPoints = ret<Point2::ArrayWithCastConverter<cv::Point2f>>("destPoints");

		  executeBinding = [=]() {
			  cv::undistortPoints(srcPoints->ref(), destPoints->ref(), cameraMatrix->ref(), distCoeffs->ref(), cameraMatrix->ref());
		  };
	  };
  };
#endif

  class GoodFeaturesToTrack : public CvClassMethodBinding<Mat> {
  public:
	  void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
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
				  self->ref(), corners->ref(), maxCorners->ref(), qualityLevel->ref(), minDistance->ref(), mask->ref(), blockSize->ref(),
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
				  gradientSize->ref(),
#endif
				  useHarrisDetector->ref(), harrisK->ref()
			  );
		  };
	  };
  };

  class Blur : public CvClassMethodBinding<Mat> {
  public:
	  void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
		  auto kSize = req<Size::Converter>();
		  auto anchor = opt<Point2::Converter>("anchor", cv::Point2d());
		  auto borderType = opt<FF::IntConverter>("borderType", cv::BORDER_CONSTANT);
		  auto blurMat = ret<Mat::Converter>("blurMat");

		  executeBinding = [=]() {
			  cv::blur(self->ref(), blurMat->ref(), kSize->ref(), anchor->ref(), borderType->ref());
		  };
	  };

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 1) && !Point2::hasInstance(info[1]);
	  }
  };

  class GaussianBlur : public CvClassMethodBinding<Mat> {
  public:
	  void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
		  auto kSize = req<Size::Converter>();
		  auto sigmaX = req<FF::DoubleConverter>();
		  auto sigmaY = opt<FF::DoubleConverter>("sigmaY", 0);
		  auto borderType = opt<FF::IntConverter>("borderType", cv::BORDER_CONSTANT);
		  auto blurMat = ret<Mat::Converter>("blurMat");

		  executeBinding = [=]() {
			  cv::GaussianBlur(self->ref(), blurMat->ref(), kSize->ref(), sigmaX->ref(), sigmaY->ref(), borderType->ref());
		  };
	  };
  };

  class MedianBlur : public CvClassMethodBinding<Mat> {
  public:
	  void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
		  auto kSize = req<FF::IntConverter>();
		  auto blurMat = ret<Mat::Converter>("blurMat");

		  executeBinding = [=]() {
			  cv::medianBlur(self->ref(), blurMat->ref(), kSize->ref());
		  };
	  };
  };

	class Accumulate : public CvBinding {
	public:
		void setup() {
			auto src = req<Mat::Converter>();
			auto dst = req<Mat::Converter>();
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
			executeBinding = [=]() {
				auto depth = dst->ref().depth();
				if (depth != CV_32F && depth != CV_64F)
					throw std::runtime_error("dst must has a depth of CV_32F or CV_64F");
				cv::accumulate(src->ref(), dst->ref(), mask->ref());
			};
		};
	};

	class AccumulateProduct : public CvBinding {
	public:
		void setup() {
			auto src1 = req<Mat::Converter>();
			auto src2 = req<Mat::Converter>();
			auto dst = req<Mat::Converter>();
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());

			executeBinding = [=]() {
				auto depth = dst->ref().depth();
				if (depth != CV_32F && depth != CV_64F)
					throw std::runtime_error("dst must has a depth of CV_32F or CV_64F");
				cv::accumulateProduct(src1->ref(), src2->ref(), dst->ref(), mask->ref());
			};
		};
	};

	class AccumulateSquare : public CvBinding {
	public:
		void setup() {
			auto src = req<Mat::Converter>();
			auto dst = req<Mat::Converter>();
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());

			executeBinding = [=]() {
				auto depth = dst->ref().depth();
				if (depth != CV_32F && depth != CV_64F)
					throw std::runtime_error("dst must has a depth of CV_32F or CV_64F");
				cv::accumulateSquare(src->ref(), dst->ref(), mask->ref());
			};
		};
	};

	class AccumulateWeighted : public CvBinding {
	public:
		void setup() {
			auto src = req<Mat::Converter>();
			auto dst = req<Mat::Converter>();
			auto alpha = req<FF::DoubleConverter>();
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());

			executeBinding = [=]() {
				auto depth = dst->ref().depth();
				if (depth != CV_32F && depth != CV_64F)
					throw std::runtime_error("dst must has a depth of CV_32F or CV_64F");
				cv::accumulateWeighted(src->ref(), dst->ref(), alpha->ref(), mask->ref());
			};
		};
	};

  class CalcHist : public CvBinding {
  public:
    void setup() {

      auto src = req<Mat::Converter>();
      auto jsHistAxes = req<HistAxes::ArrayConverter>();
      auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
      auto retHist = ret<Mat::Converter>("hist");

      executeBinding = [=]() {
        auto histAxes = jsHistAxes->ref();
        auto img = src->ref();
        cv::MatND hist;

        const int dims = histAxes.size();

        auto **ranges = new float*[dims];
        int *channels = new int[dims];
        int *bins = new int[dims];

        for (int i = 0; i < dims; i++) {
          auto entry = histAxes.at(i);
          ranges[i] = new float[2];
          ranges[i][0] = entry.range[0];
          ranges[i][1] = entry.range[1];
          channels[i] = entry.channel;
          bins[i] = entry.bins;
        }

        cv::calcHist(
            &img,
            1,
            channels,
            mask->ref(),
            hist,
            dims,
            bins,
            (const float **)(ranges),
            true,
            false
        );

        for (int i = 0; i < dims; ++i) {
          delete[] ranges[i];
        }
        delete[] ranges;
        delete[] channels;
        delete[] bins;

        int outputType = CV_MAKETYPE(CV_64F, img.channels());
        if (outputType != hist.type()) {
          hist.convertTo(hist, outputType);
        }

        retHist->ref() = hist;
      };
    }
  };
}

#endif