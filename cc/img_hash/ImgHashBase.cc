#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "ImgHashBase.h"
#include "ImgHashBaseBindings.h"


void ImgHashBase::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "compare", Compare);
  Nan::SetPrototypeMethod(ctor, "compareAsync", CompareAsync);
  Nan::SetPrototypeMethod(ctor, "compute", Compute);
  Nan::SetPrototypeMethod(ctor, "computeAsync", ComputeAsync);
};

NAN_METHOD(ImgHashBase::Compare) {
  FF::executeSyncBinding(
    std::make_shared<ImgHashBaseBindings::CompareWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
    "ImgHashBase::Compare",
    info
  );
}

NAN_METHOD(ImgHashBase::CompareAsync) {
  FF::executeAsyncBinding(
    std::make_shared<ImgHashBaseBindings::CompareWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
    "ImgHashBase::CompareAsync",
    info
  );
}

NAN_METHOD(ImgHashBase::Compute) {
	FF::executeSyncBinding(
		std::make_shared<ImgHashBaseBindings::ComputeWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
		"ImgHashBase::Compute",
		info
	);
}

NAN_METHOD(ImgHashBase::ComputeAsync) {
	FF::executeAsyncBinding(
		std::make_shared<ImgHashBaseBindings::ComputeWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
		"ImgHashBase::ComputeAsync",
		info
	);
}


#endif
