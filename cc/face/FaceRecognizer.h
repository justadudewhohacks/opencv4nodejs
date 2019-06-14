#include "NativeNodeUtils.h"
#include "macros.h"
#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include <opencv2/face.hpp>

#ifndef __FF_FACERECOGNIZER_H__
#define __FF_FACERECOGNIZER_H__

class FaceRecognizer : public FF::ObjectWrapBase<FaceRecognizer>, public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::face::FaceRecognizer> getFaceRecognizer() = 0;
	virtual void save(std::string) = 0;
	virtual void load(std::string) = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);

	static NAN_METHOD(Save);
	static NAN_METHOD(Load);
	static NAN_METHOD(Train);
	static NAN_METHOD(TrainAsync);
	static NAN_METHOD(Predict);
	static NAN_METHOD(PredictAsync);
};

#endif