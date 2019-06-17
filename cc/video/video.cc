#include "opencv_modules.h"

#ifdef HAVE_OPENCV_VIDEO

#include "video.h"
#include "BackgroundSubtractorMOG2.h"
#include "BackgroundSubtractorKNN.h"

NAN_MODULE_INIT(Video::Init) {
	BackgroundSubtractorMOG2::Init(target);
	BackgroundSubtractorKNN::Init(target);
};

#endif