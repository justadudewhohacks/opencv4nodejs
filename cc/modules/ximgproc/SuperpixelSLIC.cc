#ifdef HAVE_XIMGPROC

#include "SuperpixelSLIC.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> SuperpixelSLIC::constructor;

NAN_MODULE_INIT(SuperpixelSLIC::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelSLIC::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SuperpixelSLIC").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("img").ToLocalChecked(), SuperpixelSLIC::GetImg);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), SuperpixelSLIC::GetLabels);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), SuperpixelSLIC::GetLabelContourMask);
	Nan::SetAccessor(instanceTemplate, Nan::New("algorithm").ToLocalChecked(), SuperpixelSLIC::GetAlgorithm);
	Nan::SetAccessor(instanceTemplate, Nan::New("regionSize").ToLocalChecked(), SuperpixelSLIC::GetRegionSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("ruler").ToLocalChecked(), SuperpixelSLIC::GetRuler);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), SuperpixelSLIC::GetNumCalculatedSuperpixels);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelSLIC::Iterate);

  target->Set(Nan::New("SuperpixelSLIC").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelSLIC::New) {
	FF_ASSERT_CONSTRUCT_CALL(SuperpixelSLIC);
	FF::TryCatch tryCatch;
	SuperpixelSLIC::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelSLIC::New");
		tryCatch.throwNew(err);
		return;
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
	FF::TryCatch tryCatch;

	uint iterations = 10;
	if (UintConverter::optArg(0, &iterations, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelSLIC::Iterate");
		tryCatch.throwNew(err);
		return;
	}

	SuperpixelSLIC* self = Nan::ObjectWrap::Unwrap<SuperpixelSLIC>(info.This());
	self->superpixelSlic->iterate((int)iterations);
	self->superpixelSlic->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelSlic->getNumberOfSuperpixels();
	self->superpixelSlic->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_XIMGPROC
