#include "Moments.h"
#include "opencv2/imgproc.hpp"

Nan::Persistent<v8::FunctionTemplate> Moments::constructor;

NAN_MODULE_INIT(Moments::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Moments::New);
	Moments::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Moments").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m00"), Moments::m00);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m10"), Moments::m10);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m01"), Moments::m01);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m20"), Moments::m20);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m11"), Moments::m11);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m02"), Moments::m02);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m30"), Moments::m30);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m12"), Moments::m12);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("m03"), Moments::m03);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu20"), Moments::mu20);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu11"), Moments::mu11);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu02"), Moments::mu02);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu30"), Moments::mu30);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu21"), Moments::mu21);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu12"), Moments::mu12);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("mu03"), Moments::mu03);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu20"), Moments::nu20);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu11"), Moments::nu11);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu02"), Moments::nu02);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu30"), Moments::nu30);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu21"), Moments::nu21);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu12"), Moments::nu12);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu03"), Moments::nu03);

	Nan::SetPrototypeMethod(ctor, "huMoments", HuMoments);

  target->Set(Nan::New("Moments").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Moments::New) {
	Moments* self = new Moments();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Moments::HuMoments) {
	FF_METHOD_CONTEXT("Moments::HuMoments");
	std::vector<double> huMoments;
	cv::HuMoments(FF_UNWRAP(info.This(), Moments)->moments, huMoments);
	FF_PACK_ARRAY(jsHuMoments, huMoments);
	FF_RETURN(jsHuMoments);
}