#include "core.h"
#include "CvBinding.h"

#ifndef __FF_COREBINDINGS_H__
#define __FF_COREBINDINGS_H__

namespace CoreBindings {

	class CartToPolar : public CvBinding {
	public:
		void setup() {
			auto x = req<Mat::Converter>();
			auto y = req<Mat::Converter>();
			auto angleInDegrees = opt<FF::BoolConverter>("angleInDegrees", false);
			auto magnitude = ret<Mat::Converter>("magnitude");
			auto angle = ret<Mat::Converter>("angle");

			executeBinding = [=]() {
				cv::cartToPolar(x->ref(), y->ref(), magnitude->ref(), angle->ref(), angleInDegrees->ref());
			};
		};
	};

	class PolarToCart : public CvBinding {
	public:
		void setup() {
			auto magnitude = req<Mat::Converter>();
			auto angle = req<Mat::Converter>();
			auto angleInDegrees = opt<FF::BoolConverter>("angleInDegrees", false);
			auto x = ret<Mat::Converter>("x");
			auto y = ret<Mat::Converter>("y");

			executeBinding = [=]() {
				cv::polarToCart(magnitude->ref(), angle->ref(), x->ref(), y->ref(), angleInDegrees->ref());
			};
		};
	};

	/* Mat Core Class Methods */

	class AddWeighted : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto alpha = req<FF::DoubleConverter>();
			auto src2 = req<Mat::Converter>();
			auto beta = req<FF::DoubleConverter>();
			auto gamma = req<FF::DoubleConverter>();
			auto dtype = opt<FF::IntConverter>("dtype", -1);
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::addWeighted(self->ref(), alpha->ref(), src2->ref(), beta->ref(), gamma->ref(), dst->ref(), dtype->ref());
			};
		};
	};

	class MinMaxLoc : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
			auto minVal = ret<FF::DoubleConverter>("minVal");
			auto maxVal = ret<FF::DoubleConverter>("maxVal");
			auto minLoc = ret<Point2::WithCastConverter<cv::Point2i>>("minLoc");
			auto maxLoc = ret<Point2::WithCastConverter<cv::Point2i>>("maxLoc");

			executeBinding = [=]() {
				cv::minMaxLoc(self->ref(), minVal->ptr(), maxVal->ptr(), minLoc->ptr(), maxLoc->ptr(), mask->ref());
			};
		};
	};

	class FindNonZero : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto idx = ret<Point2::ArrayWithCastConverter<cv::Point2i>>("idx");

			executeBinding = [=]() {
				cv::findNonZero(self->ref(), idx->ref());
			};
		};
	};

	class CountNonZero : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto num = ret<FF::IntConverter>("num");

			executeBinding = [=]() {
				num->ref() = cv::countNonZero(self->ref());
			};
		};
	};

	class Split : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mv = ret<Mat::ArrayConverter>("mv");

			executeBinding = [=]() {
				cv::split(self->ref(), mv->ref());
			};
		};
	};

	class MulSpectrums : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mat2 = req<Mat::Converter>();
			auto flags = req<FF::IntConverter>();
			auto conjB = opt<FF::BoolConverter>("conjB", false);
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::mulSpectrums(self->ref(), mat2->ref(), dst->ref(), flags->ref(), conjB->ref());
			};
		};
	};

	class Transform : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto m = req<Mat::Converter>();
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::transform(self->ref(), dst->ref(), m->ref());
			};
		};
	};

	class PerspectiveTransform : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto m = req<Mat::Converter>();
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::perspectiveTransform(self->ref(), dst->ref(), m->ref());
			};
		};
	};

	class Sum : public CvClassMethodBinding<Mat> {
	public:
		std::shared_ptr<FF::Value<cv::Mat>> self;
		cv::Scalar sum;
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			this->self = self;
			executeBinding = [=]() {
				sum = cv::sum(self->ref());
			};
		};

		v8::Local<v8::Value> getReturnValue() {
			switch (self->ref().channels()) {
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

	class ConvertScaleAbs : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto alpha = opt<FF::DoubleConverter>("alpha", 1);
			auto beta = opt<FF::DoubleConverter>("beta", 0);
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::convertScaleAbs(self->ref(), dst->ref(), alpha->ref(), beta->ref());
			};
		};
	};

	class Mean : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
			auto mean = ret<Vec4::Converter>("mean");

			executeBinding = [=]() {
				mean->ref() = cv::mean(self->ref(), mask->ref());
			};
		};
	};

	class MeanStdDev : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
			auto mean = ret<Mat::Converter>("mean");
			auto stddev = ret<Mat::Converter>("stddev");

			executeBinding = [=]() {
				cv::meanStdDev(self->ref(), mean->ref(), stddev->ref(), mask->ref());
			};
		};
	};

	class Reduce : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto dim = req<FF::IntConverter>();
			auto rtype = req<FF::IntConverter>();
			auto dtype = opt<FF::IntConverter>("dtype", -1);
			auto result = ret<Mat::Converter>("result");

			executeBinding = [=]() {
				cv::reduce(self->ref(), result->ref(), dim->ref(), rtype->ref(), dtype->ref());
			};
		};
	};

	class Eigen : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto eigenvalues = ret<Mat::Converter>("eigenvalues");

			executeBinding = [=]() {
				cv::eigen(self->ref(), eigenvalues->ref());
			};
		};
	};

	class Solve : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto mat2 = req<Mat::Converter>();
			auto flags = opt<FF::IntConverter>("flags", 0);
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::solve(self->ref(), mat2->ref(), dst->ref(), flags->ref());
			};
		};
	};

	class Normalize : public CvClassMethodBinding<Mat> {
	public:
		void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
			auto alpha = opt<FF::DoubleConverter>("alpha", 1);
			auto beta = opt<FF::DoubleConverter>("beta", 0);
			auto normType = opt<FF::IntConverter>("normType", cv::NORM_L2);
			auto dtype = opt<FF::IntConverter>("dtype", -1);
			auto mask = opt<Mat::Converter>("mask", cv::noArray().getMat());
			auto dst = ret<Mat::Converter>("dst");

			executeBinding = [=]() {
				cv::normalize(self->ref(), dst->ref(), alpha->ref(), beta->ref(), normType->ref(), dtype->ref(), mask->ref());
			};
		};
	};

}

#endif