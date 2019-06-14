#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_MOMENTS_H__
#define __FF_MOMENTS_H__

class Moments : public FF::ObjectWrap<Moments, cv::Moments> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Moments";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	// spatial moments
	FF_ACCESSORS(m00, FF::DoubleConverter);
	FF_ACCESSORS(m10, FF::DoubleConverter);
	FF_ACCESSORS(m01, FF::DoubleConverter);
	FF_ACCESSORS(m20, FF::DoubleConverter);
	FF_ACCESSORS(m11, FF::DoubleConverter);
	FF_ACCESSORS(m02, FF::DoubleConverter);
	FF_ACCESSORS(m30, FF::DoubleConverter);
	FF_ACCESSORS(m21, FF::DoubleConverter);
	FF_ACCESSORS(m12, FF::DoubleConverter);
	FF_ACCESSORS(m03, FF::DoubleConverter);

	// central moments
	FF_ACCESSORS(mu20, FF::DoubleConverter);
	FF_ACCESSORS(mu11, FF::DoubleConverter);
	FF_ACCESSORS(mu02, FF::DoubleConverter);
	FF_ACCESSORS(mu30, FF::DoubleConverter);
	FF_ACCESSORS(mu21, FF::DoubleConverter);
	FF_ACCESSORS(mu12, FF::DoubleConverter);
	FF_ACCESSORS(mu03, FF::DoubleConverter);

	// central normalized  moments
	FF_ACCESSORS(nu20, FF::DoubleConverter);
	FF_ACCESSORS(nu11, FF::DoubleConverter);
	FF_ACCESSORS(nu02, FF::DoubleConverter);
	FF_ACCESSORS(nu30, FF::DoubleConverter);
	FF_ACCESSORS(nu21, FF::DoubleConverter);
	FF_ACCESSORS(nu12, FF::DoubleConverter);
	FF_ACCESSORS(nu03, FF::DoubleConverter);

	static NAN_METHOD(HuMoments);
};

#endif