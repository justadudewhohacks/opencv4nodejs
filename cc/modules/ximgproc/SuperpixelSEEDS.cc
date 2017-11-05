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

  target->Set(Nan::New("SuperpixelSEEDS").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SuperpixelSEEDS::New) {
	FF_METHOD_CONTEXT("SuperpixelSEEDS::New");
	if (!info.IsConstructCall()) {
		FF_THROW("expected new key word");
	}
	SuperpixelSEEDS* self = new SuperpixelSEEDS();

	FF_ARG_INSTANCE(0, self->img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INT(1, self->numSuperpixels);
	FF_ARG_INT(2, self->numLevels);
	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, self->prior, "prior", 2);
	FF_GET_INT_IFDEF(optArgs, self->histogramBins, "histogramBins", 5);
	FF_GET_BOOL_IFDEF(optArgs, self->doubleStep, "doubleStep", false);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, self->prior, self->prior);
		FF_ARG_INT_IFDEF(4, self->histogramBins, self->histogramBins);
		FF_ARG_BOOL_IFDEF(5, self->doubleStep, self->doubleStep);
	}
	self->Wrap(info.Holder());
	self->superpixelSeeds = cv::ximgproc::createSuperpixelSEEDS(
		self->img.cols,
		self->img.rows,
		self->img.channels(),
		self->numSuperpixels, 
		self->numLevels, 
		self->prior, 
		self->histogramBins, 
		self->doubleStep
	);
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelSEEDS::Iterate) {
	FF_METHOD_CONTEXT("SuperpixelSEEDS::Iterate");

	FF_ARG_UINT_IFDEF(0, uint iterations, 4);

	SuperpixelSEEDS* self = FF_UNWRAP(info.This(), SuperpixelSEEDS);
	self->superpixelSeeds->iterate(self->img, (int)iterations);
	self->superpixelSeeds->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelSeeds->getNumberOfSuperpixels();
	self->superpixelSeeds->getLabelContourMask(self->labelContourMask);
}

#endif // HAVE_XIMGPROC