#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_MOMENTS_H__
#define __FF_MOMENTS_H__

class Moments : public Nan::ObjectWrap {
public:
	cv::Moments moments;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	// spatial moments
	static FF_GETTER(Moments, m00, moments.m00);
	static FF_GETTER(Moments, m10, moments.m10);
	static FF_GETTER(Moments, m01, moments.m01);
	static FF_GETTER(Moments, m20, moments.m20);
	static FF_GETTER(Moments, m11, moments.m11);
	static FF_GETTER(Moments, m02, moments.m02);
	static FF_GETTER(Moments, m30, moments.m30);
	static FF_GETTER(Moments, m21, moments.m21);
	static FF_GETTER(Moments, m12, moments.m12);
	static FF_GETTER(Moments, m03, moments.m03);

	// central moments
	static FF_GETTER(Moments, mu20, moments.mu20);
	static FF_GETTER(Moments, mu11, moments.mu11);
	static FF_GETTER(Moments, mu02, moments.mu02);
	static FF_GETTER(Moments, mu30, moments.mu30);
	static FF_GETTER(Moments, mu21, moments.mu21);
	static FF_GETTER(Moments, mu12, moments.mu12);
	static FF_GETTER(Moments, mu03, moments.mu03);

	// central normalized  moments
	static FF_GETTER(Moments, nu20, moments.nu20);
	static FF_GETTER(Moments, nu11, moments.nu11);
	static FF_GETTER(Moments, nu02, moments.nu02);
	static FF_GETTER(Moments, nu30, moments.nu30);
	static FF_GETTER(Moments, nu21, moments.nu21);
	static FF_GETTER(Moments, nu12, moments.nu12);
	static FF_GETTER(Moments, nu03, moments.nu03);

	static NAN_METHOD(HuMoments);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Moments* getNativeObjectPtr() { return &moments; }
	cv::Moments getNativeObject() { return moments; }

	typedef InstanceConverter<Moments, cv::Moments> Converter;

	static const char* getClassName() {
		return "Moments";
	}
};

#endif