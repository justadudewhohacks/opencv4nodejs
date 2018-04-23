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
    
    
    FF_VAL getReturnValue() {
        FF_OBJ ret = FF_NEW_OBJ();            
        Nan::Set(ret, FF_NEW_STRING("msers"), ObjectArrayOfArraysConverter<Point2, cv::Point>::wrap(regions));
        Nan::Set(ret, FF_NEW_STRING("bboxes"), ObjectArrayConverter<Rect, cv::Rect>::wrap(mser_bbox));
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
