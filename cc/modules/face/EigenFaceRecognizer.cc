#ifdef HAVE_FACE

#include "EigenFaceRecognizer.h"
#include "FaceRecognizerBindings.h"

Nan::Persistent<v8::FunctionTemplate> EigenFaceRecognizer::constructor;

NAN_MODULE_INIT(EigenFaceRecognizer::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(EigenFaceRecognizer::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FaceRecognizer::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("EigenFaceRecognizer").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(Nan::New("EigenFaceRecognizer").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(EigenFaceRecognizer::New) {
	FF::TryCatch tryCatch;
	FaceRecognizerBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("EigenFaceRecognizer::New");
		tryCatch.throwNew(err);
		return;
	}

	EigenFaceRecognizer* self = new EigenFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_MINOR < 3
		self->faceRecognizer = cv::face::createEigenFaceRecognizer(worker.num_components, worker.threshold);
#else
		self->faceRecognizer = cv::face::EigenFaceRecognizer::create(worker.num_components, worker.threshold);
#endif
	FF_RETURN(info.Holder());
};

#endif