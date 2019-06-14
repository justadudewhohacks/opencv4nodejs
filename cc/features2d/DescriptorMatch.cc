#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "DescriptorMatch.h"

Nan::Persistent<v8::FunctionTemplate> DescriptorMatch::constructor;

NAN_MODULE_INIT(DescriptorMatch::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DescriptorMatch::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("DescriptorMatch").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("queryIdx").ToLocalChecked(), queryIdx_getter, queryIdx_setter);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("trainIdx").ToLocalChecked(), trainIdx_getter, trainIdx_setter);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("distance").ToLocalChecked(), distance_getter, distance_setter);

	Nan::Set(target,Nan::New("DescriptorMatch").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(DescriptorMatch::New) {
	FF::TryCatch tryCatch("DescriptorMatch::New");
	FF_ASSERT_CONSTRUCT_CALL();
	DescriptorMatch* self = new DescriptorMatch();
	if (info.Length() > 0) {
		int queryIdx, trainIdx;
		double distance;
		if (
			FF::IntConverter::arg(0, &queryIdx, info) ||
			FF::IntConverter::arg(1, &trainIdx, info) ||
			FF::DoubleConverter::arg(2, &distance, info)
			) {
			return tryCatch.reThrow();
		}
		self->self = cv::DMatch(queryIdx, trainIdx, distance);
	}
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

#endif
