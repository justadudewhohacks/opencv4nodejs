#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "TermCriteria.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(GetBuildInformation);
	static NAN_METHOD(Partition);
	static NAN_METHOD(Kmeans);
	static NAN_METHOD(CartToPolar);
	static NAN_METHOD(CartToPolarAsync);
	static NAN_METHOD(PolarToCart);
	static NAN_METHOD(PolarToCartAsync);
	static NAN_METHOD(GetNumThreads);
	static NAN_METHOD(SetNumThreads);
	static NAN_METHOD(GetThreadNum);
};

#endif
