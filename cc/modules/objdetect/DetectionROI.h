#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/objdetect.hpp>
#include "Point.h"

#ifndef __FF_DETECTIONROI_H__
#define __FF_DETECTIONROI_H__

class DetectionROI : public Nan::ObjectWrap {
public:
	cv::DetectionROI detectionROI;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(DetectionROI, scaleGet, detectionROI.scale);
	static FF_SETTER_NUMBER(DetectionROI, scale, detectionROI.scale);
	static NAN_GETTER(locationsGet) {
		v8::Local<v8::Value> val = Point2::ArrayWithCastConverter<cv::Point2i>::wrap(unwrapSelf(info).locations);
		info.GetReturnValue().Set(val);
	}

	static NAN_SETTER(locationsSet) {
		std::vector<cv::Point> locations;
		if (Point2::ArrayWithCastConverter<cv::Point2i>::unwrapTo(&locations, value)) {
			return Nan::ThrowError("expected locations to be an Array of type Point2");
		}
		Converter::unwrapPtr(info.This())->locations = locations;
	}

	static NAN_GETTER(confidencesGet) {
		info.GetReturnValue().Set(FF::DoubleArrayConverter::wrap(unwrapSelf(info).confidences));
	}

	static NAN_SETTER(confidencesSet) {
		std::vector<double> confidences;
		if (FF::DoubleArrayConverter::unwrapTo(&confidences, value)) {
			return Nan::ThrowError("expected confidences to be an Array of type Number");
		}
		Converter::unwrapPtr(info.This())->confidences = confidences;
	}

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::DetectionROI* getNativeObjectPtr() { return &detectionROI; }
	cv::DetectionROI getNativeObject() { return detectionROI; }

	typedef InstanceConverter<DetectionROI, cv::DetectionROI> Converter;

	static const char* getClassName() {
		return "DetectionROI";
	}
};

#endif