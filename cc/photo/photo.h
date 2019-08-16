#include "macros.h"
#include "Mat.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>

#ifndef __FF_PHOTO_H__
#define __FF_PHOTO_H__

class Photo {
public:
	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(FastNlMeansDenoisingColored);
	static NAN_METHOD(FastNlMeansDenoisingColoredAsync);
	static NAN_METHOD(Inpaint);
	static NAN_METHOD(InpaintAsync);
	static NAN_METHOD(SeamlessClone);
	static NAN_METHOD(SeamlessCloneAsync);
};

#endif