#include "features2d.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "DescriptorMatch.h"
#include "descriptorMatching.h"
#include "detectors/AGASTDetector.h"
#include "detectors/AKAZEDetector.h"
#include "detectors/BRISKDetector.h"
#include "detectors/FASTDetector.h"
#include "detectors/GFTTDetector.h"
#include "detectors/KAZEDetector.h"
#include "detectors/MSERDetector.h"
#include "detectors/ORBDetector.h"

NAN_MODULE_INIT(Features2d::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	KeyPoint::Init(module);
	KeyPointMatch::Init(module);
	DescriptorMatch::Init(module);
	DescriptorMatching::Init(module);
	AGASTDetector::Init(module);
	AKAZEDetector::Init(module);
	BRISKDetector::Init(module);
	FASTDetector::Init(module);
	GFTTDetector::Init(module);
	KAZEDetector::Init(module);
	MSERDetector::Init(module);
	ORBDetector::Init(module);
  target->Set(Nan::New("features2d").ToLocalChecked(), module);
};