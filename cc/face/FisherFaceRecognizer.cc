#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

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

	Nan::Set(target,Nan::New("FisherFaceRecognizer").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FisherFaceRecognizer::New) {
	FF::TryCatch tryCatch("FisherFaceRecognizer::New");
	FF_ASSERT_CONSTRUCT_CALL();
	FaceRecognizerBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	FisherFaceRecognizer* self = new FisherFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->faceRecognizer = cv::face::FisherFaceRecognizer::create(worker.num_components, worker.threshold);
#else
	self->faceRecognizer = cv::face::createFisherFaceRecognizer(worker.num_components, worker.threshold);
#endif
	info.GetReturnValue().Set(info.Holder());
};

#endif
