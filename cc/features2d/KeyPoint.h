#include "macros.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "Point2.h"

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

class KeyPoint : public FF::ObjectWrap<KeyPoint, cv::KeyPoint> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "KeyPoint";
	}

	int localId = -1;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	FF_GETTER_CUSTOM(localId, FF::IntConverter, localId);
	FF_ACCESSORS(pt, Point2::Converter);
	FF_ACCESSORS(angle, FF::FloatConverter);
	FF_ACCESSORS(class_id, FF::IntConverter);
	FF_ACCESSORS(response, FF::FloatConverter);
	FF_ACCESSORS(size, FF::FloatConverter);
	FF_ACCESSORS(octave, FF::IntConverter);
};

#endif