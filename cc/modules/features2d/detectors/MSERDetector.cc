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
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("MSERDetector::New expected new key word");
	}

	MSERDetector* self = new MSERDetector();
	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->delta, delta, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->minArea, minArea, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->maxArea, maxArea, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->maxVariation, maxVariation, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->minDiversity, minDiversity, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->maxEvolution, maxEvolution, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->areaThreshold, areaThreshold, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->minMargin, minMargin, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->edgeBlurSize, edgeBlurSize, IsInt32, Int32Value)
	}
	
	self->Wrap(info.Holder());
	self->detector = cv::MSER::create(self->delta, self->minArea, self->maxArea, self->maxVariation, 
		self->minDiversity, self->maxEvolution, self->areaThreshold, self->minMargin, self->edgeBlurSize);
  info.GetReturnValue().Set(info.Holder());
}