#include <node.h>
#include "ExternalMemTracking.h"
#include "opencv_modules.h"

#include "core/core.h"
#ifdef HAVE_OPENCV_CALIB3D
#include "calib3d/calib3d.h"
#endif
#ifdef HAVE_OPENCV_DNN
#include "dnn/dnn.h"
#endif
#ifdef HAVE_OPENCV_FACE
#include "face/face.h"
#endif
#ifdef HAVE_OPENCV_FEATURES2D
#include "features2d/features2d.h"
#endif
#ifdef HAVE_OPENCV_IMGPROC
#include "imgproc/imgproc.h"
#endif
#ifdef HAVE_IO
#include "io/io.h"
#endif
#ifdef HAVE_OPENCV_ML
#include "machinelearning/machinelearning.h"
#endif
#ifdef HAVE_OPENCV_OBJDETECT
#include "objdetect/objdetect.h"
#endif
#ifdef HAVE_OPENCV_PHOTO
#include "photo/photo.h"
#endif
#ifdef HAVE_OPENCV_TEXT
#include "text/text.h"
#endif
#ifdef HAVE_OPENCV_TRACKING
#include "tracking/tracking.h"
#endif
#ifdef HAVE_OPENCV_VIDEO
#include "video/video.h"
#endif
#ifdef HAVE_OPENCV_XFEATURES2D
#include "xfeatures2d/xfeatures2d.h"
#endif
#ifdef HAVE_OPENCV_XIMGPROC
#include "ximgproc/ximgproc.h"
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

	Nan::Set(modules, FF::newString("core"), Nan::New(true));
	Core::Init(target);
#ifdef HAVE_OPENCV_CALIB3D
	Nan::Set(modules, FF::newString("calib3d"), Nan::New(true));
	Calib3d::Init(target);
#endif
#ifdef HAVE_OPENCV_DNN
	Nan::Set(modules, FF::newString("dnn"), Nan::New(true));
	Dnn::Init(target);
#endif
#ifdef HAVE_OPENCV_FACE
	Nan::Set(modules, FF::newString("face"), Nan::New(true));
	Face::Init(target);
#endif
#ifdef HAVE_OPENCV_FEATURES2D
	Nan::Set(modules, FF::newString("features2d"), Nan::New(true));
	Features2d::Init(target);
#endif
#ifdef HAVE_OPENCV_IMGPROC
	Nan::Set(modules, FF::newString("imgproc"), Nan::New(true));
	Imgproc::Init(target);
#endif
#ifdef HAVE_IO
	Nan::Set(modules, FF::newString("io"), Nan::New(true));
	Io::Init(target);
#endif
#ifdef HAVE_OPENCV_ML
	Nan::Set(modules, FF::newString("ml"), Nan::New(true));
	MachineLearning::Init(target);
#endif
#ifdef HAVE_OPENCV_OBJDETECT
	Nan::Set(modules, FF::newString("objdetect"), Nan::New(true));
	Objdetect::Init(target);
#endif
#ifdef HAVE_OPENCV_PHOTO
	Nan::Set(modules, FF::newString("photo"), Nan::New(true));
	Photo::Init(target);
#endif
#ifdef HAVE_OPENCV_TEXT
	Nan::Set(modules, FF::newString("text"), Nan::New(true));
	Text::Init(target);
#endif
#ifdef HAVE_OPENCV_TRACKING
	Nan::Set(modules, FF::newString("tracking"), Nan::New(true));
	Tracking::Init(target);
#endif
#ifdef HAVE_OPENCV_VIDEO
	Nan::Set(modules, FF::newString("video"), Nan::New(true));
	Video::Init(target);
#endif
#ifdef HAVE_OPENCV_XFEATURES2D
	Nan::Set(modules, FF::newString("xfeatures2d"), Nan::New(true));
	XFeatures2d::Init(target);
#endif
#ifdef HAVE_OPENCV_XIMGPROC
	Nan::Set(modules, FF::newString("ximgproc"), Nan::New(true));
	XImgproc::Init(target);
#endif
};

NODE_MODULE(opencv4nodejs, init)
