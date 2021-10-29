#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "xfeatures2d.h"
// #include "SIFTDetector.h" https://github.com/justadudewhohacks/opencv4nodejs/issues/805#issuecomment-806314329
#include "SURFDetector.h"

NAN_MODULE_INIT(XFeatures2d::Init) {
	// SIFTDetector::Init(target); https://github.com/justadudewhohacks/opencv4nodejs/issues/805#issuecomment-806314329
	SURFDetector::Init(target);
};

#endif // HAVE_OPENCV_XFEATURES2D