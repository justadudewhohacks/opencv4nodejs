#include "macros.h"
#include <opencv2/tracking.hpp>
#include "Mat.h"
#include "Rect.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_MULTITRACKER_H__
#define __FF_MULTITRACKER_H__

class MultiTracker : public Nan::ObjectWrap {
public:
	cv::MultiTracker tracker;

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(AddMIL);
	static NAN_METHOD(AddBOOSTING);
	static NAN_METHOD(AddMEDIANFLOW);
	static NAN_METHOD(AddTLD);
	static NAN_METHOD(AddKCF);
	static NAN_METHOD(AddMOSSE);
	static NAN_METHOD(AddCSRT);
	static NAN_METHOD(Update);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif

#endif