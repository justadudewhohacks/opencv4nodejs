#include "ParamGrid.h"

Nan::Persistent<v8::FunctionTemplate> ParamGrid::constructor;

NAN_MODULE_INIT(ParamGrid::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(ParamGrid::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString("ParamGrid"));

	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("minVal"), minVal);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("maxVal"), maxVal);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("logStep"), logStep);

	target->Set(FF::newString("ParamGrid"), FF::getFunction(ctor));
};

NAN_METHOD(ParamGrid::New) {
  FF_ASSERT_CONSTRUCT_CALL(ParamGrid);
	FF_METHOD_CONTEXT("ParamGrid::New");
	ParamGrid* self = new ParamGrid();
	if (info.Length() > 0) {
		FF::TryCatch tryCatch;
		if (info.Length() == 1) {
			unsigned int paramId;
			if (UintConverter::arg(0, &paramId, info)) {
				v8::Local<v8::Value> err = tryCatch.formatCatchedError("ParamGrid::New");
				tryCatch.throwNew(err);
				return;
			}
			self->paramGrid = cv::ml::SVM::getDefaultGrid(paramId);
		}
		else {
			double minVal, maxVal, logStep;
			if (
				DoubleConverter::arg(0, &minVal, info) ||
				DoubleConverter::arg(1, &maxVal, info) ||
				DoubleConverter::arg(2, &logStep, info)
			) {
				v8::Local<v8::Value> err = tryCatch.formatCatchedError("ParamGrid::New");
				tryCatch.throwNew(err);
				return;
			}
			self->paramGrid = cv::ml::ParamGrid(minVal, maxVal, logStep);
		}
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};
