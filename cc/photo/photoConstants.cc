#include "opencv_modules.h"

#ifdef HAVE_OPENCV_PHOTO

#include "photoConstants.h"

using namespace cv;

void PhotoConstants::Init(v8::Local<v8::Object> target) {
	FF_SET_CV_CONSTANT(target, INPAINT_NS);
	FF_SET_CV_CONSTANT(target, INPAINT_TELEA);
}

#endif