#include "io.h"
#include "Mat.h"
#include "VideoCapture.h"
#include <iostream>

NAN_MODULE_INIT(Io::Init) {
  Nan::SetMethod(target, "imread", Imread);
  Nan::SetMethod(target, "imshow", Imshow);
	Nan::SetMethod(target, "imshowWait", ImshowWait);
  Nan::SetMethod(target, "imwrite", Imwrite);
	Nan::SetMethod(target, "waitKey", WaitKey);
	VideoCapture::Init(target);
};

NAN_METHOD(Io::Imread) {
	FF_METHOD_CONTEXT("Imread");
  if (!info[0]->IsString()) {
		FF_THROW("expected arg0 to be path");
  }

  std::string path = FF_CAST_STRING(info[0]);
	cv::Mat mat = cv::imread(path);
	if (mat.rows == 0 && mat.cols == 0) {
		FF_THROW("empty mat");
	}
	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMat) = mat;
	FF_RETURN(jsMat);
}

NAN_METHOD(Io::Imwrite) {
	FF_METHOD_CONTEXT("Imwrite");
  if (!info[0]->IsString()) {
		FF_THROW("expected arg0 to be path");
	}
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		FF_THROW("expected arg1 to be an instance of Mat");
	}
	cv::imwrite(FF_CAST_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
}

NAN_METHOD(Io::Imshow) {
	FF_METHOD_CONTEXT("Imshow");
  if (!info[0]->IsString()) {
		FF_THROW("expected arg0 to be the window name");
  }
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		FF_THROW("expected arg1 to be an instance of Mat");
	}
	cv::imshow(FF_CAST_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
}

NAN_METHOD(Io::ImshowWait) {
	FF_METHOD_CONTEXT("ImshowWait");
	if (!info[0]->IsString()) {
		FF_THROW("expected arg0 to be the window name");
	}
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		FF_THROW("expected arg1 to be an instance of Mat");
	}
	cv::imshow(FF_CAST_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
	cv::waitKey();
}

NAN_METHOD(Io::WaitKey) {
	int key;
	if (info[0]->IsNumber()) {
		key = cv::waitKey(info[0]->NumberValue());
	} else{
		key = cv::waitKey();
	}
	FF_RETURN(Nan::New(key));
}