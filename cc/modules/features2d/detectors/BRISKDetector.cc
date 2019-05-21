#include "BRISKDetector.h"

Nan::Persistent<v8::FunctionTemplate> BRISKDetector::constructor;

NAN_MODULE_INIT(BRISKDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BRISKDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("BRISKDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("thresh").ToLocalChecked(), BRISKDetector::GetThresh);
	Nan::SetAccessor(instanceTemplate, Nan::New("octaves").ToLocalChecked(), BRISKDetector::GetOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("patternScale").ToLocalChecked(), BRISKDetector::GetPatternScale);

  Nan::Set(target,Nan::New("BRISKDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(BRISKDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(BFMatcher);
	FF::TryCatch tryCatch;
	BRISKDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("BFMatcher::New");
		tryCatch.throwNew(err);
		return;
	}

	BRISKDetector* self = new BRISKDetector();
	self->thresh = worker.thresh;
	self->octaves = worker.octaves;
	self->patternScale = worker.patternScale;
	self->detector = cv::BRISK::create(self->thresh, self->octaves, (float)self->patternScale);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}