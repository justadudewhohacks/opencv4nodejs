#include "AGASTDetector.h"

Nan::Persistent<v8::FunctionTemplate> AGASTDetector::constructor;

NAN_MODULE_INIT(AGASTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(AGASTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("AGASTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), AGASTDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nonmaxSuppression").ToLocalChecked(), AGASTDetector::GetNonmaxSuppression);
	Nan::SetAccessor(instanceTemplate, Nan::New("type").ToLocalChecked(), AGASTDetector::GetType);

  Nan::Set(target,Nan::New("AGASTDetector").ToLocalChecked(), FF::getFunction(ctor));
};

struct NewWorker : CatchCvExceptionWorker {
public:
	int threshold = 10;
	bool nonmaxSuppression = true;
	int type = cv::AgastFeatureDetector::OAST_9_16;

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			FF::IntConverter::optArg(0, &threshold, info) ||
			FF::BoolConverter::optArg(1, &nonmaxSuppression, info) ||
			FF::IntConverter::optArg(2, &type, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::isArgObject(info, 0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		return (
			FF::IntConverter::optProp(&threshold, "threshold", opts) ||
			FF::BoolConverter::optProp(&nonmaxSuppression, "nonmaxSuppression", opts) ||
			FF::IntConverter::optProp(&type, "type", opts)
		);
	}

	std::string executeCatchCvExceptionWorker() {
		return "";
	}
};

NAN_METHOD(AGASTDetector::New) {
	FF::TryCatch tryCatch("AGASTDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	AGASTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	AGASTDetector* self = new AGASTDetector();
	self->detector = cv::AgastFeatureDetector::create(worker.threshold, worker.nonmaxSuppression, worker.type);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
