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

  target->Set(Nan::New("SuperpixelLSC").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SuperpixelLSC::New) {
	FF_METHOD_CONTEXT("SuperpixelLSC::New");
	if (!info.IsConstructCall()) {
		FF_THROW("expected new key word");
	}
	SuperpixelLSC* self = new SuperpixelLSC();

	FF_ARG_INSTANCE(0, self->img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
  FF_ARG_INT_IFDEF(1, self->regionSize, 10);
  FF_ARG_INT_IFDEF(2, self->ratio, 0.075);

	self->Wrap(info.Holder());
	self->superpixelLsc = cv::ximgproc::createSuperpixelLSC(
		self->img,
		self->regionSize, 
		self->ratio
	);
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelLSC::Iterate) {
	FF_METHOD_CONTEXT("SuperpixelLSC::Iterate");

	FF_ARG_UINT_IFDEF(0, uint iterations, 10);

	SuperpixelLSC* self = FF_UNWRAP(info.This(), SuperpixelLSC);
	self->superpixelLsc->iterate((int)iterations);
	self->superpixelLsc->getLabels(self->labels);
	self->numCalculatedSuperpixels = self->superpixelLsc->getNumberOfSuperpixels();
	self->superpixelLsc->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_XIMGPROC