#ifdef HAVE_XIMGPROC

#include "ximgproc.h"
#include "SuperpixelSEEDS.h"

#if CV_MINOR_VERSION > 0
#include "SuperpixelSLIC.h"
#include "SuperpixelLSC.h"
#endif

NAN_MODULE_INIT(XImgproc::Init) {
	SuperpixelSEEDS::Init(target);
#if CV_MINOR_VERSION > 0
	SuperpixelSLIC::Init(target);
	SuperpixelLSC::Init(target);
	FF_SET_JS_PROP(target, SLIC, Nan::New<v8::Integer>(cv::ximgproc::SLIC));
	FF_SET_JS_PROP(target, SLICO, Nan::New<v8::Integer>(cv::ximgproc::SLICO));
#endif
}

#endif // HAVE_XIMGPROC