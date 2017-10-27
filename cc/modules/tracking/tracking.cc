#ifdef HAVE_TRACKING

#include "tracking.h"
#include "./Trackers/TrackerBoosting.h"
#include "./Trackers/TrackerMedianFlow.h"
#include "./Trackers/TrackerMIL.h"
#include "./Trackers/TrackerTLD.h"

#if CV_MINOR_VERSION > 0
#include "./Trackers/TrackerKCF.h"
#include "MultiTracker.h"
#endif

#if CV_MINOR_VERSION > 1
#include "./Trackers/TrackerGOTURN.h"
#endif

NAN_MODULE_INIT(Tracking::Init) {
	TrackerBoosting::Init(target);
	TrackerMedianFlow::Init(target);
	TrackerMIL::Init(target);
	TrackerTLD::Init(target);

#if CV_MINOR_VERSION > 0
	TrackerKCF::Init(target);
	MultiTracker::Init(target);
	FF_OBJ trackerKCFModes = FF_NEW_OBJ();
	FF_SET_JS_PROP(trackerKCFModes, GRAY, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::GRAY));
	FF_SET_JS_PROP(trackerKCFModes, CN, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CN));
	FF_SET_JS_PROP(trackerKCFModes, CUSTOM, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CUSTOM));
	target->Set(FF_NEW_STRING("trackerKCFModes"), trackerKCFModes);
#endif

#if CV_MINOR_VERSION > 1
	TrackerGOTURN::Init(target);
#endif
};

#endif