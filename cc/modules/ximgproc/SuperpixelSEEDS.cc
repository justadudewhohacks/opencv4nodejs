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

	Nan::SetPrototypeMethod(ctor, "iterate", SuperpixelSEEDS::Iterate);

  target->Set(Nan::New("SuperpixelSEEDS").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SuperpixelSEEDS::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("SuperpixelSEEDS::New expected new key word");
	}
	if (!info[0]->IsObject()) {
		// TODO usage messages
		return Nan::ThrowError(FF_V8STRING("SuperpixelSEEDS::New - args object required"));
	}
	SuperpixelSEEDS* self = new SuperpixelSEEDS();
	v8::Local<v8::Object> args = info[0]->ToObject();
	v8::Local<v8::Object> _jsImg;
	FF_GET_JSPROP_REQUIRED(args, _jsImg, img, ToObject);
	// TODO check if Mat is passed
	Mat* img = Nan::ObjectWrap::Unwrap<Mat>(_jsImg);
	self->jsImg.Reset(img->persistent());

	if (img->mat.cols < 1 || img->mat.rows < 1 || img->mat.channels() > 3) {
		return Nan::ThrowError(FF_V8STRING("SuperpixelSEEDS::New - empty image"));
	}

	Mat* _jsLabels = Nan::ObjectWrap::Unwrap<Mat>(Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked());
	self->jsLabels.Reset(_jsLabels->persistent());

	FF_GET_TYPECHECKED_JSPROP_REQUIRED(args, self->numSuperpixels, numSuperpixels, IsInt32, Int32Value);
	FF_GET_TYPECHECKED_JSPROP_REQUIRED(args, self->numLevels, numLevels, IsInt32, Int32Value);
	FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->prior, prior, IsInt32, Int32Value);
	FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->histogramBins, histogramBins, IsInt32, Int32Value);
	FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->doubleStep, doubleStep, IsBoolean, BooleanValue)

	self->Wrap(info.Holder());
	self->superpixelSeeds = cv::ximgproc::createSuperpixelSEEDS(img->mat.cols, img->mat.rows,
		img->mat.channels(), self->numSuperpixels, self->numLevels, self->prior, self->histogramBins, self->doubleStep);
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SuperpixelSEEDS::Iterate) {
	int iterations = 4;
	if (info[0]->IsInt32()) {
		iterations = info[0]->Int32Value();
	}
	SuperpixelSEEDS* self = Nan::ObjectWrap::Unwrap<SuperpixelSEEDS>(info.This());
	self->superpixelSeeds->iterate(Nan::ObjectWrap::Unwrap<Mat>(Nan::New(self->jsImg))->mat, iterations);
	self->superpixelSeeds->getLabels(Nan::ObjectWrap::Unwrap<Mat>(Nan::New(self->jsLabels))->mat);
	self->numCalculatedSuperpixels = self->superpixelSeeds->getNumberOfSuperpixels();
}

#endif // HAVE_XIMGPROC