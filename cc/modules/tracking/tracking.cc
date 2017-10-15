#include "Tracking.h"
#include "./Trackers/TrackerBoosting.h"
#include "./Trackers/TrackerGOTURN.h"
#include "./Trackers/TrackerKCF.h"
#include "./Trackers/TrackerMedianFlow.h"
#include "./Trackers/TrackerMIL.h"
#include "./Trackers/TrackerTLD.h"
#include "MultiTracker.h"

NAN_MODULE_INIT(Tracking::Init) {
	TrackerBoosting::Init(target);
	TrackerGOTURN::Init(target);
	TrackerKCF::Init(target);
	TrackerMedianFlow::Init(target);
	TrackerMIL::Init(target);
	TrackerTLD::Init(target);
	MultiTracker::Init(target);

	FF_OBJ trackerKCFModes = FF_NEW_OBJ();
	FF_SET_JS_PROP(trackerKCFModes, GRAY, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::GRAY));
	FF_SET_JS_PROP(trackerKCFModes, CN, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CN));
	FF_SET_JS_PROP(trackerKCFModes, CUSTOM, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CUSTOM));
	target->Set(FF_NEW_STRING("trackerKCFModes"), trackerKCFModes);
};