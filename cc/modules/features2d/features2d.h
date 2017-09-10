#include "macros.h"

#ifndef __FF_FEATURES2D_H__
#define __FF_FEATURES2D_H__

class Features2d {
public:
  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(DrawKeyPoints);
	static NAN_METHOD(DrawMatches);
};

#endif