#ifdef HAVE_XIMGPROC

#include "SuperpixelLSC.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> SuperpixelLSC::constructor;

NAN_MODULE_INIT(SuperpixelLSC::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelLSC::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SuperpixelLSC").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("img").ToLocalChecked(), SuperpixelLSC::GetImg);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), SuperpixelLSC::GetLabels);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), SuperpixelLSC::GetLabelContourMask);
	Nan::SetAccessor(instanceTemplate, Nan::New("regionSize").ToLocalChecked(), SuperpixelLSC::GetRegionSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("ratio").ToLocalChecked(), SuperpixelLSC::GetRatio);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), SuperpixelLSC::GetNumCalculatedSuperpixels);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelLSC::Iterate);

  Nan::Set(target,Nan::New("SuperpixelLSC").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelLSC::New) {
	FF_ASSERT_CONSTRUCT_CALL(SuperpixelLSC);
	FF::TryCatch tryCatch;
	SuperpixelLSC::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelLSC::New");
		tryCatch.throwNew(err);
		return;
	}

	SuperpixelLSC* self = new SuperpixelLSC();
	self->image = worker.image;
	self->region_size = worker.region_size;
	self->ratio = worker.ratio;
	self->superpixelLsc = cv::ximgproc::createSuperpixelLSC(
		worker.image,
		worker.region_size,
		worker.ratio
	);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelLSC::Iterate) {
	FF::TryCatch tryCatch;

	uint iterations = 10;
	if (FF::IntConverter::optArg(0, &iterations, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelLSC::Iterate");
		tryCatch.throwNew(err);
		return;
	}

	SuperpixelLSC* self = Nan::ObjectWrap::Unwrap<SuperpixelLSC>(info.This());
	self->superpixelLsc->iterate((int)iterations);
	self->superpixelLsc->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelLsc->getNumberOfSuperpixels();
	self->superpixelLsc->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_XIMGPROC
