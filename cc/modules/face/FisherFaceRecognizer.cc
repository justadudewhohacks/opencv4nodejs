#ifdef HAVE_FACE

#include "FisherFaceRecognizer.h"
#include "FaceRecognizerBindings.h"

Nan::Persistent<v8::FunctionTemplate> FisherFaceRecognizer::constructor;

NAN_MODULE_INIT(FisherFaceRecognizer::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(FisherFaceRecognizer::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FaceRecognizer::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("FisherFaceRecognizer").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(Nan::New("FisherFaceRecognizer").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(FisherFaceRecognizer::New) {
	FF::TryCatch tryCatch;
	FaceRecognizerBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("FisherFaceRecognizer::New");
		tryCatch.throwNew(err);
		return;
	}

	FisherFaceRecognizer* self = new FisherFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_MINOR < 3
	self->faceRecognizer = cv::face::createFisherFaceRecognizer(worker.num_components, worker.threshold);
#else
	self->faceRecognizer = cv::face::FisherFaceRecognizer::create(worker.num_components, worker.threshold);
#endif
	FF_RETURN(info.Holder());
};

#endif