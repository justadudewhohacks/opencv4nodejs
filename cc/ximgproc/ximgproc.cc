#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "ximgproc.h"
#include "SuperpixelSEEDS.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
#include "SuperpixelSLIC.h"
#include "SuperpixelLSC.h"
#endif

NAN_MODULE_INIT(XImgproc::Init) {
	SuperpixelSEEDS::Init(target);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
	SuperpixelSLIC::Init(target);
	SuperpixelLSC::Init(target);
	FF_SET_JS_PROP(target, SLIC, Nan::New<v8::Integer>(cv::ximgproc::SLIC));
	FF_SET_JS_PROP(target, SLICO, Nan::New<v8::Integer>(cv::ximgproc::SLICO));
#endif
}

#endif // HAVE_OPENCV_XIMGPROC