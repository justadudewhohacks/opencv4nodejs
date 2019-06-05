#include "core.h"
#include "CvBinding.h"

#ifndef __FF_COREBINDINGS_H__
#define __FF_COREBINDINGS_H__

namespace CoreBindings {

	class CartToPolarBinding : public CvBinding {
	public:
		CartToPolarBinding() {
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

	class PolarToCartBinding : public CvBinding {
	public:
		PolarToCartBinding() {
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

}

#endif