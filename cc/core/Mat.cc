#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

NAN_MODULE_INIT(Mat::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Mat::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Mat").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rows").ToLocalChecked(), Mat::GetRows);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("cols").ToLocalChecked(), Mat::GetCols);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), Mat::GetType);

	Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
  Nan::SetPrototypeMethod(ctor, "row", Row);

	v8::Local<v8::Object> matTypesModule = Nan::New<v8::Object>();
  initMatTypes(matTypesModule);
	target->Set(Nan::New("matTypes").ToLocalChecked(), matTypesModule);
  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Mat::New) {
  Mat* self = new Mat();
  if (info[0]->IsArray() && info[1]->IsInt32()) {
    v8::Local<v8::Array> rowArray = v8::Local<v8::Array>::Cast(info[0]);
		int type = info[1]->Int32Value();

		int numCols = -1;	
		for (uint i = 0; i < rowArray->Length(); i++) {
			if (!rowArray->Get(i)->IsArray()) {
				return Nan::ThrowError(Nan::New("Column should be an array, at column: " + std::to_string(i)).ToLocalChecked());
			}
			v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(rowArray->Get(i));
			if (numCols != -1 && numCols != colArray->Length()) {
				return Nan::ThrowError(Nan::New("Mat cols must be of uniform length, at column: " + std::to_string(i)).ToLocalChecked());
			}
			numCols = colArray->Length();
		}
	
		cv::Mat mat = cv::Mat(rowArray->Length(), numCols, type);
		FF::fillMatDataFromJsArray(mat, rowArray, type);
    self->setNativeProps(mat);
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Mat::GetData) {
	info.GetReturnValue().Set(FF::matDataToJsArray(Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat));
}

NAN_METHOD(Mat::Rescale) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: rescale(double factor)");      
  }
  double factor = (double)info[0]->NumberValue();
  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
  cv::resize(
    Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat, 
    Nan::ObjectWrap::Unwrap<Mat>(handle)->mat, 
    cv::Size(), 
    factor, 
    factor
  );
  info.GetReturnValue().Set(handle);
}

NAN_METHOD(Mat::Resize) {
  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    return Nan::ThrowError("usage: resize(int rows, int cols)");      
  }
  int rows = (int)info[0]->NumberValue();
  int cols = (int)info[1]->NumberValue();
  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
  cv::resize(
    Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat, 
    Nan::ObjectWrap::Unwrap<Mat>(handle)->mat, 
    cv::Size(rows, cols)
  );
  info.GetReturnValue().Set(handle);
}

NAN_METHOD(Mat::ResizeToMax) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: resizeToMax(int maxRowsOrCols)");      
  }
  int maxRowsOrCols = (int)info[0]->NumberValue();
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
  double ratioY = (double)maxRowsOrCols / (double)mat.rows;
  double ratioX = (double)maxRowsOrCols / (double)mat.cols;
	double scale = std::min(ratioY, ratioX);

  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
  cv::resize(
    mat, 
    Nan::ObjectWrap::Unwrap<Mat>(handle)->mat, 
    cv::Size((int)(mat.cols * scale), (int)(mat.rows * scale))
  );
  info.GetReturnValue().Set(handle);
}

NAN_METHOD(Mat::Row) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: row(int r)");      
  }
  int r = (int)info[0]->NumberValue();
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
  v8::Local<v8::Array> row = Nan::New<v8::Array>(mat.cols);
  try {
    if (mat.type() == CV_32FC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New(mat.at<float>(r, c)));
      }
    } else if (mat.type() == CV_8UC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New((uint)mat.at<uchar>(r, c)));
      }
    } else if (mat.type() == CV_8UC3) {
      for (int c = 0;  c < mat.cols; c++) {
        cv::Vec3b vec = mat.at<cv::Vec3b>(r, c);
        v8::Local<v8::Array> jsVec = Nan::New<v8::Array>(3);
        for (int i = 0; i < 3; i++) {
          jsVec->Set(i, Nan::New(vec[i]));
        }
        row->Set(c, jsVec);
      }
    } else {
      return Nan::ThrowError(Nan::New("not implemented yet - mat type:" + mat.type()).ToLocalChecked());
    }
  } catch(std::exception &e) {
    return Nan::ThrowError(e.what());
  } catch(...) {
    return Nan::ThrowError("... Exception");
  }
  info.GetReturnValue().Set(row);
}

void Mat::setNativeProps(cv::Mat mat) {
  this->mat = mat;
};