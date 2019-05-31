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

	static NAN_GETTER(GetPoint) {
		info.GetReturnValue().Set(Point2::Converter::wrap(unwrapSelf(info).pt));
	}
	static FF_GETTER(KeyPoint, GetLocalId, localId);
	static FF_GETTER(KeyPoint, GetAngle, self.angle);
	static FF_GETTER(KeyPoint, GetClassId, self.class_id);
	static FF_GETTER(KeyPoint, GetResponse, self.response);
	static FF_GETTER(KeyPoint, GetSize, self.size);
	static FF_GETTER(KeyPoint, GetOctave, self.octave);
};

#endif