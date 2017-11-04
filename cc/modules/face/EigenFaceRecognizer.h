#include "FaceRecognizer.h"

#ifndef __FF_EIGENFACERECOGNIZER_H__
#define __FF_EIGENFACERECOGNIZER_H__

class EigenFaceRecognizer : public FaceRecognizer {
public:
	cv::Ptr<cv::face::FaceRecognizer> faceRecognizer;
	void save(std::string path) {
		faceRecognizer->save(path);
	}

	void load(std::string path) {
#if CV_VERSION_MINOR < 3
		faceRecognizer->load(path);
#else
		faceRecognizer = cv::Algorithm::load<cv::face::EigenFaceRecognizer>(path);
#endif
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::face::FaceRecognizer> getFaceRecognizer() {
		return faceRecognizer;
	}
};

#endif