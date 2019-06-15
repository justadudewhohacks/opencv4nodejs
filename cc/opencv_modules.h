#include "macros.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
#include <opencv2/opencv_modules.hpp>
// TODO: else via OPENCV4NODEJS_FOUND_MODULE_XYZ
#endif

#ifdef HAVE_OPENCV_HIGHGUI
#ifdef HAVE_OPENCV_IMGCODECS
#ifdef HAVE_OPENCV_VIDEOIO
#define HAVE_IO
#endif
#endif
#endif