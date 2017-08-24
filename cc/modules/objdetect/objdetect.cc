#include "objdetect.h"
#include "CascadeClassifier.h"

NAN_MODULE_INIT(Objdetect::Init) {
	CascadeClassifier::Init(target);
};