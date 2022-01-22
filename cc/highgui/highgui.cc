#include "opencv_modules.h"

#ifdef HAVE_OPENCV_HIGHGUI

// #include "opencv2/core.hpp"
// #include "macros.h"
#include "highgui.h"
#include "highguiBindings.h"
#include "highguiConstants.h"

NAN_MODULE_INIT(Highgui::Init) {
    HighguiConstants::Init(target);
};

#endif
