#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "tracking.h"
#include "./Trackers/TrackerBoosting.h"
#include "./Trackers/TrackerMedianFlow.h"
#include "./Trackers/TrackerMIL.h"
#include "./Trackers/TrackerTLD.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
#include "./Trackers/TrackerKCF.h"
#include "MultiTracker.h"
#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
#include "./Trackers/TrackerGOTURN.h"
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
#include "./Trackers/TrackerMOSSE.h"
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
#include "./Trackers/TrackerCSRT.h"
#endif

NAN_MODULE_INIT(Tracking::Init) {
	TrackerBoosting::Init(target);
	TrackerMedianFlow::Init(target);
	TrackerMIL::Init(target);
	TrackerTLD::Init(target);

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
	TrackerKCF::Init(target);
	MultiTracker::Init(target);
	v8::Local<v8::Object> trackerKCFModes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(trackerKCFModes, GRAY, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::GRAY));
	FF_SET_JS_PROP(trackerKCFModes, CN, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CN));
	FF_SET_JS_PROP(trackerKCFModes, CUSTOM, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CUSTOM));
	Nan::Set(target,FF::newString("trackerKCFModes"), trackerKCFModes);
#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
	TrackerGOTURN::Init(target);
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
	TrackerMOSSE::Init(target);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
	TrackerCSRT::Init(target);
#endif

};

#endif
