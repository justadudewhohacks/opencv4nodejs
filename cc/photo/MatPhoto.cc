#include "opencv_modules.h"

#ifdef HAVE_OPENCV_PHOTO

#include "MatPhoto.h"
#include "photoBindings.h"

void MatPhoto::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "seamlessClone", SeamlessClone);
  Nan::SetPrototypeMethod(ctor, "seamlessCloneAsync", SeamlessCloneAsync);
};

NAN_METHOD(MatPhoto::SeamlessClone) {
	Mat::syncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

NAN_METHOD(MatPhoto::SeamlessCloneAsync) {
	Mat::asyncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

#endif