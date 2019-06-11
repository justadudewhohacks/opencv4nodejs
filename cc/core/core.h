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

	static NAN_METHOD(AddWeighted);
	static NAN_METHOD(AddWeightedAsync);
	static NAN_METHOD(MinMaxLoc);
	static NAN_METHOD(MinMaxLocAsync);
	static NAN_METHOD(FindNonZero);
	static NAN_METHOD(FindNonZeroAsync);
	static NAN_METHOD(CountNonZero);
	static NAN_METHOD(CountNonZeroAsync);
	static NAN_METHOD(PadToSquare);
	static NAN_METHOD(PadToSquareAsync);
};

#endif
