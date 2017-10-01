#include "TermCriteria.h"

Nan::Persistent<v8::FunctionTemplate> TermCriteria::constructor;

NAN_MODULE_INIT(TermCriteria::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TermCriteria::New);
	TermCriteria::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(FF_NEW_STRING("TermCriteria"));
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("type"), TermCriteria::GetType);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("maxCount"), TermCriteria::GetMaxCount);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("epsilon"), TermCriteria::GetEpsilon);

  target->Set(FF_NEW_STRING("TermCriteria"), ctor->GetFunction());
};

NAN_METHOD(TermCriteria::New) {
	FF_METHOD_CONTEXT("TermCriteria::New");
	TermCriteria* self = new TermCriteria();
	if (info.Length() > 0) {
		FF_ARG_INT(0, int type);
		FF_ARG_INT(1, int maxCount);
		FF_ARG_NUMBER(2, double epsilon);
		self->termCriteria = cv::TermCriteria(type, maxCount, epsilon);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}