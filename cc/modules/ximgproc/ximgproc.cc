#ifdef HAVE_XIMGPROC

#include "ximgproc.h"
#include "SuperpixelSEEDS.h"
#include "SuperpixelSLIC.h"

NAN_MODULE_INIT(XImgproc::Init) {
	SuperpixelSEEDS::Init(target);
	SuperpixelSLIC::Init(target);
}

#endif // HAVE_XIMGPROC