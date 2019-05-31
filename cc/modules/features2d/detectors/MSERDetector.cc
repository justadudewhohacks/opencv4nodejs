#include "MSERDetector.h"
#include "Rect.h"
#include "Point.h"

Nan::Persistent<v8::FunctionTemplate> MSERDetector::constructor;

NAN_MODULE_INIT(MSERDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(MSERDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("MSERDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(ctor, "detectRegions", MSERDetector::DetectRegions);
	Nan::SetPrototypeMethod(ctor, "detectRegionsAsync", MSERDetector::DetectRegionsAsync);

	Nan::SetAccessor(instanceTemplate, Nan::New("delta").ToLocalChecked(), MSERDetector::GetDelta);
	Nan::SetAccessor(instanceTemplate, Nan::New("minArea").ToLocalChecked(), MSERDetector::GetMinArea);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxArea").ToLocalChecked(), MSERDetector::GetMaxArea);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxVariation").ToLocalChecked(), MSERDetector::GetMaxVariation);
	Nan::SetAccessor(instanceTemplate, Nan::New("minDiversity").ToLocalChecked(), MSERDetector::GetMinDiversity);
	Nan::SetAccessor(instanceTemplate, Nan::New("maxEvolution").ToLocalChecked(), MSERDetector::GetMaxEvolution);
	Nan::SetAccessor(instanceTemplate, Nan::New("areaThreshold").ToLocalChecked(), MSERDetector::GetAreaThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("minMargin").ToLocalChecked(), MSERDetector::GetMinMargin);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeBlurSize").ToLocalChecked(), MSERDetector::GetEdgeBlurSize);

  Nan::Set(target,Nan::New("MSERDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(MSERDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(MSERDetector);
	FF::TryCatch tryCatch;
	MSERDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("MSERDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	MSERDetector* self = new MSERDetector();
	self->Wrap(info.Holder());
	self->delta = worker.delta;
	self->minArea = worker.minArea;
	self->maxArea = worker.maxArea;
	self->maxVariation = worker.maxVariation;
	self->minDiversity = worker.minDiversity;
	self->maxEvolution = worker.maxEvolution;
	self->areaThreshold = worker.areaThreshold;
	self->minMargin = worker.minMargin;
	self->edgeBlurSize = worker.edgeBlurSize;
	self->detector = cv::MSER::create(worker.delta, worker.minArea, worker.maxArea, worker.maxVariation,
		worker.minDiversity, worker.maxEvolution, worker.areaThreshold, worker.minMargin, worker.edgeBlurSize);
	info.GetReturnValue().Set(info.Holder());
}

struct DetectRegionsWorker : public CatchCvExceptionWorker {
public:
    cv::Ptr<cv::MSER> det;

    DetectRegionsWorker( MSERDetector *mser){
        this->det = mser->getMSERDetector();
    }

    cv::Mat img;
    std::vector<std::vector<cv::Point> > regions;
    std::vector<cv::Rect> mser_bbox;

    std::string executeCatchCvExceptionWorker() {
        det->detectRegions(img, regions, mser_bbox);
        return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
        // we only need input image
		return Mat::Converter::arg(0, &img, info);
	}


    v8::Local<v8::Value> getReturnValue() {
        v8::Local<v8::Object> ret = Nan::New<v8::Object>();
        Nan::Set(ret, FF::newString("msers"), ObjectArrayOfArraysConverter<Point2, cv::Point>::wrap(regions));
        Nan::Set(ret, FF::newString("bboxes"), Rect::ArrayConverter::wrap(mser_bbox));
        return ret;
    }
};


NAN_METHOD(MSERDetector::DetectRegions) {
	FF::SyncBinding(
		std::make_shared<DetectRegionsWorker>(FF_UNWRAP(info.This(), MSERDetector)),
		"MSERDetector::DetectRegions",
		info
	);
}

NAN_METHOD(MSERDetector::DetectRegionsAsync) {
	FF::AsyncBinding(
		std::make_shared<DetectRegionsWorker>(FF_UNWRAP(info.This(), MSERDetector)),
		"MSERDetector::DetectRegionsAsync",
		info
	);
}
