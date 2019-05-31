#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/objdetect.hpp>
#include "Point.h"

#ifndef __FF_DETECTIONROI_H__
#define __FF_DETECTIONROI_H__

class DetectionROI : public FF::ObjectWrap<DetectionROI, cv::DetectionROI> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "DetectionROI";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(DetectionROI, scaleGet, self.scale);
	static FF_SETTER_NUMBER(DetectionROI, scale, self.scale);

	static NAN_GETTER(locationsGet) {
		v8::Local<v8::Value> val = Point2::ArrayWithCastConverter<cv::Point2i>::wrap(unwrapSelf(info).locations);
		info.GetReturnValue().Set(val);
	}

	static NAN_SETTER(locationsSet) {
		std::vector<cv::Point> locations;
		if (Point2::ArrayWithCastConverter<cv::Point2i>::unwrapTo(&locations, value)) {
			return Nan::ThrowError("expected locations to be an Array of type Point2");
		}
		DetectionROI::unwrapThis(info)->self.locations = locations;
	}

	static NAN_GETTER(confidencesGet) {
		info.GetReturnValue().Set(FF::DoubleArrayConverter::wrap(unwrapSelf(info).confidences));
	}

	static NAN_SETTER(confidencesSet) {
		std::vector<double> confidences;
		if (FF::DoubleArrayConverter::unwrapTo(&confidences, value)) {
			return Nan::ThrowError("expected confidences to be an Array of type Number");
		}
		DetectionROI::unwrapThis(info)->self.confidences = confidences;
	}
};

#endif