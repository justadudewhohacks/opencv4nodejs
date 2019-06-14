#include <node.h>
#include "ExternalMemTracking.h"

#include "core/core.h"
#include "cvTypes/cvTypes.h"
#ifdef HAVE_HIGHGUI
#include "io/io.h"
#endif
#ifdef HAVE_CALIB3D
#include "calib3d/calib3d.h"
#endif
#ifdef HAVE_IMGPROC
#include "imgproc/imgproc.h"
#endif
#ifdef HAVE_VIDEO
#include "video/video.h"
#endif
#ifdef HAVE_PHOTO
#include "photo/photo.h"
#endif
#ifdef HAVE_FEATURES2D
#include "features2d/features2d.h"
#endif
#ifdef HAVE_OBJDETECT
#include "objdetect/objdetect.h"
#endif
#ifdef HAVE_ML
#include "machinelearning/machinelearning.h"
#endif
#ifdef HAVE_TRACKING
#include "tracking/tracking.h"
#endif
#ifdef HAVE_XIMGPROC
#include "ximgproc/ximgproc.h"
#endif
#ifdef HAVE_XFEATURES2D
#include "xfeatures2d/xfeatures2d.h"
#endif
#ifdef HAVE_TEXT
#include "text/text.h"
#endif
#ifdef HAVE_FACE
#include "face/face.h"
#endif
#if HAVE_DNN
#include "dnn/dnn.h"
#endif

int customCvErrorHandler(int status, const char* func_name, const char* err_msg, const char* file_name, int line, void* userdata) {
    std::string msg = "OpenCV Error: (" + std::string(err_msg) + ")"
      + " in " + std::string(func_name)
      + ", in file " + std::string(file_name)
      + ", line " + std::to_string(line)
      + ", status " + std::to_string(status);

    throw std::runtime_error(msg);
    return 0;
}

void init(v8::Local<v8::Object> target) {
	// can be disabled by defining env variable: OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING
	ExternalMemTracking::Init(target);

	// override cv error handler to prevent printing cv errors and throw std::exception
	// instead, which can be catched and forwarded to node process
	cv::redirectError(customCvErrorHandler);


	v8::Local<v8::Object> version = Nan::New<v8::Object>();
	Nan::Set(version, FF::newString("major"), Nan::New(CV_VERSION_MAJOR));
	Nan::Set(version, FF::newString("minor"), Nan::New(CV_VERSION_MINOR));
	Nan::Set(version, FF::newString("revision"), Nan::New(CV_VERSION_REVISION));
	Nan::Set(target, FF::newString("version"), version);

	v8::Local<v8::Object> modules = Nan::New<v8::Object>();
	Nan::Set(target, FF::newString("modules"), modules);

	CvTypes::Init(target);
	Core::Init(target);
#if HAVE_HIGHGUI
	Io::Init(target);
#endif
#if HAVE_VIDEO
	Video::Init(target);
#endif
#if HAVE_PHOTO
	Photo::Init(target);
#endif
#if HAVE_CALIB3D
	Calib3d::Init(target);
#endif
#if HAVE_IMGPROC
	Imgproc::Init(target);
#endif
#if HAVE_FEATURES2D
	Features2d::Init(target);
#endif
#if HAVE_ML
	Objdetect::Init(target);
#endif
#if HAVE_ML
	MachineLearning::Init(target);
#endif
#if HAVE_DNN
	Nan::Set(modules, FF::newString("dnn"), Nan::New(true));
	Dnn::Init(target);
#endif
#ifdef HAVE_TRACKING
	Nan::Set(modules, FF::newString("tracking"), Nan::New(true));
	Tracking::Init(target);
#endif // HAVE_TRACKING
#ifdef HAVE_XIMGPROC
	Nan::Set(modules, FF::newString("ximgproc"), Nan::New(true));
	XImgproc::Init(target);
#endif // HAVE_XIMGPROC
#ifdef HAVE_XFEATURES2D
	Nan::Set(modules, FF::newString("xfeatures2d"), Nan::New(true));
	XFeatures2d::Init(target);
#endif // HAVE_XFEATURES2D
#ifdef HAVE_TEXT
	Nan::Set(modules, FF::newString("text"), Nan::New(true));
	Text::Init(target);
#endif // HAVE_TEXT
#ifdef HAVE_FACE
	Nan::Set(modules, FF::newString("face"), Nan::New(true));
	Face::Init(target);
#endif // HAVE_FACE
};

NODE_MODULE(opencv4nodejs, init)
