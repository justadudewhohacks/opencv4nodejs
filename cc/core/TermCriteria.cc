#include "TermCriteria.h"

Nan::Persistent<v8::FunctionTemplate> TermCriteria::constructor;

NAN_MODULE_INIT(TermCriteria::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TermCriteria::New);
	TermCriteria::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(FF::newString("TermCriteria"));
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("type"), TermCriteria::GetType);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("maxCount"), TermCriteria::GetMaxCount);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("epsilon"), TermCriteria::GetEpsilon);

  Nan::Set(target,FF::newString("TermCriteria"), FF::getFunction(ctor));
};

NAN_METHOD(TermCriteria::New) {
	FF_ASSERT_CONSTRUCT_CALL(TermCriteria);
	TermCriteria* self = new TermCriteria();

	if (info.Length() > 0) {
		FF::TryCatch tryCatch;
		int type, maxCount;
		double epsilon;
		if (
			IntConverter::arg(0, &type, info) ||
			IntConverter::arg(1, &maxCount, info) ||
			DoubleConverter::arg(2, &epsilon, info)
		) {
			tryCatch.throwNew(tryCatch.formatCatchedError("TermCriteria::New"));
			return;
		}
		self->termCriteria = cv::TermCriteria(type, maxCount, epsilon);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
