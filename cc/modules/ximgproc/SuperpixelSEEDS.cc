#ifdef HAVE_XIMGPROC

#include "SuperpixelSEEDS.h"

Nan::Persistent<v8::FunctionTemplate> SuperpixelSEEDS::constructor;

NAN_MODULE_INIT(SuperpixelSEEDS::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SuperpixelSEEDS::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SuperpixelSEEDS").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("img").ToLocalChecked(), SuperpixelSEEDS::GetImg);
	Nan::SetAccessor(instanceTemplate, Nan::New("numSuperpixels").ToLocalChecked(), SuperpixelSEEDS::GetNumSuperpixels);
	Nan::SetAccessor(instanceTemplate, Nan::New("numLevels").ToLocalChecked(), SuperpixelSEEDS::GeNumLevels);
	Nan::SetAccessor(instanceTemplate, Nan::New("prior").ToLocalChecked(), SuperpixelSEEDS::GetPrior);
	Nan::SetAccessor(instanceTemplate, Nan::New("histogramBins").ToLocalChecked(), SuperpixelSEEDS::GetHistogramBins);
	Nan::SetAccessor(instanceTemplate, Nan::New("doubleStep").ToLocalChecked(), SuperpixelSEEDS::GetDoubleStep);
	Nan::SetAccessor(instanceTemplate, Nan::New("numCalculatedSuperpixels").ToLocalChecked(), SuperpixelSEEDS::GetNumCalculatedSuperpixels);
	Nan::SetAccessor(instanceTemplate, Nan::New("labels").ToLocalChecked(), SuperpixelSEEDS::GetLabels);
	Nan::SetAccessor(instanceTemplate, Nan::New("labelContourMask").ToLocalChecked(), SuperpixelSEEDS::GetLabelContourMask);

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelSEEDS::Iterate);

  Nan::Set(target,Nan::New("SuperpixelSEEDS").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SuperpixelSEEDS::New) {
	FF_ASSERT_CONSTRUCT_CALL(SuperpixelSEEDS);
	FF::TryCatch tryCatch;
	SuperpixelSEEDS::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelSEEDS::New");
		tryCatch.throwNew(err);
		return;
	}

	SuperpixelSEEDS* self = new SuperpixelSEEDS();
	self->img = worker.img;
	self->num_superpixels = worker.num_superpixels;
	self->num_levels = worker.num_levels;
	self->prior = worker.prior;
	self->histogram_bins = worker.histogram_bins;
	self->double_step = worker.double_step;

	self->superpixelSeeds = cv::ximgproc::createSuperpixelSEEDS(
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
	FF::TryCatch tryCatch;

	uint iterations = 4;
	if (UFF::IntConverter::optArg(0, &iterations, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SuperpixelSEEDS::Iterate");
		tryCatch.throwNew(err);
		return;
	}

	SuperpixelSEEDS* self = Nan::ObjectWrap::Unwrap<SuperpixelSEEDS>(info.This());
	self->superpixelSeeds->iterate(self->img, (int)iterations);
	self->superpixelSeeds->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelSeeds->getNumberOfSuperpixels();
	self->superpixelSeeds->getLabelContourMask(self->labelContourMask);
}

#endif // HAVE_XIMGPROC
