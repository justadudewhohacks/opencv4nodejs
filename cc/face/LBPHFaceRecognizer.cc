#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

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

	Nan::Set(target,Nan::New("LBPHFaceRecognizer").ToLocalChecked(), FF::getFunction(ctor));
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
			FF::IntConverter::optArg(0, &radius, info) ||
			FF::IntConverter::optArg(1, &neighbors, info) ||
			FF::IntConverter::optArg(2, &grid_x, info) ||
			FF::IntConverter::optArg(3, &grid_y, info) ||
			FF::DoubleConverter::optArg(4, &threshold, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::isArgObject(info, 0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		return (
			FF::IntConverter::optProp(&radius, "radius", opts) ||
			FF::IntConverter::optProp(&neighbors, "neighbors", opts) ||
			FF::IntConverter::optProp(&grid_x, "grid_x", opts) ||
			FF::IntConverter::optProp(&grid_y, "grid_y", opts) ||
			FF::DoubleConverter::optProp(&threshold, "threshold", opts)
		);
	}
};

NAN_METHOD(LBPHFaceRecognizer::New) {
	FF::TryCatch tryCatch("LBPHFaceRecognizer::New");
	FF_ASSERT_CONSTRUCT_CALL();
	LBPHFaceRecognizer::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	LBPHFaceRecognizer* self = new LBPHFaceRecognizer();
	self->Wrap(info.Holder());
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->faceRecognizer = cv::face::LBPHFaceRecognizer::create(worker.radius, worker.neighbors, worker.grid_x, worker.grid_y, worker.threshold);
#else
	self->faceRecognizer = cv::face::createLBPHFaceRecognizer(worker.radius, worker.neighbors, worker.grid_x, worker.grid_y, worker.threshold);
#endif
	info.GetReturnValue().Set(info.Holder());
};

#endif // HAVE_OPENCV_FACE
