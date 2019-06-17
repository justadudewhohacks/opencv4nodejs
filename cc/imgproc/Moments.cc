#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "Moments.h"
#include <opencv2/imgproc.hpp>

Nan::Persistent<v8::FunctionTemplate> Moments::constructor;

NAN_MODULE_INIT(Moments::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Moments::New);
	Moments::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Moments").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m00"), m00_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m10"), m10_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m01"), m01_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m20"), m20_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m11"), m11_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m02"), m02_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m30"), m30_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m12"), m12_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("m03"), m03_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu20"), mu20_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu11"), mu11_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu02"), mu02_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu30"), mu30_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu21"), mu21_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu12"), mu12_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("mu03"), mu03_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu20"), nu20_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu11"), nu11_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu02"), nu02_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu30"), nu30_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu21"), nu21_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu12"), nu12_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu03"), nu03_getter);

	Nan::SetPrototypeMethod(ctor, "huMoments", HuMoments);

  Nan::Set(target,Nan::New("Moments").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Moments::New) {
	FF::TryCatch tryCatch("Moments::New");
	FF_ASSERT_CONSTRUCT_CALL();
	Moments* self = new Moments();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Moments::HuMoments) {
	std::vector<double> huMoments;
	cv::HuMoments(Moments::unwrapThis(info)->self, huMoments);
	info.GetReturnValue().Set(FF::DoubleArrayConverter::wrap(huMoments));
}

#endif