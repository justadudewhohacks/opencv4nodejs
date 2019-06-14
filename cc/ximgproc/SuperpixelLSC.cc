#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelLSC.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Nan::Persistent<v8::FunctionTemplate> SuperpixelLSC::constructor;

NAN_MODULE_INIT(SuperpixelLSC::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelLSC::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SuperpixelLSC").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("image").ToLocalChecked(), image_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), labels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), labelContourMask_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("region_size").ToLocalChecked(), region_size_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("ratio").ToLocalChecked(), ratio_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), numCalculatedSuperpixels_getter);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelLSC::Iterate);

  Nan::Set(target,Nan::New("SuperpixelLSC").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelLSC::New) {
	FF::TryCatch tryCatch("SuperpixelLSC::New");
	FF_ASSERT_CONSTRUCT_CALL();
	SuperpixelLSC::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	SuperpixelLSC* self = new SuperpixelLSC();
	self->image = worker.image;
	self->region_size = worker.region_size;
	self->ratio = worker.ratio;
	self->self = cv::ximgproc::createSuperpixelLSC(
		worker.image,
		worker.region_size,
		worker.ratio
	);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelLSC::Iterate) {
	FF::TryCatch tryCatch("SuperpixelLSC::Iterate");

	uint iterations = 10;
	if (FF::UintConverter::optArg(0, &iterations, info)) {
		return tryCatch.reThrow();
	}

	SuperpixelLSC* self = Nan::ObjectWrap::Unwrap<SuperpixelLSC>(info.This());
	self->self->iterate((int)iterations);
	self->self->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->self->getNumberOfSuperpixels();
	self->self->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_OPENCV_XIMGPROC
