#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(Partition);
	static NAN_METHOD(Kmeans);

	struct CartToPolarWorker;
	static NAN_METHOD(CartToPolar);
	static NAN_METHOD(CartToPolarAsync);

	struct PolarToCartWorker;
	static NAN_METHOD(PolarToCart);
	static NAN_METHOD(PolarToCartAsync);
    
    static NAN_METHOD(GetMemMetrics);
    
};

#endif