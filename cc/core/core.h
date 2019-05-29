#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "TermCriteria.h"
#include "FeatureSet.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>

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

	// CUDA core
	static NAN_METHOD(DeviceSupports);
    static NAN_METHOD(GetCudaEnabledDeviceCount);
    static NAN_METHOD(GetDevice);
    static NAN_METHOD(PrintCudaDeviceInfo);
    static NAN_METHOD(PrintShortCudaDeviceInfo);
    static NAN_METHOD(ResetDevice);
    static NAN_METHOD(SetDevice);
};

#endif
