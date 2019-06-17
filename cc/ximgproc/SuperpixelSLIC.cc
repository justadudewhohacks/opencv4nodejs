#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelSLIC.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Nan::Persistent<v8::FunctionTemplate> SuperpixelSLIC::constructor;

NAN_MODULE_INIT(SuperpixelSLIC::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelSLIC::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
	constructor.Reset(ctor);
	instanceTemplate->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("SuperpixelSLIC").ToLocalChecked());


	Nan::SetAccessor(instanceTemplate, Nan::New("image").ToLocalChecked(), image_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), labels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), labelContourMask_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), numCalculatedSuperpixels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("algorithm").ToLocalChecked(), algorithm_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("region_size").ToLocalChecked(), region_size_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("ruler").ToLocalChecked(), ruler_getter);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelSLIC::Iterate);

	Nan::Set(target,Nan::New("SuperpixelSLIC").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelSLIC::New) {
	FF::TryCatch tryCatch("SuperpixelSLIC::New");
	FF_ASSERT_CONSTRUCT_CALL();
	SuperpixelSLIC::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	SuperpixelSLIC* self = new SuperpixelSLIC();
	self->image = worker.image;
	self->algorithm = worker.algorithm;
	self->region_size = worker.region_size;
	self->ruler = worker.ruler;
	self->superpixelSlic = cv::ximgproc::createSuperpixelSLIC(
		worker.image,
		worker.algorithm,
		worker.region_size,
		worker.ruler
	);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelSLIC::Iterate) {
	FF::TryCatch tryCatch("SuperpixelSLIC::Iterate");

	uint iterations = 10;
	if (FF::UintConverter::optArg(0, &iterations, info)) {
		return tryCatch.reThrow();
	}

	SuperpixelSLIC* self = Nan::ObjectWrap::Unwrap<SuperpixelSLIC>(info.This());
	self->superpixelSlic->iterate((int)iterations);
	self->superpixelSlic->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelSlic->getNumberOfSuperpixels();
	self->superpixelSlic->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_OPENCV_XIMGPROC
