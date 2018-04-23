#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>

#ifndef __FF_PHOTOCONSTANTS_H__
#define __FF_PHOTOCONSTANTS_H__

class PhotoConstants {
public:
	static void Init(v8::Local<v8::Object> target);
};

#endif //__FF_PHOTOCONSTANTS_H__
