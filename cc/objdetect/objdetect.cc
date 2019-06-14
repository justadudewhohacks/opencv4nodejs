#include "objdetect.h"
#include "CascadeClassifier.h"
#include "HOGDescriptor.h"
#include "DetectionROI.h"

NAN_MODULE_INIT(Objdetect::Init) {
	CascadeClassifier::Init(target);
	HOGDescriptor::Init(target);
	DetectionROI::Init(target);
};