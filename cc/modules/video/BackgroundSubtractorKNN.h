#include "macros.h"
#include "BackgroundSubtractor.h"

#ifndef __FF_BACKGROUNDSUBTRACTORKNN_H__
#define __FF_BACKGROUNDSUBTRACTORKNN_H__

class BackgroundSubtractorKNN : public BackgroundSubtractor {
public:
	cv::Ptr<cv::BackgroundSubtractorKNN> subtractor;

	static FF_GETTER(BackgroundSubtractorKNN, GetHistory, subtractor->getHistory());
	static FF_GETTER(BackgroundSubtractorKNN, GetDist2Threshold, subtractor->getDist2Threshold());
	static FF_GETTER(BackgroundSubtractorKNN, GetDetectShadows, subtractor->getDetectShadows());

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return subtractor;
	}
};

#endif