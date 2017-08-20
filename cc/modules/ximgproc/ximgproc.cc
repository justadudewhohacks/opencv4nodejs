#ifdef HAVE_XIMGPROC

#include "ximgproc.h"
#include "SuperpixelSEEDS.h"

NAN_MODULE_INIT(XImgproc::Init) {
	SuperpixelSEEDS::Init(target);
}

#endif // HAVE_XIMGPROC