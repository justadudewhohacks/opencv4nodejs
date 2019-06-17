#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelSEEDS.h"

Nan::Persistent<v8::FunctionTemplate> SuperpixelSEEDS::constructor;

NAN_MODULE_INIT(SuperpixelSEEDS::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelSEEDS::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SuperpixelSEEDS").ToLocalChecked());


	Nan::SetAccessor(instanceTemplate, Nan::New("image").ToLocalChecked(), image_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), labels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), labelContourMask_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("num_superpixels").ToLocalChecked(), num_superpixels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("num_levels").ToLocalChecked(), num_levels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("prior").ToLocalChecked(), prior_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("histogram_bins").ToLocalChecked(), histogram_bins_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("double_step").ToLocalChecked(), double_step_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), numCalculatedSuperpixels_getter);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelSEEDS::Iterate);

  Nan::Set(target,Nan::New("SuperpixelSEEDS").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelSEEDS::New) {
	FF::TryCatch tryCatch("SuperpixelSEEDS::New");
	FF_ASSERT_CONSTRUCT_CALL();
	SuperpixelSEEDS::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	SuperpixelSEEDS* self = new SuperpixelSEEDS();
	self->image = worker.img;
	self->num_superpixels = worker.num_superpixels;
	self->num_levels = worker.num_levels;
	self->prior = worker.prior;
	self->histogram_bins = worker.histogram_bins;
	self->double_step = worker.double_step;

	self->self = cv::ximgproc::createSuperpixelSEEDS(
		worker.img.cols,
		worker.img.rows,
		worker.img.channels(),
		worker.num_superpixels,
		worker.num_levels,
		worker.prior,
		worker.histogram_bins,
		worker.double_step
	);
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelSEEDS::Iterate) {
	FF::TryCatch tryCatch("SuperpixelSEEDS::Iterate");

	uint iterations = 4;
	if (FF::UintConverter::optArg(0, &iterations, info)) {
		return tryCatch.reThrow();
	}

	SuperpixelSEEDS* self = Nan::ObjectWrap::Unwrap<SuperpixelSEEDS>(info.This());
	self->self->iterate(self->image, (int)iterations);
	self->self->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->self->getNumberOfSuperpixels();
	self->self->getLabelContourMask(self->labelContourMask);
}

#endif // HAVE_OPENCV_XIMGPROC
