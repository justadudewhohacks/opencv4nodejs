#ifdef HAVE_FACE

#include "face.h"
#include "EigenFaceRecognizer.h"
#include "FisherFaceRecognizer.h"
#include "LBPHFaceRecognizer.h"

NAN_MODULE_INIT(Face::Init) {
	EigenFaceRecognizer::Init(target);
	FisherFaceRecognizer::Init(target);
	LBPHFaceRecognizer::Init(target);
};

#endif