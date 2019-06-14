#include "imgproc.h"

#ifndef __FF_CONTOURBINDINGS_H_
#define __FF_CONTOURBINDINGS_H_

namespace ContourBindings {

	struct ApproxPolyDPWorker : public CatchCvExceptionWorker {
	public:
		std::vector<cv::Point2i> self;
		ApproxPolyDPWorker(std::vector<cv::Point2i>  self) {
			this->self = self;
		}

		double epsilon;
		bool closed;
		std::vector<cv::Point2i> curve;
		std::string executeCatchCvExceptionWorker() {
			cv::approxPolyDP(self, curve, epsilon, closed);
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			return Point2::ArrayWithCastConverter<cv::Point2i>::wrap(curve);
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::DoubleConverter::arg(0, &epsilon, info) ||
				FF::BoolConverter::arg(1, &closed, info)
			);
		}
	};
}
#endif
