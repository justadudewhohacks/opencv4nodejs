#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(Partition);
};

#endif