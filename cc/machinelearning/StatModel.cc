#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "StatModel.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> StatModel::constructor;

NAN_MODULE_INIT(StatModel::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(StatModel::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("StatModel").ToLocalChecked());

	Nan::Set(target,Nan::New("StatModel").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(StatModel::New) {
	FF::TryCatch tryCatch("StatModel::New");
	FF_ASSERT_CONSTRUCT_CALL();
	StatModel* self = new StatModel();

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
