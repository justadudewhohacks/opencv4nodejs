#ifdef HAVE_FACE

#include "LBPHFaceRecognizer.h"
#include "FaceRecognizerBindings.h"

Nan::Persistent<v8::FunctionTemplate> LBPHFaceRecognizer::constructor;

NAN_MODULE_INIT(LBPHFaceRecognizer::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(LBPHFaceRecognizer::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FaceRecognizer::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("LBPHFaceRecognizer").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(Nan::New("LBPHFaceRecognizer").ToLocalChecked(), ctor->GetFunction());
};

struct LBPHFaceRecognizer::NewWorker : public FF::SimpleWorker {
public:
	int radius = 1;
	int neighbors = 8;
	int grid_x = 8;
	int grid_y = 8;
	double threshold = DBL_MAX;

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &radius, info) ||
			IntConverter::optArg(1, &neighbors, info) ||
			IntConverter::optArg(2, &grid_x, info) ||
			IntConverter::optArg(3, &grid_y, info) ||
			DoubleConverter::optArg(4, &threshold, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject();
		return (
			IntConverter::optProp(&radius, "radius", opts) ||
			IntConverter::optProp(&neighbors, "neighbors", opts) ||
			IntConverter::optProp(&grid_x, "grid_x", opts) ||
			IntConverter::optProp(&grid_y, "grid_y", opts) ||
			DoubleConverter::optProp(&threshold, "threshold", opts)
		);
	}
};

NAN_METHOD(LBPHFaceRecognizer::New) {
	FF::TryCatch tryCatch;
	LBPHFaceRecognizer::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("LBPHFaceRecognizer::New");
		tryCatch.throwNew(err);
		return;
	}

	LBPHFaceRecognizer* self = new LBPHFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_MINOR < 3
	self->faceRecognizer = cv::face::createLBPHFaceRecognizer(worker.radius, worker.neighbors, worker.grid_x, worker.grid_y, worker.threshold);
#else
	self->faceRecognizer = cv::face::LBPHFaceRecognizer::create(worker.radius, worker.neighbors, worker.grid_x, worker.grid_y, worker.threshold);
#endif
	FF_RETURN(info.Holder());
};

#endif HAVE_FACE