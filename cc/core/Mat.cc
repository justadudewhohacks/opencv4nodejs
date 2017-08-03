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
	Nan::SetPrototypeMethod(ctor, "row", Row);
	Nan::SetPrototypeMethod(ctor, "copy", Copy);
	Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);

	Nan::SetPrototypeMethod(ctor, "add", Add);
	Nan::SetPrototypeMethod(ctor, "sub", Sub);
	Nan::SetPrototypeMethod(ctor, "and", And);
	Nan::SetPrototypeMethod(ctor, "or", Or);
	Nan::SetPrototypeMethod(ctor, "mul", Mul);
	Nan::SetPrototypeMethod(ctor, "div", Div);

	/* #IFDEF IMGPROC */
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax); 
	Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
	Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
	Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
	Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
	/* #ENDIF IMGPROC */

	v8::Local<v8::Object> matTypesModule = Nan::New<v8::Object>();
  initMatTypes(matTypesModule);
	target->Set(Nan::New("matTypes").ToLocalChecked(), matTypesModule);
  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

// TODO type undefined throw error 
NAN_METHOD(Mat::New) {
	Mat* self = new Mat();
	/* data, type */
	if (info[0]->IsArray() && info[1]->IsInt32()) {
		v8::Local<v8::Array> rowArray = v8::Local<v8::Array>::Cast(info[0]);
		int type = FF::reassignMatTypeIfFloat(info[1]->Int32Value());

		int numCols = -1;
		for (uint i = 0; i < rowArray->Length(); i++) {
			if (!rowArray->Get(i)->IsArray()) {
				return Nan::ThrowError(Nan::New("Mat::New - Column should be an array, at column: " + std::to_string(i)).ToLocalChecked());
			}
			v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(rowArray->Get(i));
			if (numCols != -1 && numCols != colArray->Length()) {
				return Nan::ThrowError(Nan::New("Mat::New - Mat cols must be of uniform length, at column: " + std::to_string(i)).ToLocalChecked());
			}
			numCols = colArray->Length();
		}

		cv::Mat mat = cv::Mat(rowArray->Length(), numCols, type);
		FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, type, FF_MAT_FROM_JS_ARRAY, FF::matPut);
		self->setNativeProps(mat);
	}
	/* row, col, type */
	else if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsInt32()) {
		int type = FF::reassignMatTypeIfFloat(info[2]->Int32Value());
		cv::Mat mat(info[0]->Int32Value(), info[1]->Int32Value(), type);
		/* fill vector */
		if (info[3]->IsArray()) {
			v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(info[3]);
			if (mat.channels() != vec->Length()) {
				return Nan::ThrowError(FF_V8STRING(
					std::string("Mat::New - number of channels (") + std::to_string(mat.channels())  
					+ std::string(") dont match fill vector length ") + std::to_string(vec->Length()))
				);
			}
			FF_MAT_APPLY_TYPED_OPERATOR(mat, vec, type, FF_MAT_FILL, FF::matPut);
		}
		if (info[3]->IsNumber()) {
			FF_MAT_APPLY_TYPED_OPERATOR(mat, info[3], type, FF_MAT_FILL, FF::matPut);
		}
		self->setNativeProps(mat);
	} 
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Mat::GetData) {
	cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
	v8::Local<v8::Array> rowArray = Nan::New<v8::Array>(mat.rows);
	FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
	info.GetReturnValue().Set(rowArray);
}

NAN_METHOD(Mat::Copy) {
	cv::Mat matSelf = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
	v8::Local<v8::Object> jsMatDst = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
	cv::Mat matDst = cv::Mat::zeros(matSelf.size(), matSelf.type());
	Nan::ObjectWrap::Unwrap<Mat>(jsMatDst)->setNativeProps(matDst);
	if (info[0]->IsObject()) {
		/* with mask*/
		matSelf.copyTo(matDst, Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat);
	}
	else {
		matSelf.copyTo(matDst);
	}
	info.GetReturnValue().Set(jsMatDst);
}

NAN_METHOD(Mat::CopyTo) {
	if (!info[0]->IsObject()) {
		return Nan::ThrowError("Mat::CopyTo - expected arg: destination mat");
	}
	cv::Mat matSelf = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
	cv::Mat matDst = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
	
	if (info[1]->IsObject()) {
		/* with mask*/
		matSelf.copyTo(matDst, Nan::ObjectWrap::Unwrap<Mat>(info[1]->ToObject())->mat);
	}
	else {
		matSelf.copyTo(matDst);
	}
	info.GetReturnValue().Set(info[0]);
}

NAN_METHOD(Mat::Add) {
	FF_MAT_OPERATOR(Mat::Add, +, false);
}

NAN_METHOD(Mat::Sub) {
	FF_MAT_OPERATOR(Mat::Sub, -, false);
}

NAN_METHOD(Mat::And) {
	FF_MAT_OPERATOR(Mat::And, &, false);
}

NAN_METHOD(Mat::Or) {
	FF_MAT_OPERATOR(Mat::Or, |, false);
}

NAN_METHOD(Mat::Mul) {
	FF_MAT_OPERATOR_WITH_SCALAR(Mat::Mul, *);
}

NAN_METHOD(Mat::Div) {
	FF_MAT_OPERATOR_WITH_SCALAR(Mat::Div, / );
}

/* #IFDEC IMGPROC */

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

NAN_METHOD(Mat::Threshold) {
	if (!info[0]->IsObject()) {
		// TODO usage messages
		return Nan::ThrowError(FF_V8STRING("Mat::Threshold - args object required"));
	}
	v8::Local<v8::Object> args = info[0]->ToObject();
	double thresh, maxVal;
	int type;
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, thresh, NumberValue);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, maxVal, NumberValue);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, type, Int32Value);

	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
	cv::threshold(
		Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat,
		Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat,
		thresh,
		maxVal,
		type
	);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::CvtColor) {
	if (!info[0]->IsObject()) {
		// TODO usage messages
		return Nan::ThrowError(FF_V8STRING("Mat::Threshold - args object required"));
	}
	v8::Local<v8::Object> args = info[0]->ToObject();
	int code, dstCn;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, code, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, dstCn, IsInt32, Int32Value)
		v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
	cv::cvtColor(
		Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat,
		Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat,
		code,
		dstCn
	);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::BgrToGray) {
	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
	cv::cvtColor(
		Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat, 
		Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat,
		CV_BGR2GRAY
	);

	info.GetReturnValue().Set(jsMat);
}
NAN_METHOD(Mat::WarpPerspective) {
	if (!info[0]->IsObject()) {
		// TODO usage messages
		return Nan::ThrowError(FF_V8STRING("warpPerspective - args object required"));
	}
	Mat* self = Nan::ObjectWrap::Unwrap<Mat>(info.This());
	v8::Local<v8::Object> args = info[0]->ToObject();
	v8::Local<v8::Object> jsTransformMat;
	FF_GET_JSPROP_REQUIRED(args, jsTransformMat, transformationMatrix, ToObject);
	cv::Mat transformationMatrix = Nan::ObjectWrap::Unwrap<Mat>(jsTransformMat)->mat;
	cv::Size size = cv::Size(self->mat.cols, self->mat.rows);
	if (args->HasOwnProperty(FF_V8STRING("size"))) {
		Nan::ObjectWrap::Unwrap<Size>(FF_GET_JSPROP(args, size)->ToObject())->size;
	}
	int flags = cv::INTER_LINEAR;
	int borderMode = cv::BORDER_CONSTANT;
	// TODO borderValue
	const cv::Scalar& borderValue = cv::Scalar();

	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, flags, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, borderMode, IsInt32, Int32Value);

	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();
	cv::warpPerspective(self->mat, Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat, transformationMatrix, size, flags, borderMode, borderValue);

	info.GetReturnValue().Set(jsMat);
}

/* #ENDIF IMGPROC */

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