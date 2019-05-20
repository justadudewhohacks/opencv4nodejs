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

	target->Set(FF_NEW_STRING("TrainData"), FF::getFunction(ctor));
};

NAN_METHOD(TrainData::New) {
  FF_ASSERT_CONSTRUCT_CALL(TrainData);
	TrainData* self = new TrainData();
	if (info.Length() > 0) {
		FF::TryCatch tryCatch;
		TrainData::NewWorker worker;

		if (worker.applyUnwrappers(info)) {
			v8::Local<v8::Value> err = tryCatch.formatCatchedError("TrainData::New");
			tryCatch.throwNew(err);
			return;
		}

		// TODO: uchar / char converter
		std::vector<uchar> varType;
		for (auto val : worker.varType) {
			varType.push_back(val);
		}
		self->trainData = cv::ml::TrainData::create(
			worker.samples, worker.layout, worker.responses, worker.varIdx, worker.sampleIdx, worker.sampleWeights, varType
		);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};
