#include "io.h"
#include "Mat.h"
#include <iostream>

NAN_MODULE_INIT(Io::Init) {
  Nan::SetMethod(target, "imread", Imread);
  Nan::SetMethod(target, "imshow", Imshow);
	Nan::SetMethod(target, "imshowWait", ImshowWait);
  Nan::SetMethod(target, "imsave", Imsave);
	Nan::SetMethod(target, "waitKey", WaitKey);
};

NAN_METHOD(Io::Imread) {
  if (!info[0]->IsString()) {
    return Nan::ThrowError("Imread expected arg0 to be path");
  }

  std::string path = FF_JS_VAL_TO_STRING(info[0]);
	cv::Mat mat = cv::imread(path);
	if (mat.rows == 0 && mat.cols == 0) {
		return Nan::ThrowError("imread empty mat");
	}
	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMat) = mat;
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Io::Imsave) {
  if (!info[0]->IsString()) {
    return Nan::ThrowError("Imsave expected arg0 to be path");
	}
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		return Nan::ThrowError("Imsave expected arg1 to be an instance of Mat");
	}
	cv::imwrite(FF_JS_VAL_TO_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
}

NAN_METHOD(Io::Imshow) {
  if (!info[0]->IsString()) {
    return Nan::ThrowError("Imshow expected arg0 to be the window name");
  }
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		return Nan::ThrowError("Imshow expected arg1 to be an instance of Mat");
	}
	cv::imshow(FF_JS_VAL_TO_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
}

NAN_METHOD(Io::ImshowWait) {
	if (!info[0]->IsString()) {
		return Nan::ThrowError("Imshow expected arg0 to be the window name");
	}
	if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
		return Nan::ThrowError("Imshow expected arg1 to be an instance of Mat");
	}
	cv::imshow(FF_JS_VAL_TO_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject()));
	cv::waitKey();
}

NAN_METHOD(Io::WaitKey) {
	if (!info[0]->IsNumber()) {
		cv::waitKey(info[0]->NumberValue());
	} else{
		cv::waitKey();
	}
}