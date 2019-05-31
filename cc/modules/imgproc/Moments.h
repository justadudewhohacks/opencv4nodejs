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
	static FF_GETTER(Moments, m00, self.m00);
	static FF_GETTER(Moments, m10, self.m10);
	static FF_GETTER(Moments, m01, self.m01);
	static FF_GETTER(Moments, m20, self.m20);
	static FF_GETTER(Moments, m11, self.m11);
	static FF_GETTER(Moments, m02, self.m02);
	static FF_GETTER(Moments, m30, self.m30);
	static FF_GETTER(Moments, m21, self.m21);
	static FF_GETTER(Moments, m12, self.m12);
	static FF_GETTER(Moments, m03, self.m03);

	// central moments
	static FF_GETTER(Moments, mu20, self.mu20);
	static FF_GETTER(Moments, mu11, self.mu11);
	static FF_GETTER(Moments, mu02, self.mu02);
	static FF_GETTER(Moments, mu30, self.mu30);
	static FF_GETTER(Moments, mu21, self.mu21);
	static FF_GETTER(Moments, mu12, self.mu12);
	static FF_GETTER(Moments, mu03, self.mu03);

	// central normalized  moments
	static FF_GETTER(Moments, nu20, self.nu20);
	static FF_GETTER(Moments, nu11, self.nu11);
	static FF_GETTER(Moments, nu02, self.nu02);
	static FF_GETTER(Moments, nu30, self.nu30);
	static FF_GETTER(Moments, nu21, self.nu21);
	static FF_GETTER(Moments, nu12, self.nu12);
	static FF_GETTER(Moments, nu03, self.nu03);

	static NAN_METHOD(HuMoments);
};

#endif