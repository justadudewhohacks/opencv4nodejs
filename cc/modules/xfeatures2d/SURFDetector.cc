#ifdef HAVE_XFEATURES2D

#include "SURFDetector.h"

Nan::Persistent<v8::FunctionTemplate> SURFDetector::constructor;

NAN_MODULE_INIT(SURFDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SURFDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SURFDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("hessianThreshold").ToLocalChecked(), SURFDetector::GetHessianThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), SURFDetector::GetNOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), SURFDetector::GetNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), SURFDetector::GetExtended);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), SURFDetector::GetUpright);

  target->Set(Nan::New("SURFDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SURFDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(SURFDetector);
	FF::TryCatch tryCatch;
	SURFDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SURFDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	SURFDetector* self = new SURFDetector();
	self->Wrap(info.Holder());
	self->detector = cv::xfeatures2d::SURF::create(
		worker.hessianThreshold,
		worker.nOctaves,
		worker.nOctaveLayers,
		worker.extended,
		worker.upright
	);
	info.GetReturnValue().Set(info.Holder());
}


#endif // HAVE_XFEATURES2D
