#include "TrainData.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> TrainData::constructor;

NAN_MODULE_INIT(TrainData::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrainData::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString("TrainData"));

	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("layout"), layout);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("samples"), samples);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("responses"), responses);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("varIdx"), varIdx);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("sampleWeights"), sampleWeights);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("varType"), varType);

	Nan::Set(target,FF::newString("TrainData"), FF::getFunction(ctor));
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
		self->self = cv::ml::TrainData::create(
			worker.samples, worker.layout, worker.responses, worker.varIdx, worker.sampleIdx, worker.sampleWeights, varType
		);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};
