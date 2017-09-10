#include "macros.h"
#include "BackgroundSubtractor.h"

#ifndef __FF_BACKGROUNDSUBTRACTORMOG2_H__
#define __FF_BACKGROUNDSUBTRACTORMOG2_H__

class BackgroundSubtractorMOG2 : public BackgroundSubtractor {
public:
	cv::Ptr<cv::BackgroundSubtractorMOG2> subtractor;

	static FF_GETTER(BackgroundSubtractorMOG2, GetHistory, subtractor->getHistory());
	static FF_GETTER(BackgroundSubtractorMOG2, GetVarThreshold, subtractor->getVarThreshold());
	static FF_GETTER(BackgroundSubtractorMOG2, GetDetectShadows, subtractor->getDetectShadows());

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return subtractor;
	}
};

#endif