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

	Nan::SetPrototypeMethod(ctor, "at", At);
	Nan::SetPrototypeMethod(ctor, "atRaw", AtRaw);
	Nan::SetPrototypeMethod(ctor, "set", Set);
	Nan::SetPrototypeMethod(ctor, "getData", GetData);
	Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
	Nan::SetPrototypeMethod(ctor, "row", Row);
	Nan::SetPrototypeMethod(ctor, "copy", Copy);
	Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
	Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);

	FF_PROTO_SET_MAT_OPERATIONS(ctor);

	/* #IFDEF IMGPROC */
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
	Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
	Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
	Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
	Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
	Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
	Nan::SetPrototypeMethod(ctor, "erode", Erode);
	/* #ENDIF IMGPROC */

	v8::Local<v8::Object> matTypesModule = Nan::New<v8::Object>();
	target->Set(Nan::New("matTypes").ToLocalChecked(), matTypesModule);
  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

// TODO type undefined throw error
NAN_METHOD(Mat::New) {
	Mat* self = new Mat();
	/* data array, type */
	if (info.Length() == 2 && info[0]->IsArray() && info[1]->IsInt32()) {
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
	/* raw data, row, col, type */
	else if (info.Length() == 4 && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsInt32()) {
		int type = FF::reassignMatTypeIfFloat(info[3]->Int32Value());
		char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject()));
		cv::Mat mat(info[1]->Int32Value(), info[2]->Int32Value(), type);
		size_t size = mat.rows * mat.cols * mat.elemSize();
		memcpy(mat.data, data, size);
		self->setNativeProps(mat);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Mat::At) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	v8::Local<v8::Value> jsVal;
	if (val->IsArray()) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(val);
		v8::Local<v8::Object> jsVec;
		if (vec->Length() == 2) {
			jsVec = FF_NEW(Vec2::constructor);
			FF_UNWRAP_VEC2(jsVec)->vec = cv::Vec2d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue());
		}
		else if (vec->Length() == 3) {
			jsVec = FF_NEW(Vec3::constructor);
			FF_UNWRAP_VEC3(jsVec)->vec = cv::Vec3d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue());
		}
		else {
			jsVec = FF_NEW(Vec4::constructor);
			FF_UNWRAP_VEC4(jsVec)->vec = cv::Vec4d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue(), vec->Get(3)->NumberValue());
		}
		jsVal = jsVec;
	}
	else {
		jsVal = v8::Local<v8::Value>::Cast(val);
	}
	info.GetReturnValue().Set(jsVal);
}

NAN_METHOD(Mat::AtRaw) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	info.GetReturnValue().Set(val);
}

NAN_METHOD(Mat::Set) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::Set row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::Set col");

	int cn = matSelf.channels();
	if (info[2]->IsArray()) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(info[2]);
		FF_ASSERT_CHANNELS(cn, vec->Length(), "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, vec, matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec2::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 2, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<2>(FF_UNWRAP_VEC2_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec3::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 3, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<3>(FF_UNWRAP_VEC3_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec4::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 4, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<4>(FF_UNWRAP_VEC4_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (info[2]->IsNumber()) {
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, info[2], matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else {
		return Nan::ThrowError(FF_V8STRING("Mat::Set - unexpected argument 2"));
	}
}

NAN_METHOD(Mat::GetData) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	size_t size = matSelf.rows * matSelf.cols * matSelf.elemSize();
	char *data = static_cast<char *>(malloc(size));
	memcpy(data, matSelf.data, size);
	info.GetReturnValue().Set(Nan::NewBuffer(data, size).ToLocalChecked());
}

NAN_METHOD(Mat::GetDataAsArray) {
	cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
	v8::Local<v8::Array> rowArray = Nan::New<v8::Array>(mat.rows);
	FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
	info.GetReturnValue().Set(rowArray);
}

NAN_METHOD(Mat::Copy) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	v8::Local<v8::Object> jsMatDst = FF_NEW(constructor);
	cv::Mat matDst = cv::Mat::zeros(matSelf.size(), matSelf.type());
	Nan::ObjectWrap::Unwrap<Mat>(jsMatDst)->setNativeProps(matDst);
	if (info[0]->IsObject()) {
		/* with mask*/
		FF_REQUIRE_INSTANCE(constructor, info[0], "mask", "Mat");
		matSelf.copyTo(matDst, FF_UNWRAP_MAT_AND_GET(info[0]->ToObject()));
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
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
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

NAN_METHOD(Mat::ConvertTo) {
	FF_REQUIRE_ARGS_OBJ("Mat::ConvertTo");

	int type;
	double alpha = 1.0, beta = 0.0;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, type, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, alpha, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, beta, IsNumber, NumberValue);
	v8::Local<v8::Object> jsMatConverted = FF_NEW(constructor);
	FF_UNWRAP_MAT_AND_GET(info.This()).convertTo(
		FF_UNWRAP_MAT_AND_GET(jsMatConverted),
		type,
		alpha,
		beta
	);
	info.GetReturnValue().Set(jsMatConverted);
}

/* #IFDEC IMGPROC */

NAN_METHOD(Mat::Rescale) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("Mat::Rescale - expected arg: factor");
  }
  double factor = (double)info[0]->NumberValue();
  v8::Local<v8::Object> jsMat = FF_NEW(constructor);
  cv::resize(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size(),
    factor,
    factor
  );
  info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::Resize) {
  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    return Nan::ThrowError("Mat::Resize - expected args: rows, cols");
  }
  int rows = (int)info[0]->NumberValue();
  int cols = (int)info[1]->NumberValue();
  v8::Local<v8::Object> jsMat = FF_NEW(constructor);
  cv::resize(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size(rows, cols)
  );
  info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::ResizeToMax) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("Mat::ResizeToMax - expected arg: maxRowsOrCols");
  }
  int maxRowsOrCols = (int)info[0]->NumberValue();
  cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
  double ratioY = (double)maxRowsOrCols / (double)mat.rows;
  double ratioX = (double)maxRowsOrCols / (double)mat.cols;
	double scale = std::min(ratioY, ratioX);

  v8::Local<v8::Object> jsMat = FF_NEW(constructor);
  cv::resize(
    mat,
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size((int)(mat.cols * scale), (int)(mat.rows * scale))
  );
  info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::Threshold) {
	FF_REQUIRE_ARGS_OBJ("Mat::Threshold");

	double thresh, maxVal;
	int type;
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, thresh, NumberValue);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, maxVal, NumberValue);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, type, Int32Value);

	v8::Local<v8::Object> jsMat = FF_NEW(constructor);
	cv::threshold(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		thresh,
		maxVal,
		type
	);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::CvtColor) {
	FF_REQUIRE_ARGS_OBJ("Mat::CvtColor");

	int code, dstCn;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, code, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, dstCn, IsInt32, Int32Value);
	v8::Local<v8::Object> jsMat = FF_NEW(constructor);
	cv::cvtColor(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		code,
		dstCn
	);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::BgrToGray) {
	v8::Local<v8::Object> jsMat = FF_NEW(constructor);
	cv::cvtColor(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		CV_BGR2GRAY
	);

	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Mat::WarpPerspective) {
	FF_REQUIRE_ARGS_OBJ("Mat::WarpPerspective");

	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	cv::Mat transformationMatrix;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, transformationMatrix, constructor, FF_UNWRAP_MAT_AND_GET, Mat);


	cv::Size size = cv::Size(matSelf.cols, matSelf.rows);
	if (FF_HAS_JS_PROP(args, size)) {
		Nan::ObjectWrap::Unwrap<Size>(FF_GET_JSPROP(args, size)->ToObject())->size;
	}
	int flags = cv::INTER_LINEAR;
	int borderMode = cv::BORDER_CONSTANT;
	// TODO borderValue
	const cv::Scalar& borderValue = cv::Scalar();

	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, flags, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, borderMode, IsInt32, Int32Value);

	v8::Local<v8::Object> jsMat = FF_NEW(constructor);
	cv::warpPerspective(matSelf, FF_UNWRAP_MAT_AND_GET(jsMat), transformationMatrix, size, flags, borderMode, borderValue);

	info.GetReturnValue().Set(jsMat);
}

void Mat::dilateOrErode(Nan::NAN_METHOD_ARGS_TYPE info, char* methodName, bool isErode = false) {
	FF_REQUIRE_ARGS_OBJ(methodName);
	v8::Local<v8::Object> jsKernel;
	cv::Point2i anchor(-1, -1);
	cv::Scalar borderValue = cv::morphologyDefaultBorderValue();
	int iterations = 1, borderType = 0;
	FF_GET_JSPROP_REQUIRED(args, jsKernel, kernel, ToObject);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, iterations, IsInt32, Int32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, borderType, IsInt32, Int32Value);
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	v8::Local<v8::Object> jsMatDst = FF_NEW(constructor);
	if (isErode) {
		FF_MAT_DILATE_OR_ERODE(cv::erode);
	}
	else {
		FF_MAT_DILATE_OR_ERODE(cv::dilate);
	}
	info.GetReturnValue().Set(jsMatDst);
}

NAN_METHOD(Mat::Dilate) {
	dilateOrErode(info, "Mat::Dilate");
}

NAN_METHOD(Mat::Erode) {
	dilateOrErode(info, "Mat::Erode", true);
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