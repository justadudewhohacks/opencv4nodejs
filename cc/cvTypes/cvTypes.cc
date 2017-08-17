#include "cvTypes.h"
#include "matTypes.h"
#include "imgprocConstants.h"

void CvTypes::Init(v8::Local<v8::Object> target) {
	v8::Local<v8::Object> cvTypes = Nan::New<v8::Object>();
	initMatTypes(cvTypes);
	ImgprocConstants::Init(cvTypes);
	target->Set(FF_V8STRING("cvTypes"), cvTypes);
}