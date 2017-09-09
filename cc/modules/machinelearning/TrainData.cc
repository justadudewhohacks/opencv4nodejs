#include "TrainData.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> TrainData::constructor;

NAN_MODULE_INIT(TrainData::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrainData::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_V8STRING("TrainData"));

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("varIdx"), varIdx);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("sampleWeights"), sampleWeights);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("varType"), varType);

	target->Set(FF_V8STRING("TrainData"), ctor->GetFunction());
};

NAN_METHOD(TrainData::New) {
	FF_METHOD_CONTEXT("TrainData::New");
	TrainData* self = new TrainData();
	if (info.Length() > 0) {
		// required args
		FF_ARG_OBJ(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		FF_ARG_UINT(1, unsigned int layout);
		FF_ARG_OBJ(2, cv::Mat responses, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

		// optional args
		FF_OBJ optArgs = (info.Length() == 4 && info[3]->IsObject() && !FF_IS_INSTANCE(Mat::constructor, info[3]) ? info[3]->ToObject() : FF_NEW_OBJ());
		FF_GET_OBJ_IFDEF(optArgs, cv::Mat varIdx, "varIdx", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
		FF_GET_OBJ_IFDEF(optArgs, cv::Mat sampleIdx, "sampleIdx", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
		FF_GET_OBJ_IFDEF(optArgs, cv::Mat sampleWeights, "sampleWeights", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
		FF_GET_OBJ_IFDEF(optArgs, cv::Mat varType, "varType", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());

		FF_ARG_OBJ_IFDEF(3, varIdx, Mat::constructor, FF_UNWRAP_MAT_AND_GET, varIdx);
		FF_ARG_OBJ_IFDEF(4, sampleIdx, Mat::constructor, FF_UNWRAP_MAT_AND_GET, sampleIdx);
		FF_ARG_OBJ_IFDEF(5, sampleWeights, Mat::constructor, FF_UNWRAP_MAT_AND_GET, sampleWeights);
		FF_ARG_OBJ_IFDEF(6, varType, Mat::constructor, FF_UNWRAP_MAT_AND_GET, varType);

		self->trainData = cv::ml::TrainData::create(samples, layout, responses, varIdx, sampleIdx, sampleWeights, varType);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};