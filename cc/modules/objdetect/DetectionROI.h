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
		FF_VAL val = ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(Converter::unwrap(info.This()).locations);
		FF_RETURN(val);
	}

	static NAN_SETTER(locationsSet) {
		std::vector<cv::Point> locations;
		if (ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::unwrap(&locations, value)) {
			return Nan::ThrowError("expected locations to be an Array of type Point2");
		}
		Converter::unwrapPtr(info.This())->locations = locations;
	}

	static NAN_GETTER(confidencesGet) {
		FF_RETURN(DoubleArrayConverter::wrap(Converter::unwrap(info.This()).confidences));
	}

	static NAN_SETTER(confidencesSet) {
		std::vector<double> confidences;
		if (DoubleArrayConverter::unwrap(&confidences, value)) {
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