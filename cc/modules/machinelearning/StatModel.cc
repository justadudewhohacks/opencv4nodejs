#include "StatModel.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> StatModel::constructor;

NAN_MODULE_INIT(StatModel::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(StatModel::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("StatModel").ToLocalChecked());

	target->Set(Nan::New("StatModel").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(StatModel::New) {
	StatModel* self = new StatModel();
	/*
	self->svm = cv::ml::StatModel::create()
	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("StatModel::New");
		Nan::TryCatch tryCatch;
		self->setParams(args);
		if (tryCatch.HasCaught()) {
			tryCatch.ReThrow();
		}
	}
	*/
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};