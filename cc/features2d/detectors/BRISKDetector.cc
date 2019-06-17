#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BRISKDetector.h"

Nan::Persistent<v8::FunctionTemplate> BRISKDetector::constructor;

NAN_MODULE_INIT(BRISKDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BRISKDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("BRISKDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("thresh").ToLocalChecked(), thresh_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("octaves").ToLocalChecked(), octaves_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("patternScale").ToLocalChecked(), patternScale_getter);

  Nan::Set(target,Nan::New("BRISKDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(BRISKDetector::New) {
	FF::TryCatch tryCatch("BRISKDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	BRISKDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	BRISKDetector* self = new BRISKDetector();
	self->thresh = worker.thresh;
	self->octaves = worker.octaves;
	self->patternScale = worker.patternScale;
	self->self = cv::BRISK::create(self->thresh, self->octaves, (float)self->patternScale);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

#endif