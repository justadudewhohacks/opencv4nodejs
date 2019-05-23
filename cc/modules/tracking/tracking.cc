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

#if CV_MINOR_VERSION > 3
#include "./Trackers/TrackerMOSSE.h"
#endif
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)
#include "./Trackers/TrackerCSRT.h"
#endif

NAN_MODULE_INIT(Tracking::Init) {
	TrackerBoosting::Init(target);
	TrackerMedianFlow::Init(target);
	TrackerMIL::Init(target);
	TrackerTLD::Init(target);

#if CV_MINOR_VERSION > 0
	TrackerKCF::Init(target);
	MultiTracker::Init(target);
	v8::Local<v8::Object> trackerKCFModes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(trackerKCFModes, GRAY, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::GRAY));
	FF_SET_JS_PROP(trackerKCFModes, CN, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CN));
	FF_SET_JS_PROP(trackerKCFModes, CUSTOM, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CUSTOM));
	Nan::Set(target,FF::newString("trackerKCFModes"), trackerKCFModes);
#endif

#if CV_MINOR_VERSION > 1
	TrackerGOTURN::Init(target);
#endif

#if CV_MINOR_VERSION > 3
	TrackerMOSSE::Init(target);
#endif
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)
	TrackerCSRT::Init(target);
#endif

};

#endif
