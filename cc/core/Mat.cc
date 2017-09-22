#include "Mat.h"
#include "Point2.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Moments.h"
#include "imgproc/Contour.h"

Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

NAN_MODULE_INIT(Mat::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Mat::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Mat").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rows").ToLocalChecked(), Mat::GetRows);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("cols").ToLocalChecked(), Mat::GetCols);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), Mat::GetType);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("channels").ToLocalChecked(), Mat::GetChannels);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("dims").ToLocalChecked(), Mat::GetDims);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("depth").ToLocalChecked(), Mat::GetDepth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("empty").ToLocalChecked(), Mat::GetIsEmpty);

	Nan::SetPrototypeMethod(ctor, "at", At);
	Nan::SetPrototypeMethod(ctor, "atRaw", AtRaw);
	Nan::SetPrototypeMethod(ctor, "set", Set);
	Nan::SetPrototypeMethod(ctor, "getData", GetData);
	Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
	Nan::SetPrototypeMethod(ctor, "getRegion", GetRegion);
	Nan::SetPrototypeMethod(ctor, "row", Row);
	Nan::SetPrototypeMethod(ctor, "copy", Copy);
	Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
	Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
	Nan::SetPrototypeMethod(ctor, "norm", Norm);
	Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
	Nan::SetPrototypeMethod(ctor, "splitChannels", SplitChannels);

	FF_PROTO_SET_MAT_OPERATIONS(ctor);

	/* #IFDEF IMGPROC */
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
	Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
	Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
	Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
	Nan::SetPrototypeMethod(ctor, "inRange", InRange);
	Nan::SetPrototypeMethod(ctor, "warpAffine", WarpAffine);
	Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
	Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
	Nan::SetPrototypeMethod(ctor, "erode", Erode);
	Nan::SetPrototypeMethod(ctor, "distanceTransform", DistanceTransform);
	Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabels", DistanceTransformWithLabels);
	Nan::SetPrototypeMethod(ctor, "blur", Blur);
	Nan::SetPrototypeMethod(ctor, "gaussianBlur", GaussianBlur);
	Nan::SetPrototypeMethod(ctor, "medianBlur", MedianBlur);
	Nan::SetPrototypeMethod(ctor, "connectedComponents", ConnectedComponents);
	Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStats", ConnectedComponentsWithStats);
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);
	Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
	Nan::SetPrototypeMethod(ctor, "drawContours", DrawContours);
	Nan::SetPrototypeMethod(ctor, "drawLine", DrawLine);
	Nan::SetPrototypeMethod(ctor, "drawCircle", DrawCircle);
	Nan::SetPrototypeMethod(ctor, "drawRectangle", DrawRectangle);
	Nan::SetPrototypeMethod(ctor, "drawEllipse", DrawEllipse);
	Nan::SetPrototypeMethod(ctor, "putText", PutText);
	/* #ENDIF IMGPROC */

  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

// TODO type undefined throw error
NAN_METHOD(Mat::New) {
	Mat* self = new Mat();
	/* from channels */
	if (info.Length() == 1 && info[0]->IsArray()) {
		FF_ARR jsChannelMats = FF_ARR::Cast(info[0]);
		std::vector<cv::Mat> channels;
		for (int i = 0; i < jsChannelMats->Length(); i++) {
			FF_OBJ jsChannelMat = FF_CAST_OBJ(jsChannelMats->Get(i));
			FF_REQUIRE_INSTANCE(constructor, jsChannelMat,
				FF_NEW_STRING("expected channel " + std::to_string(i) + " to be an instance of Mat"));
			cv::Mat channelMat = FF_UNWRAP_MAT_AND_GET(jsChannelMat);
			channels.push_back(channelMat);
			if (i > 0) {
				FF_ASSERT_EQUALS(channels.at(i - 1).rows, channelMat.rows, "Mat::New - rows", " at channel " + std::to_string(i));
				FF_ASSERT_EQUALS(channels.at(i - 1).cols, channelMat.cols, "Mat::New - cols", " at channel " + std::to_string(i));
			}
		}
		cv::Mat mat;
		cv::merge(channels, mat);
		self->setNativeProps(mat);
	}
	/* data array, type */
	else if (info.Length() == 2 && info[0]->IsArray() && info[1]->IsInt32()) {
		FF_ARR rowArray = FF_ARR::Cast(info[0]);
		int type = info[1]->Int32Value();

		int numCols = -1;
		for (uint i = 0; i < rowArray->Length(); i++) {
			if (!rowArray->Get(i)->IsArray()) {
				return Nan::ThrowError(Nan::New("Mat::New - Column should be an array, at column: " + std::to_string(i)).ToLocalChecked());
			}
			FF_ARR colArray = FF_ARR::Cast(rowArray->Get(i));
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
		int type = info[2]->Int32Value();
		cv::Mat mat(info[0]->Int32Value(), info[1]->Int32Value(), type);
		/* fill vector */
		// TODO by Vec
		if (info[3]->IsArray()) {
			FF_ARR vec = FF_ARR::Cast(info[3]);
			if (mat.channels() != vec->Length()) {
				return Nan::ThrowError(FF_NEW_STRING(
					std::string("Mat::New - number of channels (") + std::to_string(mat.channels())
					+ std::string(") do not match fill vector length ") + std::to_string(vec->Length()))
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
		int type = info[3]->Int32Value();
		char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject()));
		cv::Mat mat(info[1]->Int32Value(), info[2]->Int32Value(), type);
		size_t size = mat.rows * mat.cols * mat.elemSize();
		memcpy(mat.data, data, size);
		self->setNativeProps(mat);
	}
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
}

NAN_METHOD(Mat::At) {
	FF_METHOD_CONTEXT("Mat::At");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	v8::Local<v8::Value> jsVal;
	if (val->IsArray()) {
		FF_ARR vec = FF_ARR::Cast(val);
		FF_OBJ jsVec;
		if (vec->Length() == 2) {
			jsVec = FF_NEW_INSTANCE(Vec2::constructor);
			FF_UNWRAP_VEC2(jsVec)->vec = cv::Vec2d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue());
		}
		else if (vec->Length() == 3) {
			jsVec = FF_NEW_INSTANCE(Vec3::constructor);
			FF_UNWRAP_VEC3(jsVec)->vec = cv::Vec3d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue());
		}
		else {
			jsVec = FF_NEW_INSTANCE(Vec4::constructor);
			FF_UNWRAP_VEC4(jsVec)->vec = cv::Vec4d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue(), vec->Get(3)->NumberValue());
		}
		jsVal = jsVec;
	}
	else {
		jsVal = v8::Local<v8::Value>::Cast(val);
	}
	FF_RETURN(jsVal);
}

NAN_METHOD(Mat::AtRaw) {
	FF_METHOD_CONTEXT("Mat::AtRaw");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	FF_RETURN(val);
}

NAN_METHOD(Mat::Set) {
	FF_METHOD_CONTEXT("Mat::Set");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::Set row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::Set col");

	int cn = matSelf.channels();
	if (info[2]->IsArray()) {
		FF_ARR vec = FF_ARR::Cast(info[2]);
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
		return Nan::ThrowError(FF_NEW_STRING("Mat::Set - unexpected argument 2"));
	}
}

NAN_METHOD(Mat::GetData) {
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	size_t size = matSelf.rows * matSelf.cols * matSelf.elemSize();
	char *data = static_cast<char *>(malloc(size));
	memcpy(data, matSelf.data, size);
	FF_RETURN(Nan::NewBuffer(data, size).ToLocalChecked());
}

NAN_METHOD(Mat::GetDataAsArray) {
	cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ARR rowArray = FF_NEW_ARRAY(mat.rows);
	FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
	FF_RETURN(rowArray);
}

NAN_METHOD(Mat::GetRegion) {
	if (!FF_IS_INSTANCE(Rect::constructor, info[0])) {
		Nan::ThrowError("Mat::GetRegion expected arg0 to be an instance of Rect");
	}
	cv::Rect2d rect = FF_UNWRAP(info[0]->ToObject(), Rect)->rect;
	FF_OBJ jsRegion = FF_NEW_INSTANCE(constructor);
	FF_UNWRAP_MAT_AND_GET(jsRegion) = FF_UNWRAP_MAT_AND_GET(info.This())(rect);
	FF_RETURN(jsRegion);
}

NAN_METHOD(Mat::Copy) {
	FF_METHOD_CONTEXT("Mat::Copy");

	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	cv::Mat matDst = cv::Mat::zeros(matSelf.size(), matSelf.type());
	if (info.Length() > 0) {
		/* with mask*/
		FF_ARG_INSTANCE(0, cv::Mat mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		matSelf.copyTo(matDst, mask);
	}
	else {
		matSelf.copyTo(matDst);
	}
	FF_OBJ jsMatDst = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMatDst) = matDst;
	FF_RETURN(jsMatDst);
}

NAN_METHOD(Mat::CopyTo) {
	FF_METHOD_CONTEXT("Mat::CopyTo");

	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ARG_INSTANCE(0, cv::Mat dst, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	if (info.Length() > 1) {
		/* with mask*/
		FF_ARG_INSTANCE(1, cv::Mat mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		matSelf.copyTo(dst, mask);
	}
	else {
		matSelf.copyTo(dst);
	}
	FF_RETURN(info[0]);
}

NAN_METHOD(Mat::ConvertTo) {
	FF_METHOD_CONTEXT("Mat::ConvertTo");

	// required args
	FF_ARG_UINT(0, uint type);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();
	FF_GET_NUMBER_IFDEF(optArgs, double alpha, "alpha", 1.0);
	FF_GET_NUMBER_IFDEF(optArgs, double beta, "beta", 0.0);
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, alpha, 1.0);
		FF_ARG_NUMBER_IFDEF(2, beta, 0.0);
	}

	FF_OBJ jsMatConverted = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(info.This()).convertTo(
		FF_UNWRAP_MAT_AND_GET(jsMatConverted),
		(int)type,
		alpha,
		beta
	);
	FF_RETURN(jsMatConverted);
}


NAN_METHOD(Mat::Norm) {
	FF_METHOD_CONTEXT("Mat::Norm");

	bool withSrc2 = FF_HAS_ARG(0) && FF_IS_INSTANCE(Mat::constructor, info[0]);
	uint i = withSrc2 ? 1 : 0;
	double norm;

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(i) && info[i]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[i]->ToObject() : FF_NEW_OBJ();
	FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(i, normType, normType);
		FF_ARG_INSTANCE_IFDEF(i + 1, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
	}

	if (withSrc2) {
		FF_ARG_INSTANCE(0, cv::Mat src2, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), src2, (int)normType, mask);
	}
	else {
		norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), (int)normType, mask);
	}
	FF_RETURN(norm);
}

NAN_METHOD(Mat::Normalize) {
	FF_METHOD_CONTEXT("Mat::Normalize");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();
	FF_GET_NUMBER_IFDEF(optArgs, double alpha, "alpha", 1.0);
	FF_GET_NUMBER_IFDEF(optArgs, double beta, "beta", 0.0);
	FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
	FF_GET_UINT_IFDEF(optArgs, int dtype, "dtype", -1);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(0, alpha, 1.0);
		FF_ARG_NUMBER_IFDEF(1, beta, 0.0);
		FF_ARG_UINT_IFDEF(3, normType, normType);
		FF_ARG_INT_IFDEF(4, dtype, dtype);
		FF_ARG_INSTANCE_IFDEF(5, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::normalize(FF_UNWRAP_MAT_AND_GET(info.This()), FF_UNWRAP_MAT_AND_GET(jsMat), alpha, beta, normType, dtype, mask);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::SplitChannels) {
	std::vector<cv::Mat> channels;
	cv::split(FF_UNWRAP_MAT_AND_GET(info.This()), channels);
	FF_ARR jsChannelMats = FF_NEW_ARRAY(channels.size());
	for (int i = 0; i < channels.size(); i++) {
		FF_OBJ jsChannelMat = FF_NEW_INSTANCE(constructor);
		FF_UNWRAP_MAT_AND_GET(jsChannelMat) = channels.at(i);
		jsChannelMats->Set(i, jsChannelMat);
	}
	FF_RETURN(jsChannelMats);
}

/* #IFDEC IMGPROC */

NAN_METHOD(Mat::Rescale) {
	FF_METHOD_CONTEXT("Mat::Rescale");

	FF_ARG_NUMBER(0, double factor);

  FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
  cv::resize(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size(),
    factor,
    factor
  );
  FF_RETURN(jsMat);
}

NAN_METHOD(Mat::Resize) {
	FF_METHOD_CONTEXT("Mat::Resize");

	FF_ARG_UINT(0, uint rows);
	FF_ARG_UINT(1, uint cols);

  FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
  cv::resize(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size((int)rows, (int)cols)
  );
  FF_RETURN(jsMat);
}

NAN_METHOD(Mat::ResizeToMax) {
	FF_METHOD_CONTEXT("Mat::ResizeToMax");

	FF_ARG_UINT(0, uint maxRowsOrCols);
  cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
  double ratioY = (double)maxRowsOrCols / (double)mat.rows;
  double ratioX = (double)maxRowsOrCols / (double)mat.cols;
	double scale = (std::min)(ratioY, ratioX);

  FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
  cv::resize(
    mat,
		FF_UNWRAP_MAT_AND_GET(jsMat),
    cv::Size((int)(mat.cols * scale), (int)(mat.rows * scale))
  );
  FF_RETURN(jsMat);
}

NAN_METHOD(Mat::Threshold) {
	FF_METHOD_CONTEXT("Mat::Threshold");


	FF_ARG_NUMBER(0, double thresh);
	FF_ARG_NUMBER(1, double maxVal);
	FF_ARG_UINT(2, uint type);

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::threshold(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		thresh,
		maxVal,
		(int)type
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::InRange) {
	FF_METHOD_CONTEXT("Mat::InRange");

	FF_ARG_INSTANCE(0, cv::Vec3d lower, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);
	FF_ARG_INSTANCE(1, cv::Vec3d upper, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::inRange(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		lower,
		upper,
		FF_UNWRAP_MAT_AND_GET(jsMat)
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::CvtColor) {
	FF_METHOD_CONTEXT("Mat::CvtColor");

	FF_ARG_UINT(0, uint code);
	FF_ARG_UINT_IFDEF(1, uint dstCn, 0);

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::cvtColor(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		(int)code,
		(int)dstCn
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::BgrToGray) {
	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::cvtColor(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		CV_BGR2GRAY
	);

	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::WarpAffine) {
	Nan::TryCatch tryCatch;
	warp(info, "Mat::WarpAffine", &cv::warpAffine);
	if (tryCatch.HasCaught()) {
		tryCatch.ReThrow();
	}
}

NAN_METHOD(Mat::WarpPerspective) {
	Nan::TryCatch tryCatch;
	warp(info, "Mat::WarpPerspective", &cv::warpPerspective);
	if (tryCatch.HasCaught()) {
		tryCatch.ReThrow();
	}
}

NAN_METHOD(Mat::Dilate) {
	Nan::TryCatch tryCatch;
	morph(info, "Mat::Dilate", cv::dilate);
	if (tryCatch.HasCaught()) {
		tryCatch.ReThrow();
	}
}

NAN_METHOD(Mat::Erode) {
	Nan::TryCatch tryCatch;
	morph(info, "Mat::Erode", cv::erode);
	if (tryCatch.HasCaught()) {
		tryCatch.ReThrow();
	}
}

NAN_METHOD(Mat::DistanceTransform) {
	FF_METHOD_CONTEXT("Mat::DistanceTransform");

	FF_ARG_UINT(0, uint distanceType);
	FF_ARG_UINT(1, uint maskSize);
	FF_ARG_UINT_IFDEF(2, uint dstType, CV_32F);

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::distanceTransform(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		(int)distanceType,
		(int)maskSize,
		(int)dstType
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::DistanceTransformWithLabels) {
	FF_METHOD_CONTEXT("Mat::DistanceTransformWithLabels");

	FF_ARG_UINT(0, uint distanceType);
	FF_ARG_UINT(1, uint maskSize);
	FF_ARG_UINT_IFDEF(2, uint labelType, cv::DIST_LABEL_CCOMP);

	FF_OBJ jsDst = FF_NEW_INSTANCE(constructor);
	FF_OBJ jsLabels = FF_NEW_INSTANCE(constructor);
	cv::distanceTransform(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsDst),
		FF_UNWRAP_MAT_AND_GET(jsLabels),
		(int)distanceType,
		(int)maskSize,
		(int)labelType
	);

	FF_OBJ ret = FF_NEW_OBJ();
	Nan::Set(ret, FF_NEW_STRING("labels"), jsLabels);
	Nan::Set(ret, FF_NEW_STRING("dist"), jsDst);
	FF_RETURN(ret);
}

NAN_METHOD(Mat::Blur) {
	FF_METHOD_CONTEXT("Mat::Blur");

	FF_ARG_INSTANCE(0, cv::Size kSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Point2d anchor, "anchor", Point2::constructor, FF_UNWRAP_PT2_AND_GET, Point2, cv::Point2d(-1, -1));
	FF_GET_UINT_IFDEF(optArgs, uint borderType, "borderType", cv::BORDER_CONSTANT);
	if (!hasOptArgsObj) {
		FF_ARG_INSTANCE_IFDEF(1, anchor, Point2::constructor, FF_UNWRAP_PT2_AND_GET, anchor);
		FF_ARG_UINT_IFDEF(2, borderType, borderType);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::blur(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		kSize,
		anchor,
		borderType
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::GaussianBlur) {
	FF_METHOD_CONTEXT("Mat::GaussianBlur");

	FF_ARG_INSTANCE(0, cv::Size kSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET);
	FF_ARG_NUMBER(1, double sigmaX);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();
	FF_GET_NUMBER_IFDEF(optArgs, double sigmaY, "sigmaY", 0.0);
	FF_GET_UINT_IFDEF(optArgs, uint borderType, "borderType", cv::BORDER_CONSTANT);
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(2, sigmaY, sigmaY);
		FF_ARG_NUMBER_IFDEF(3, borderType, borderType);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::GaussianBlur(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		kSize,
		sigmaX,
		sigmaY,
		borderType
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::MedianBlur) {
	FF_METHOD_CONTEXT("Mat::MedianBlur");

	FF_ARG_UINT(0, uint kSize);

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::medianBlur(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		(int)kSize
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::ConnectedComponents) {
	FF_METHOD_CONTEXT("Mat::ConnectedComponents");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();
	FF_GET_UINT_IFDEF(optArgs, uint connectivity, "connectivity", 8);
	FF_GET_UINT_IFDEF(optArgs, uint ltype, "ltype", CV_32S);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(0, connectivity, connectivity);
		FF_ARG_UINT_IFDEF(1, ltype, ltype);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::connectedComponents(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsMat),
		(int)connectivity,
		(int)ltype
	);
	FF_RETURN(jsMat);
}

NAN_METHOD(Mat::ConnectedComponentsWithStats) {
	FF_METHOD_CONTEXT("Mat::ConnectedComponentsWithStats");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();
	FF_GET_UINT_IFDEF(optArgs, uint connectivity, "connectivity", 8);
	FF_GET_UINT_IFDEF(optArgs, uint ltype, "ltype", CV_32S);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(0, connectivity, connectivity);
		FF_ARG_UINT_IFDEF(1, ltype, ltype);
	}

	FF_OBJ jsLabels = FF_NEW_INSTANCE(constructor);
	FF_OBJ jsStats = FF_NEW_INSTANCE(constructor);
	FF_OBJ jsCentroids = FF_NEW_INSTANCE(constructor);
	cv::connectedComponentsWithStats(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		FF_UNWRAP_MAT_AND_GET(jsLabels),
		FF_UNWRAP_MAT_AND_GET(jsStats),
		FF_UNWRAP_MAT_AND_GET(jsCentroids),
		(int)connectivity,
		(int)ltype
	);

	FF_OBJ ret = FF_NEW_OBJ();
	Nan::Set(ret, FF_NEW_STRING("labels"), jsLabels);
	Nan::Set(ret, FF_NEW_STRING("stats"), jsStats);
	Nan::Set(ret, FF_NEW_STRING("centroids"), jsCentroids);
	FF_RETURN(ret);
}

NAN_METHOD(Mat::_Moments) {
	FF_OBJ jsMoments = FF_NEW_INSTANCE(Moments::constructor);
	FF_UNWRAP(jsMoments, Moments)->moments = cv::moments(FF_UNWRAP_MAT_AND_GET(info.This()));
	FF_RETURN(jsMoments);
}

NAN_METHOD(Mat::FindContours) {
	FF_METHOD_CONTEXT("Mat::FindContours");

	FF_ARG_UINT(0, uint mode);
	FF_ARG_UINT(1, uint method);
	FF_ARG_INSTANCE_IFDEF(2, cv::Point2d offset, Point2::constructor, FF_UNWRAP_PT2_AND_GET, cv::Point2d());

	std::vector<cv::Mat> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		contours,
		hierarchy,
		(int)mode,
		(int)method,
		offset
	);

	FF_ARR jsContours = FF_NEW_ARRAY(contours.size());
	for (uint i = 0; i < jsContours->Length(); i++) {
		FF_OBJ jsContour = FF_NEW_INSTANCE(Contour::constructor);
		FF_UNWRAP(jsContour, Contour)->contour = contours.at(i);
		FF_UNWRAP(jsContour, Contour)->hierarchy = hierarchy.at(i);
		jsContours->Set(i, jsContour);
	}

	FF_RETURN(jsContours);
}

NAN_METHOD(Mat::DrawContours) {
	FF_METHOD_CONTEXT("Mat::DrawContours");

	FF_ARG_ARRAY(0, FF_ARR jsContours);
	FF_ARG_INSTANCE(1, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();
	FF_GET_UINT_IFDEF(optArgs, uint contourIdx, "contourIdx", 0);
	FF_GET_INT_IFDEF(optArgs, int maxLevel, "maxLevel", INT_MAX);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Point2d offset, "offset", Point2::constructor, FF_UNWRAP_PT2_AND_GET, Point2, cv::Point2d());
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(2, contourIdx, contourIdx);
		FF_ARG_UINT_IFDEF(3, maxLevel, maxLevel);
		FF_ARG_INSTANCE_IFDEF(4, offset, Point2::constructor, FF_UNWRAP_PT2_AND_GET, offset);
		FF_ARG_INT_IFDEF(5, lineType, lineType);
		FF_ARG_INT_IFDEF(6, thickness, thickness);
	}

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	for (int i = 0; i < jsContours->Length(); i++) {
		FF_OBJ jsContour = jsContours->Get(i)->ToObject();
		contours.push_back(FF_UNWRAP_CONTOUR_AND_GET(jsContour));
		hierarchy.push_back(FF_UNWRAP_CONTOUR(jsContour)->hierarchy);
	}

	cv::drawContours(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		contours,
		(int)contourIdx,
		color,
		thickness,
		lineType,
		hierarchy,
		(int)maxLevel,
		offset
	);
	FF_RETURN(info.This());
}

NAN_METHOD(Mat::DrawLine) {
	FF_METHOD_CONTEXT("Mat::DrawLine");

	FF_ARG_INSTANCE(0, cv::Point2d pt1, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(1, cv::Point2d pt2, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::line(FF_UNWRAP_MAT_AND_GET(info.This()), pt1, pt2, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(Mat::DrawCircle) {
	FF_METHOD_CONTEXT("Mat::DrawCircle");

	FF_ARG_INSTANCE(0, cv::Point2d center, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_UINT(1, uint radius);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::circle(FF_UNWRAP_MAT_AND_GET(info.This()), center, (int)radius, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(Mat::DrawRectangle) {
	FF_METHOD_CONTEXT("Mat::DrawRectangle");

	FF_ARG_INSTANCE(0, cv::Point2d pt1, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(1, cv::Point2d pt2, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::rectangle(FF_UNWRAP_MAT_AND_GET(info.This()), pt1, pt2, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(Mat::DrawEllipse) {
	FF_METHOD_CONTEXT("Mat::DrawEllipse");

	FF_ARG_INSTANCE(0, cv::RotatedRect box, RotatedRect::constructor, FF_UNWRAP_ROTATEDRECT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(2, lineType, lineType);
		FF_ARG_INT_IFDEF(3, thickness, thickness);
	}

	cv::ellipse(FF_UNWRAP_MAT_AND_GET(info.This()), box, color, thickness, lineType);
	FF_RETURN(info.This());
}

NAN_METHOD(Mat::PutText) {
	FF_METHOD_CONTEXT("Mat::PutText");

	FF_ARG_STRING(0, std::string text);
	FF_ARG_INSTANCE(1, cv::Point2d org, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_UINT(2, uint fontFace);
	FF_ARG_NUMBER(3, double fontScale);
	FF_ARG_INSTANCE(4, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(5) && info[5]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[5]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_BOOL_IFDEF(optArgs, bool bottomLeftOrigin, "bottomLeftOrigin", false);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(5, lineType, lineType);
		FF_ARG_INT_IFDEF(6, thickness, thickness);
		FF_ARG_INT_IFDEF(7, bottomLeftOrigin, bottomLeftOrigin);
	}

	cv::putText(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		text,
		org,
		(int)fontFace,
		fontScale,
		color,
		thickness,
		lineType,
		bottomLeftOrigin
	);
	FF_RETURN(info.This());
}

/* #ENDIF IMGPROC */

NAN_METHOD(Mat::Row) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: row(int r)");
  }
  int r = (int)info[0]->NumberValue();
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
  FF_ARR row = FF_NEW_ARRAY(mat.cols);
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
        FF_ARR jsVec = FF_NEW_ARRAY(3);
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
  FF_RETURN(row);
}

void Mat::warp(Nan::NAN_METHOD_ARGS_TYPE info, const char* methodName, void(*func)(cv::InputArray, cv::OutputArray, cv::InputArray, cv::Size, int, int, const cv::Scalar&)) {
	FF_METHOD_CONTEXT("Mat::WarpAffine");
	cv::Mat self = FF_UNWRAP_MAT_AND_GET(info.This());

	FF_ARG_INSTANCE(0, cv::Mat transformationMatrix, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && !FF_IS_INSTANCE(Size::constructor, info[1]);
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d size, "size", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(self.cols, self.rows));
	FF_GET_UINT_IFDEF(optArgs, int flags, "flags", cv::INTER_LINEAR);
	FF_GET_UINT_IFDEF(optArgs, int borderMode, "borderMode", cv::BORDER_CONSTANT);
	if (!hasOptArgsObj) {
		FF_ARG_INSTANCE_IFDEF(1, size, Size::constructor, FF_UNWRAP_SIZE_AND_GET, size);
		FF_ARG_UINT_IFDEF(2, flags, flags);
		FF_ARG_UINT_IFDEF(3, borderMode, borderMode);
	}
	// TODO borderValue
	const cv::Scalar& borderValue = cv::Scalar();

	FF_OBJ jsWarped = FF_NEW_INSTANCE(Mat::constructor);
	func(
		self,
		FF_UNWRAP_MAT_AND_GET(jsWarped),
		transformationMatrix,
		(cv::Size)size,
		flags,
		borderMode,
		borderValue
	);
	FF_RETURN(jsWarped);
}

void Mat::morph(Nan::NAN_METHOD_ARGS_TYPE info, const char* methodName, void(*func)(cv::InputArray, cv::OutputArray, cv::InputArray, cv::Point, int, int, const cv::Scalar&)) {
	FF_METHOD_CONTEXT(methodName);
	FF_ARG_INSTANCE(0, cv::Mat kernel, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Point2d anchor, "anchor", Point2::constructor, FF_UNWRAP_PT2_AND_GET, Point2, cv::Point2d(-1, -1));
	FF_GET_UINT_IFDEF(optArgs, uint iterations, "iterations", 1);
	FF_GET_UINT_IFDEF(optArgs, uint borderType, "borderType", cv::BORDER_CONSTANT);

	if (!hasOptArgsObj) {
		FF_ARG_INSTANCE_IFDEF(1, anchor, Point2::constructor, FF_UNWRAP_PT2_AND_GET, anchor);
		FF_ARG_UINT_IFDEF(2, iterations, iterations);
		FF_ARG_UINT_IFDEF(3, borderType, borderType);
	}

	cv::Scalar borderValue = cv::morphologyDefaultBorderValue();
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_OBJ jsMatDst = FF_NEW_INSTANCE(constructor);
	func(matSelf, FF_UNWRAP_MAT_AND_GET(jsMatDst), kernel, anchor, iterations, borderType, borderValue);
	FF_RETURN(jsMatDst);
}

void Mat::setNativeProps(cv::Mat mat) {
	this->mat = mat;
};