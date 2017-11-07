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

  target->Set(Nan::New("SuperpixelSLIC").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SuperpixelSLIC::New) {
	FF_METHOD_CONTEXT("SuperpixelSLIC::New");
	if (!info.IsConstructCall()) {
		FF_THROW("expected new key word");
	}
	SuperpixelSLIC* self = new SuperpixelSLIC();

	FF_ARG_INSTANCE(0, self->img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INT_IFDEF(1, self->algorithm, cv::ximgproc::SLICO);
  FF_ARG_INT_IFDEF(2, self->regionSize, 10);
  FF_ARG_INT_IFDEF(3, self->ruler, 10.0);
	
	self->Wrap(info.Holder());
	self->superpixelSlic = cv::ximgproc::createSuperpixelSLIC(
		self->img,
		self->algorithm, 
		self->regionSize, 
		self->ruler
	);
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelSLIC::Iterate) {
	FF_METHOD_CONTEXT("SuperpixelSLIC::Iterate");

	FF_ARG_UINT_IFDEF(0, uint iterations, 10);

	SuperpixelSLIC* self = FF_UNWRAP(info.This(), SuperpixelSLIC);
	self->superpixelSlic->iterate((int)iterations);
	self->superpixelSlic->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelSlic->getNumberOfSuperpixels();
	self->superpixelSlic->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_XIMGPROC