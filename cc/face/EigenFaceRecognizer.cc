#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

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

	Nan::Set(target,Nan::New("EigenFaceRecognizer").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(EigenFaceRecognizer::New) {
	FF::TryCatch tryCatch("EigenFaceRecognizer::New");
	FF_ASSERT_CONSTRUCT_CALL();
	FaceRecognizerBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	EigenFaceRecognizer* self = new EigenFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->faceRecognizer = cv::face::EigenFaceRecognizer::create(worker.num_components, worker.threshold);
#else
	self->faceRecognizer = cv::face::createEigenFaceRecognizer(worker.num_components, worker.threshold);
#endif
	info.GetReturnValue().Set(info.Holder());
};

#endif
