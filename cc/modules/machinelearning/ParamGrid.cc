#include "ParamGrid.h"

Nan::Persistent<v8::FunctionTemplate> ParamGrid::constructor;

NAN_MODULE_INIT(ParamGrid::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(ParamGrid::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_NEW_STRING("ParamGrid"));

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("minVal"), minVal);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("maxVal"), maxVal);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("logStep"), logStep);

	target->Set(FF_NEW_STRING("ParamGrid"), ctor->GetFunction());
};

NAN_METHOD(ParamGrid::New) {
	FF_METHOD_CONTEXT("ParamGrid::New");
	ParamGrid* self = new ParamGrid();
	if (info.Length() > 0) {
		if (info.Length() == 1) {
			FF_ARG_UINT(0, unsigned int paramId);
			self->paramGrid = cv::ml::SVM::getDefaultGrid(paramId);
		}
		else {
			FF_ARG_NUMBER(0, double minVal);
			FF_ARG_NUMBER(1, double maxVal);
			FF_ARG_NUMBER(2, double logStep);
			self->paramGrid = cv::ml::ParamGrid(minVal, maxVal, logStep);
		}
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};