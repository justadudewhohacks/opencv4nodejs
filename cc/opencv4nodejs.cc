#include <node.h>
#include "cvTypes/cvTypes.h"

#include "core.h"
#include "modules/io/io.h"
#include "modules/video/video.h"
#include "modules/photo.h"
#include "modules/calib3d/calib3d.h"
#include "modules/imgproc/imgproc.h"
#include "modules/features2d/features2d.h"
#include "modules/objdetect/objdetect.h"
#include "modules/machinelearning/machinelearning.h"
#ifdef HAVE_TRACKING
#include "modules/tracking/tracking.h"
#endif // HAVE_TRACKING
#ifdef HAVE_XIMGPROC
#include "modules/ximgproc/ximgproc.h"
#endif // HAVE_XIMGPROC
#ifdef HAVE_XFEATURES2D
#include "modules/xfeatures2d/xfeatures2d.h"
#endif // HAVE_XFEATURES2D
#ifdef HAVE_TEXT
#include "modules/text/text.h"
#endif // HAVE_TEXT
#ifdef HAVE_FACE
#include "modules/face/face.h"
#endif // HAVE_FACE

#if CV_VERSION_MINOR > 2
#include "modules/dnn/dnn.h"
#endif

void init(v8::Local<v8::Object> target) {
	v8::Local<v8::Object> version = Nan::New<v8::Object>();
	Nan::Set(version, FF_NEW_STRING("major"), Nan::New(CV_MAJOR_VERSION));
	Nan::Set(version, FF_NEW_STRING("minor"), Nan::New(CV_MINOR_VERSION));
	Nan::Set(target, FF_NEW_STRING("version"), version);

	v8::Local<v8::Object> xmodules = Nan::New<v8::Object>();
	Nan::Set(target, FF_NEW_STRING("xmodules"), xmodules);

	CvTypes::Init(target);
	Core::Init(target);
  Io::Init(target);
	Video::Init(target);
  Photo::Init(target);
  Calib3d::Init(target);
  Imgproc::Init(target);
  Features2d::Init(target);
  Objdetect::Init(target);
	MachineLearning::Init(target);
#if CV_VERSION_MINOR > 2
	Nan::Set(xmodules, FF_NEW_STRING("dnn"), Nan::New(true));
	Dnn::Init(target);
#endif
#ifdef HAVE_TRACKING
	Nan::Set(xmodules, FF_NEW_STRING("tracking"), Nan::New(true));
	Tracking::Init(target);
#endif // HAVE_TRACKING
#ifdef HAVE_XIMGPROC
	Nan::Set(xmodules, FF_NEW_STRING("ximgproc"), Nan::New(true));
	XImgproc::Init(target);
#endif // HAVE_XIMGPROC
#ifdef HAVE_XFEATURES2D
	Nan::Set(xmodules, FF_NEW_STRING("xfeatures2d"), Nan::New(true));
	XFeatures2d::Init(target);
#endif // HAVE_XFEATURES2D
#ifdef HAVE_TEXT
	Nan::Set(xmodules, FF_NEW_STRING("text"), Nan::New(true));
	Text::Init(target);
#endif // HAVE_TEXT
#ifdef HAVE_FACE
	Nan::Set(xmodules, FF_NEW_STRING("face"), Nan::New(true));
	Face::Init(target);
#endif // HAVE_FACE

};

NODE_MODULE(opencv4nodejs, init)
