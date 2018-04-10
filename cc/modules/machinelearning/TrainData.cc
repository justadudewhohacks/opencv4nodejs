#include "TrainData.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> TrainData::constructor;

NAN_MODULE_INIT(TrainData::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrainData::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_NEW_STRING("TrainData"));

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("layout"), layout);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("samples"), samples);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("responses"), responses);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("varIdx"), varIdx);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("sampleWeights"), sampleWeights);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("varType"), varType);

	target->Set(FF_NEW_STRING("TrainData"), ctor->GetFunction());
};

NAN_METHOD(TrainData::New) {
	FF_METHOD_CONTEXT("TrainData::New");
	TrainData* self = new TrainData();
	if (info.Length() > 0) {
		// required args
		FF_ARG_INSTANCE(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		FF_ARG_UINT(1, unsigned int layout);
		FF_ARG_INSTANCE(2, cv::Mat responses, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

		// optional args
		bool hasOptArgsObj = FF_HAS_ARG(3) && !info[3]->IsArray();
		FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
		FF_GET_UNPACK_INT_ARRAY_IFDEF(optArgs, varIdx, "varIdx", varIdx);
		FF_GET_UNPACK_INT_ARRAY_IFDEF(optArgs, sampleIdx, "sampleIdx", sampleIdx);
		std::vector<float> sampleWeights;
		FloatArrayConverter::optProp(&sampleWeights, "sampleWeights", optArgs);
		FF_GET_UNPACK_UCHAR_ARRAY_IFDEF(optArgs, varType, "varType", varType);
		if (!hasOptArgsObj) {
			FF_ARG_UNPACK_INT_ARRAY_TO_IFDEF(3, varIdx, varIdx);
			FF_ARG_UNPACK_INT_ARRAY_TO_IFDEF(4, sampleIdx, sampleIdx);
			FloatArrayConverter::optArg(5, &sampleWeights, info);
			FF_ARG_UNPACK_UCHAR_ARRAY_TO_IFDEF(6, varType, varType);
		}

		self->trainData = cv::ml::TrainData::create(samples, layout, responses, varIdx, sampleIdx, sampleWeights, varType);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};