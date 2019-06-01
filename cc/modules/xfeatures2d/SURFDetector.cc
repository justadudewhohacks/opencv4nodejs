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

  Nan::Set(target,Nan::New("SURFDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SURFDetector::New) {
	FF::TryCatch tryCatch("SURFDetector::New");
	SURFDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	SURFDetector* self = new SURFDetector();
	try {
		self->detector = cv::xfeatures2d::SURF::create(
			worker.hessianThreshold,
			worker.nOctaves,
			worker.nOctaveLayers,
			worker.extended,
			worker.upright
		);
	}
	catch (std::exception &e) {
		return tryCatch.throwError(e.what());
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}


#endif // HAVE_XFEATURES2D
