#include "macros.h"
#include "CustomMatAllocator.h"

#ifndef __FF_EXTERNALMEMTRACKING_H__
#define __FF_EXTERNALMEMTRACKING_H__

class ExternalMemTracking {
public:

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
	static CustomMatAllocator *custommatallocator;
#endif

	static inline void onMatAllocated() {
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
		if (custommatallocator != NULL) {
			custommatallocator->FixupJSMem();
		}
#endif
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(IsCustomMatAllocatorEnabled);
	static NAN_METHOD(GetMemMetrics);
	static NAN_METHOD(DangerousEnableCustomMatAllocator);
	static NAN_METHOD(DangerousDisableCustomMatAllocator);

};

#endif