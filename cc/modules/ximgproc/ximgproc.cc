#ifdef HAVE_XIMGPROC

#include "ximgproc.h"
#include "SuperpixelSEEDS.h"

#if CV_MINOR_VERSION > 0
#include "SuperpixelSLIC.h"
#include "SuperpixelLSC.h"
#endif

NAN_MODULE_INIT(XImgproc::Init) {
	SuperpixelSEEDS::Init(target);
#if CV_MINOR_VERSION > 0
	SuperpixelSLIC::Init(target);
	SuperpixelLSC::Init(target);
#endif
}

#endif // HAVE_XIMGPROC