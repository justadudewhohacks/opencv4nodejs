#include "ExternalMemTracking.h"
#include <iostream>

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
CustomMatAllocator *ExternalMemTracking::custommatallocator = NULL;
#endif

NAN_MODULE_INIT(ExternalMemTracking::Init) {
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
	try {
		char* env = std::getenv("OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING");
		if (env == NULL && custommatallocator == NULL) {
			custommatallocator = new CustomMatAllocator();
			cv::Mat::setDefaultAllocator(custommatallocator);
		}
	}
	catch (...) {
		printf("ExternalMemTracking::Init - fatal exception while trying to read env: OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING");
	}
#endif  
	Nan::SetMethod(target, "isCustomMatAllocatorEnabled", IsCustomMatAllocatorEnabled);
	Nan::SetMethod(target, "dangerousEnableCustomMatAllocator", DangerousEnableCustomMatAllocator);
	Nan::SetMethod(target, "dangerousDisableCustomMatAllocator", DangerousDisableCustomMatAllocator);
	Nan::SetMethod(target, "getMemMetrics", GetMemMetrics);
};

NAN_METHOD(ExternalMemTracking::GetMemMetrics) {

  int64_t TotalAlloc = -1;
  int64_t TotalKnownByJS = -1;
  int64_t NumAllocations = -1;
  int64_t NumDeAllocations = -1;

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  if (ExternalMemTracking::custommatallocator != NULL){
    TotalAlloc = ExternalMemTracking::custommatallocator->readtotalmem();
    TotalKnownByJS = ExternalMemTracking::custommatallocator->readmeminformed();
    NumAllocations = ExternalMemTracking::custommatallocator->readnumallocated();
    NumDeAllocations = ExternalMemTracking::custommatallocator->readnumdeallocated();
  }
#endif

  v8::Local<v8::Object> result = Nan::New<v8::Object>();
  Nan::Set(result, FF::newString("TotalAlloc"), Nan::New((double)TotalAlloc));
  Nan::Set(result, FF::newString("TotalKnownByJS"), Nan::New((double)TotalKnownByJS));
  Nan::Set(result, FF::newString("NumAllocations"), Nan::New((double)NumAllocations));
  Nan::Set(result, FF::newString("NumDeAllocations"), Nan::New((double)NumDeAllocations));

  info.GetReturnValue().Set(result);
  return;
}


NAN_METHOD(ExternalMemTracking::IsCustomMatAllocatorEnabled) {
    bool allocatorOn = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
    if (ExternalMemTracking::custommatallocator != NULL){
		allocatorOn = true;
    }
#endif
    info.GetReturnValue().Set(allocatorOn);
}

NAN_METHOD(ExternalMemTracking::DangerousEnableCustomMatAllocator) {
	bool success = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
	if (ExternalMemTracking::custommatallocator == NULL) {
		ExternalMemTracking::custommatallocator = new CustomMatAllocator();
		cv::Mat::setDefaultAllocator(ExternalMemTracking::custommatallocator);
	}
	success = ExternalMemTracking::custommatallocator != NULL;
#endif
	info.GetReturnValue().Set(success);
}

NAN_METHOD(ExternalMemTracking::DangerousDisableCustomMatAllocator) {
	bool success = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
	if (ExternalMemTracking::custommatallocator != NULL) {
		CustomMatAllocator *allocator = ExternalMemTracking::custommatallocator;

		// return default allocator
		if (allocator->variables) {
			allocator->variables->MemTotalChangeMutex.lock();
		}
		cv::Mat::setDefaultAllocator(NULL);
		ExternalMemTracking::custommatallocator = NULL;
		if (allocator->variables) {
			allocator->variables->MemTotalChangeMutex.unlock();
		}

		// sorry, can't delete it, since it may be references by a number of outstanding Mats -> memory leak, but it's small
		// and should not happen often, or ever!.
		//delete allocator;
	}
	success = ExternalMemTracking::custommatallocator == NULL;
#endif
	info.GetReturnValue().Set(success);
}

