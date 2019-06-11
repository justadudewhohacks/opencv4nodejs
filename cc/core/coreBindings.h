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

}

#endif