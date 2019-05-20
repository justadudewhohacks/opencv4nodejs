#include "ff_marshalling.h"

#ifndef __FF_PROPGETTERS_H__
#define __FF_PROPGETTERS_H__

/* js property getters */

#define FF_GET(ff_obj, ff_prop) Nan::Get(ff_obj, FF_NEW_STRING(ff_prop)).ToLocalChecked()

#endif