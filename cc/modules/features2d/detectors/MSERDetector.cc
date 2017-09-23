#include "MSERDetector.h"

Nan::Persistent<v8::FunctionTemplate> MSERDetector::constructor;

NAN_MODULE_INIT(MSERDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(MSERDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("MSERDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("delta").ToLocalChecked(), MSERDetector::GetDelta);
	Nan::SetAccessor(instanceTemplate, Nan::New("minArea").ToLocalChecked(), MSERDetector::GetMinArea);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxArea").ToLocalChecked(), MSERDetector::GetMaxArea);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxVariation").ToLocalChecked(), MSERDetector::GetMaxVariation);
	Nan::SetAccessor(instanceTemplate, Nan::New("minDiversity").ToLocalChecked(), MSERDetector::GetMinDiversity);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxEvolution").ToLocalChecked(), MSERDetector::GetMaxEvolution);
	Nan::SetAccessor(instanceTemplate, Nan::New("areaThreshold").ToLocalChecked(), MSERDetector::GetAreaThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("minMargin").ToLocalChecked(), MSERDetector::GetMinMargin);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeBlurSize").ToLocalChecked(), MSERDetector::GetEdgeBlurSize);

  target->Set(Nan::New("MSERDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(MSERDetector::New) {
	FF_METHOD_CONTEXT("MSERDetector::New");
	MSERDetector* self = new MSERDetector();

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, self->delta, "delta", 5);
	FF_GET_INT_IFDEF(optArgs, self->minArea, "minArea", 60);
	FF_GET_INT_IFDEF(optArgs, self->maxArea, "maxArea", 14400);
	FF_GET_NUMBER_IFDEF(optArgs, self->maxVariation, "maxVariation", 0.25);
	FF_GET_NUMBER_IFDEF(optArgs, self->minDiversity, "minDiversity", 0.2);
	FF_GET_INT_IFDEF(optArgs, self->maxEvolution, "maxEvolution", 200);
	FF_GET_NUMBER_IFDEF(optArgs, self->areaThreshold, "areaThreshold", 1.01);
	FF_GET_NUMBER_IFDEF(optArgs, self->minMargin, "minMargin", 0.003);
	FF_GET_INT_IFDEF(optArgs, self->edgeBlurSize, "edgeBlurSize", 5);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, self->delta, self->delta);
		FF_ARG_INT_IFDEF(1, self->minArea, self->minArea);
		FF_ARG_INT_IFDEF(2, self->maxArea, self->maxArea);
		FF_ARG_NUMBER_IFDEF(3, self->maxVariation, self->maxVariation);
		FF_ARG_NUMBER_IFDEF(4, self->minDiversity, self->minDiversity);
		FF_ARG_INT_IFDEF(5, self->maxEvolution, self->maxEvolution);
		FF_ARG_NUMBER_IFDEF(6, self->areaThreshold, self->areaThreshold);
		FF_ARG_NUMBER_IFDEF(7, self->minMargin, self->minMargin);
		FF_ARG_INT_IFDEF(8, self->edgeBlurSize, self->edgeBlurSize);
	}

	self->Wrap(info.Holder());
	self->detector = cv::MSER::create(self->delta, self->minArea, self->maxArea, self->maxVariation, 
		self->minDiversity, self->maxEvolution, self->areaThreshold, self->minMargin, self->edgeBlurSize);
  FF_RETURN(info.Holder());
}