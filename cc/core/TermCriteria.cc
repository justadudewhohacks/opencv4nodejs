#include "TermCriteria.h"

Nan::Persistent<v8::FunctionTemplate> TermCriteria::constructor;

NAN_MODULE_INIT(TermCriteria::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TermCriteria::New);
	TermCriteria::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(FF::newString("TermCriteria"));
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("type"), type_getter, type_setter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("maxCount"), maxCount_getter, maxCount_setter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("epsilon"), epsilon_getter, epsilon_setter);

  Nan::Set(target,FF::newString("TermCriteria"), FF::getFunction(ctor));
};

NAN_METHOD(TermCriteria::New) {
	FF::TryCatch tryCatch("TermCriteria::New");
	FF_ASSERT_CONSTRUCT_CALL();
	TermCriteria* self = new TermCriteria();

	if (info.Length() > 0) {
		int type, maxCount;
		double epsilon;
		if (
			FF::IntConverter::arg(0, &type, info) ||
			FF::IntConverter::arg(1, &maxCount, info) ||
			FF::DoubleConverter::arg(2, &epsilon, info)
		) {
			return tryCatch.reThrow();
		}
		self->self = cv::TermCriteria(type, maxCount, epsilon);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
