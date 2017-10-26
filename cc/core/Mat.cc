#include "Mat.h"
#include "Point2.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "imgproc/Moments.h"
#include "imgproc/Contour.h"
#include "Converters.h"
#include "Workers.h"

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
	Nan::SetPrototypeMethod(ctor, "getDataAsync", GetData);
	Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
	Nan::SetPrototypeMethod(ctor, "getRegion", GetRegion);
	Nan::SetPrototypeMethod(ctor, "row", Row);
	Nan::SetPrototypeMethod(ctor, "copy", Copy);
	Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
	Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
	Nan::SetPrototypeMethod(ctor, "norm", Norm);
	Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
	Nan::SetPrototypeMethod(ctor, "splitChannels", SplitChannels);
	Nan::SetPrototypeMethod(ctor, "addWeighted", AddWeighted);
	Nan::SetPrototypeMethod(ctor, "minMaxLoc", MinMaxLoc);
	Nan::SetPrototypeMethod(ctor, "dct", Dct);
	Nan::SetPrototypeMethod(ctor, "dctAsync", DctAsync);
	Nan::SetPrototypeMethod(ctor, "idct", Idct);
	Nan::SetPrototypeMethod(ctor, "idctAsync", IdctAsync);
	Nan::SetPrototypeMethod(ctor, "dft", Dft);
	Nan::SetPrototypeMethod(ctor, "dftAsync", DftAsync);
	Nan::SetPrototypeMethod(ctor, "idft", Idft);
	Nan::SetPrototypeMethod(ctor, "idftAsync", IdftAsync);
	Nan::SetPrototypeMethod(ctor, "mulSpectrums", MulSpectrums);
	Nan::SetPrototypeMethod(ctor, "mulSpectrumsAsync", MulSpectrumsAsync);

	FF_PROTO_SET_MAT_OPERATIONS(ctor);

	/* imgproc */
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
	Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
	Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
	Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
	Nan::SetPrototypeMethod(ctor, "thresholdAsync", ThresholdAsync);
	Nan::SetPrototypeMethod(ctor, "adaptiveThreshold", AdaptiveThreshold);
	Nan::SetPrototypeMethod(ctor, "adaptiveThresholdAsync", AdaptiveThresholdAsync);
	Nan::SetPrototypeMethod(ctor, "inRange", InRange);
	Nan::SetPrototypeMethod(ctor, "inRangeAsync", InRangeAsync);
	Nan::SetPrototypeMethod(ctor, "warpAffine", WarpAffine);
	Nan::SetPrototypeMethod(ctor, "warpAffineAsync", WarpAffineAsync);
	Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
	Nan::SetPrototypeMethod(ctor, "warpPerspectiveAsync", WarpPerspectiveAsync);
	Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
	Nan::SetPrototypeMethod(ctor, "dilateAsync", DilateAsync);
	Nan::SetPrototypeMethod(ctor, "erode", Erode);
	Nan::SetPrototypeMethod(ctor, "erodeAsync", ErodeAsync);
	Nan::SetPrototypeMethod(ctor, "morphologyEx", MorphologyEx);
	Nan::SetPrototypeMethod(ctor, "morphologyExAsync", MorphologyExAsync);
	Nan::SetPrototypeMethod(ctor, "distanceTransform", DistanceTransform);
	Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabels", DistanceTransformWithLabels);
	Nan::SetPrototypeMethod(ctor, "blur", Blur);
	Nan::SetPrototypeMethod(ctor, "blurAsync", BlurAsync);
	Nan::SetPrototypeMethod(ctor, "gaussianBlur", GaussianBlur);
	Nan::SetPrototypeMethod(ctor, "gaussianBlurAsync", GaussianBlurAsync);
	Nan::SetPrototypeMethod(ctor, "medianBlur", MedianBlur);
	Nan::SetPrototypeMethod(ctor, "medianBlurAsync", MedianBlurAsync);
	Nan::SetPrototypeMethod(ctor, "connectedComponents", ConnectedComponents);
	Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStats", ConnectedComponentsWithStats);
	Nan::SetPrototypeMethod(ctor, "grabCut", GrabCut);
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);
	Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
	Nan::SetPrototypeMethod(ctor, "drawContours", DrawContours);
	Nan::SetPrototypeMethod(ctor, "drawLine", DrawLine);
	Nan::SetPrototypeMethod(ctor, "drawCircle", DrawCircle);
	Nan::SetPrototypeMethod(ctor, "drawRectangle", DrawRectangle);
	Nan::SetPrototypeMethod(ctor, "drawEllipse", DrawEllipse);
	Nan::SetPrototypeMethod(ctor, "putText", PutText);
	Nan::SetPrototypeMethod(ctor, "matchTemplate", MatchTemplate);
	Nan::SetPrototypeMethod(ctor, "matchTemplateAsync", MatchTemplateAsync);
	Nan::SetPrototypeMethod(ctor, "canny", Canny);
	Nan::SetPrototypeMethod(ctor, "cannyAsync", CannyAsync);
	Nan::SetPrototypeMethod(ctor, "sobel", Sobel);
	Nan::SetPrototypeMethod(ctor, "sobelAsync", SobelAsync);
	Nan::SetPrototypeMethod(ctor, "scharr", Scharr);
	Nan::SetPrototypeMethod(ctor, "scharrAsync", ScharrAsync);
	Nan::SetPrototypeMethod(ctor, "laplacian", Laplacian);
	Nan::SetPrototypeMethod(ctor, "laplacianAsync", LaplacianAsync);
	Nan::SetPrototypeMethod(ctor, "pyrDown", PyrDown);
	Nan::SetPrototypeMethod(ctor, "pyrDownAsync", PyrDownAsync);
	Nan::SetPrototypeMethod(ctor, "pyrUp", PyrUp);
	Nan::SetPrototypeMethod(ctor, "pyrUpAsync", PyrUpAsync);
	Nan::SetPrototypeMethod(ctor, "buildPyramid", BuildPyramid);
	Nan::SetPrototypeMethod(ctor, "buildPyramidAsync", BuildPyramidAsync);
	Nan::SetPrototypeMethod(ctor, "houghLines", HoughLines);
	Nan::SetPrototypeMethod(ctor, "houghLinesAsync", HoughLinesAsync);
	Nan::SetPrototypeMethod(ctor, "houghLinesP", HoughLinesP);
	Nan::SetPrototypeMethod(ctor, "houghLinesPAsync", HoughLinesPAsync);
	Nan::SetPrototypeMethod(ctor, "houghCircles", HoughCircles);
	Nan::SetPrototypeMethod(ctor, "houghCirclesAsync", HoughCirclesAsync);
	/* end imgproc */

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

struct Mat::GetDataWorker : SimpleWorker {
public:
	cv::Mat mat;

	GetDataWorker(cv::Mat mat) {
		this->mat = mat;
	}

	size_t size;
	char *data;

	const char* execute() {
		size = mat.rows * mat.cols * mat.elemSize();
		data = static_cast<char *>(malloc(size));
		memcpy(data, mat.data, size);
		return "";
	}

	FF_VAL getReturnValue() {
		return Nan::NewBuffer(data, size).ToLocalChecked();
	}
};

NAN_METHOD(Mat::GetData) {
	GetDataWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GetData", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::GetDataAsync) {
	GetDataWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GetDataAsync", GetDataWorker, worker);
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

NAN_METHOD(Mat::AddWeighted) {
	FF_METHOD_CONTEXT("Mat::AddWeighted");

	FF_ARG_NUMBER(0, double alpha);
	FF_ARG_INSTANCE(1, cv::Mat src2, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_NUMBER(2, double beta);
	FF_ARG_NUMBER(3, double gamma);
	FF_ARG_INT_IFDEF(4, int dtype, -1);

	FF_OBJ jsDstMat = FF_NEW_INSTANCE(constructor);
	cv::addWeighted(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		alpha,
		src2,
		beta,
		gamma,
		FF_UNWRAP_MAT_AND_GET(jsDstMat),
		dtype
	);

	FF_RETURN(jsDstMat);
}

NAN_METHOD(Mat::MinMaxLoc) {
	FF_METHOD_CONTEXT("Mat::MinMaxLoc");

	FF_ARG_INSTANCE_IFDEF(0, cv::Mat mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, cv::noArray().getMat());

	double minVal, maxVal;
	cv::Point2i minLoc, maxLoc;
	cv::minMaxLoc(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		&minVal,
		&maxVal,
		&minLoc,
		&maxLoc,
		mask
	);

	FF_OBJ jsMinLoc = FF_NEW_INSTANCE(Point2::constructor);
	FF_UNWRAP_PT2_AND_GET(jsMinLoc) = (cv::Point2d)minLoc;
	FF_OBJ jsMaxLoc = FF_NEW_INSTANCE(Point2::constructor);
	FF_UNWRAP_PT2_AND_GET(jsMaxLoc) = (cv::Point2d)maxLoc;

	FF_OBJ ret = FF_NEW_OBJ();
	Nan::Set(ret, FF_NEW_STRING("minVal"), Nan::New(minVal));
	Nan::Set(ret, FF_NEW_STRING("maxVal"), Nan::New(maxVal));
	Nan::Set(ret, FF_NEW_STRING("minLoc"), jsMinLoc);
	Nan::Set(ret, FF_NEW_STRING("maxLoc"), jsMaxLoc);

	FF_RETURN(ret);
}

struct Mat::DTWorker : public SimpleWorker {
public:
	cv::Mat mat;
	bool isInverse;

	DTWorker(cv::Mat mat, bool isInverse) {
		this->mat = mat;
		this->isInverse = isInverse;
	}

	int flags = 0;

	cv::Mat dst;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return false;
	}
};

struct Mat::DCTWorker : public DTWorker {
	DCTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
	}

	const char* execute() {
		if (isInverse) {
			cv::idct(mat, dst, flags);
		}
		else {
			cv::dct(mat, dst, flags);
		}
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::optArg(0, &flags, info);
	}
};

struct Mat::DFTWorker : public DTWorker {
	DFTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
	}

	int nonzeroRows = 0;

	const char* execute() {
		if (isInverse) {
			cv::idft(mat, dst, flags, nonzeroRows);
		}
		else {
			cv::dft(mat, dst, flags, nonzeroRows);
		}
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &flags, info) ||
			IntConverter::optArg(1, &nonzeroRows, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[0]->ToObject();
		return (
			IntConverter::optProp(&flags, "flags", opts) ||
			IntConverter::optProp(&nonzeroRows, "nonzeroRows", opts)
		);
	}
};

NAN_METHOD(Mat::Dct) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dct", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::DctAsync) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DctAsync", DCTWorker, worker);
}

NAN_METHOD(Mat::Idct) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Idct", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::IdctAsync) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::IdctAsync", DCTWorker, worker);
}

NAN_METHOD(Mat::Dft) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dft", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::DftAsync) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DftAsync", DFTWorker, worker);
}

NAN_METHOD(Mat::Idft) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Idft", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::IdftAsync) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::IdftAsync", DFTWorker, worker);
}

struct Mat::MulSpectrumsWorker {
public:
	cv::Mat mat;
	bool isInverse;

	MulSpectrumsWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Mat mat2;
	bool dftRows = false;
	bool conjB = false;

	cv::Mat dst;

	const char* execute() {
		int flags = (dftRows ? cv::DFT_ROWS : 0);
		cv::mulSpectrums(mat, mat2, dst, flags, conjB);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &mat2, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			BoolConverter::optArg(1, &dftRows, info) ||
			BoolConverter::optArg(2, &conjB, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			BoolConverter::optProp(&dftRows, "dftRows", opts) ||
			BoolConverter::optProp(&conjB, "conjB", opts)
		);
	}
};

NAN_METHOD(Mat::MulSpectrums) {
	MulSpectrumsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MulSpectrums", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MulSpectrumsAsync) {
	MulSpectrumsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MulSpectrumsAsync", MulSpectrumsWorker, worker);
}

/* imgproc */

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

struct Mat::ThresholdWorker : SimpleWorker {
public:
	cv::Mat mat;

	ThresholdWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double thresh;
	double maxVal;
	uint type;

	cv::Mat thresholdMat;

	const char* execute() {
		cv::threshold(mat, thresholdMat, thresh, maxVal, (int)type);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(thresholdMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &thresh, info) ||
			DoubleConverter::arg(1, &maxVal, info) ||
			UintConverter::arg(2, &type, info)
		);
	}
};

NAN_METHOD(Mat::Threshold) {
	ThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Threshold", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::ThresholdAsync) {
	ThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ThresholdAsync", ThresholdWorker, worker);
}

struct Mat::AdaptiveThresholdWorker : SimpleWorker {
public:
	cv::Mat mat;

	AdaptiveThresholdWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double maxVal;
	int adaptiveMethod;
	int thresholdType;
	int blockSize;
	double C;

	cv::Mat thresholdMat;

	const char* execute() {
		cv::adaptiveThreshold(mat, thresholdMat, maxVal, adaptiveMethod, thresholdType, blockSize, C);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(thresholdMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &maxVal, info) ||
			IntConverter::arg(1, &adaptiveMethod, info) ||
			IntConverter::arg(2, &thresholdType, info) ||
			IntConverter::arg(3, &blockSize, info) ||
			DoubleConverter::arg(4, &C, info)
			);
	}
};

NAN_METHOD(Mat::AdaptiveThreshold) {
	AdaptiveThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::AdaptiveThreshold", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::AdaptiveThresholdAsync) {
	AdaptiveThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::AdaptiveThresholdAsync", AdaptiveThresholdWorker, worker);
}

struct Mat::InRangeWorker : SimpleWorker {
public:
	cv::Mat mat;

	InRangeWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Vec3d lower;
	cv::Vec3d upper;

	cv::Mat inRangeMat;

	const char* execute() {
		cv::inRange(mat, lower, upper, inRangeMat);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(inRangeMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Vec3::Converter::arg(0, &lower, info) ||
			Vec3::Converter::arg(1, &upper, info)
		);
	}
};

NAN_METHOD(Mat::InRange) {
	InRangeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::InRange", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::InRangeAsync) {
	InRangeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::InRangeAsync", InRangeWorker, worker);
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

struct Mat::WarpWorker {
public:
	cv::Mat mat;

	WarpWorker(cv::Mat mat) {
		this->mat = mat;
		this->size = cv::Size2d(mat.cols, mat.rows);
	}

	cv::Mat transformationMatrix;
	cv::Size2d size;
	int flags = cv::INTER_LINEAR;
	int borderMode = cv::BORDER_CONSTANT;

	cv::Mat warpedMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(warpedMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &transformationMatrix, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(1, &size, info) ||
			IntConverter::optArg(2, &flags, info) ||
			IntConverter::optArg(3, &borderMode, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1) && !Size::Converter::hasInstance(info[1]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			Size::Converter::optProp(&size, "size", opts) ||
			IntConverter::optProp(&flags, "flags", opts) ||
			IntConverter::optProp(&borderMode, "borderMode", opts)
		);
	}
};

struct Mat::WarpAffineWorker : public WarpWorker {
	WarpAffineWorker(cv::Mat mat) : WarpWorker(mat) {
	}

	const char* execute() {
		cv::warpAffine(mat, warpedMat, transformationMatrix, (cv::Size)size, flags, borderMode, cv::Scalar());
		return "";
	}
};

NAN_METHOD(Mat::WarpAffine) {
	WarpAffineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::WarpAffine", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::WarpAffineAsync) {
	WarpAffineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::WarpAffineAsync", WarpAffineWorker, worker);
}

struct Mat::WarpPerspectiveWorker : public WarpWorker {
	WarpPerspectiveWorker(cv::Mat mat) : WarpWorker(mat) {
	}

	const char* execute() {
		cv::warpPerspective(mat, warpedMat, transformationMatrix, (cv::Size)size, flags, borderMode, cv::Scalar());
		return "";
	}
};

NAN_METHOD(Mat::WarpPerspective) {
	WarpPerspectiveWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::WarpPerspective", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::WarpPerspectiveAsync) {
	WarpPerspectiveWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::WarpPerspectiveAsync", WarpPerspectiveWorker, worker);
}


struct Mat::MorphWorker {
public:
	cv::Mat mat;
	bool withOp;

	MorphWorker(cv::Mat mat, bool withOp = false) {
		this->mat = mat;
		this->withOp = withOp;
	}

	cv::Mat kernel;

	int op;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	int iterations = 1;
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat resultMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &kernel, info) ||
			(withOp && IntConverter::optArg(1, &op, info))
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int off = (withOp ? 1 : 0);
		return (
			Point2::Converter::optArg(1 + off, &anchor, info) ||
			IntConverter::optArg(2 + off, &iterations, info) ||
			IntConverter::optArg(3 + off, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgN = (withOp ? 2 : 1);
		return FF_ARG_IS_OBJECT(optArgN) && !Point2::Converter::hasInstance(info[optArgN]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgN = (withOp ? 2 : 1);
		FF_OBJ opts = info[optArgN]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			IntConverter::optProp(&iterations, "iterations", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

struct Mat::ErodeWorker : public MorphWorker {
	ErodeWorker(cv::Mat mat) : MorphWorker(mat) {
	}

	const char* execute() {
		cv::erode(mat, resultMat, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(Mat::Erode) {
	ErodeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Erode", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::ErodeAsync) {
	ErodeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ErodeAsync", ErodeWorker, worker);
}


struct Mat::DilateWorker : public MorphWorker {
	DilateWorker(cv::Mat mat) : MorphWorker(mat) {
	}

	const char* execute() {
		cv::dilate(mat, resultMat, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(Mat::Dilate) {
	DilateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dilate", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::DilateAsync) {
	DilateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DilateAsync", DilateWorker, worker);
}


struct Mat::MorphologyExWorker : public MorphWorker {
public:
	MorphologyExWorker(cv::Mat mat) : MorphWorker(mat, true) {
	}

	const char* execute() {
		cv::morphologyEx(mat, resultMat, op, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(Mat::MorphologyEx) {
	MorphologyExWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MorphologyEx", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MorphologyExAsync) {
	MorphologyExWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MorphologyExAsync", MorphologyExWorker, worker);
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


struct Mat::BlurWorker {
public:
	cv::Mat mat;

	BlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Size2d kSize;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat blurMat;

	const char* execute() {
		cv::blur(mat, blurMat, kSize, anchor, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Size::Converter::arg(0, &kSize, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(1, &anchor, info) ||
			IntConverter::optArg(2, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1) && !Point2::Converter::hasInstance(info[1]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(Mat::Blur) {
	BlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Blur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::BlurAsync) {
	BlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BlurAsync", BlurWorker, worker);
}


struct Mat::GaussianBlurWorker {
public:
	cv::Mat mat;

	GaussianBlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Size2d kSize;
	double sigmaX;
	double sigmaY = 0;
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat blurMat;

	const char* execute() {
		cv::GaussianBlur(mat, blurMat, kSize, sigmaX, sigmaY, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::arg(0, &kSize, info) ||
			DoubleConverter::arg(1, &sigmaX, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(2, &sigmaY, info) ||
			IntConverter::optArg(3, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[2]->ToObject();
		return (
			DoubleConverter::optProp(&sigmaY, "sigmaY", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(Mat::GaussianBlur) {
	GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GaussianBlur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::GaussianBlurAsync) {
	GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GaussianBlurAsync", GaussianBlurWorker, worker);
}


struct Mat::MedianBlurWorker : public SimpleWorker {
public:
	cv::Mat mat;

	MedianBlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int kSize;

	cv::Mat blurMat;

	const char* execute() {
		cv::medianBlur(mat, blurMat, kSize);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &kSize, info);
	}
};

NAN_METHOD(Mat::MedianBlur) {
	MedianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MedianBlur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MedianBlurAsync) {
	MedianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MedianBlurAsync", MedianBlurWorker, worker);
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

NAN_METHOD(Mat::GrabCut) {
	FF_METHOD_CONTEXT("Mat::GrabCut");

	FF_ARG_INSTANCE(0, cv::Mat mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect rect, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	FF_ARG_INSTANCE(2, cv::Mat bgdModel, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(3, cv::Mat fgdModel, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INT(4, int iterCount);
	FF_ARG_INT(5, int mode);

	cv::grabCut(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		mask,
		rect,
		bgdModel,
		fgdModel,
		iterCount,
		mode
	);
	FF_RETURN(info.This());
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


struct Mat::MatchTemplateWorker : SimpleWorker {
public:
	cv::Mat mat;

	MatchTemplateWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Mat templ;
	int method;
	cv::Mat mask = cv::noArray().getMat();

	cv::Mat resultsMat;

	const char* execute() {
		cv::matchTemplate(mat, templ, resultsMat, method, mask);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultsMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &templ, info) ||
			IntConverter::arg(1, &method, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::optArg(2, &mask, info);
	}
};

NAN_METHOD(Mat::MatchTemplate) {
	MatchTemplateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MatchTemplate", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MatchTemplateAsync) {
	MatchTemplateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MatchTemplateAsync", MatchTemplateWorker, worker);
}


struct Mat::CannyWorker {
public:
	cv::Mat mat;

	CannyWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double threshold1;
	double threshold2;
	int apertureSize = 3;
	bool L2gradient = false;

	cv::Mat cannyMat;

	const char* execute() {
		cv::Canny(mat, cannyMat, threshold1, threshold2, apertureSize, L2gradient);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(cannyMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &threshold1, info) ||
			DoubleConverter::arg(1, &threshold2, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(2, &apertureSize, info) ||
			BoolConverter::optArg(3, &L2gradient, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[2]->ToObject();
		return (
			IntConverter::optProp(&apertureSize, "apertureSize", opts) ||
			BoolConverter::optProp(&L2gradient, "L2gradient", opts)
		);
	}
};

NAN_METHOD(Mat::Canny) {
	CannyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Canny", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::CannyAsync) {
	CannyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CannyAsync", CannyWorker, worker);
}


struct Mat::SobelScharrWorker {
public:
	cv::Mat mat;
	bool hasKsize;

	SobelScharrWorker(cv::Mat mat, bool hasKsize) {
		this->mat = mat;
		this->hasKsize = hasKsize;
	}

	int ddepth;
	int dx;
	int dy;
	int ksize = 3;
	double scale = 1.0;
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat resultMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &ddepth, info) ||
			IntConverter::arg(1, &dx, info) ||
			IntConverter::arg(2, &dy, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgIdx = hasKsize ? 3 : 2;
		return (
			(hasKsize && IntConverter::optArg(optArgIdx, &ksize, info)) ||
			DoubleConverter::optArg(optArgIdx + 1, &scale, info) ||
			DoubleConverter::optArg(optArgIdx + 2, &delta, info) ||
			IntConverter::optArg(optArgIdx + 3, &borderType, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			(hasKsize && IntConverter::optProp(&ksize, "ksize", opts)) ||
			DoubleConverter::optProp(&scale, "scale", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
			);
	}
};

struct Mat::SobelWorker : SobelScharrWorker {
	SobelWorker(cv::Mat mat, bool hasKsize) : SobelScharrWorker(mat, hasKsize) {
	}

	const char* execute() {
		cv::Sobel(mat, resultMat, ddepth, dx, dy, ksize, scale, delta, borderType);
		return "";
	}
};

NAN_METHOD(Mat::Sobel) {
	SobelWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Sobel", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::SobelAsync) {
	SobelWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::SobelAsync", SobelWorker, worker);
}

struct Mat::ScharrWorker : SobelScharrWorker {
	ScharrWorker(cv::Mat mat, bool hasKsize) : SobelScharrWorker(mat, hasKsize) {
	}

	const char* execute() {
		cv::Scharr(mat, resultMat, ddepth, dx, dy, scale, delta, borderType);
		return "";
	}
};

NAN_METHOD(Mat::Scharr) {
	ScharrWorker worker(Mat::Converter::unwrap(info.This()), false);
	FF_WORKER_SYNC("Mat::Scharr", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::ScharrAsync) {
	ScharrWorker worker(Mat::Converter::unwrap(info.This()), false);
	FF_WORKER_ASYNC("Mat::ScharrAsync", ScharrWorker, worker);
}


struct Mat::LaplacianWorker {
public:
	cv::Mat mat;

	LaplacianWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int ddepth;
	int ksize = 1;
	double scale = 1.0;
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat resultMat;

	const char* execute() {
		cv::Laplacian(mat, resultMat, ddepth, ksize, scale, delta, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &ddepth, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(1, &ksize, info) ||
			DoubleConverter::optArg(2, &scale, info) ||
			DoubleConverter::optArg(3, &delta, info) ||
			IntConverter::optArg(4, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			IntConverter::optProp(&ksize, "ksize", opts) ||
			DoubleConverter::optProp(&scale, "scale", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
			);
	}
};


NAN_METHOD(Mat::Laplacian) {
	LaplacianWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Laplacian", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::LaplacianAsync) {
	LaplacianWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::LaplacianAsync", LaplacianWorker, worker);
}


struct Mat::PyrWorker {
public:
	cv::Mat mat;
	bool isUp;

	PyrWorker(cv::Mat mat, bool isUp = false) {
		this->mat = mat;
		this->isUp = isUp;
	}

	cv::Size2d size = cv::Size2d();
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	const char* execute() {
		if (isUp) {
			cv::pyrUp(mat, dst, size, borderType);
		}
		else {
			cv::pyrDown(mat, dst, size, borderType);
		}
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return false;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(0, &size, info) ||
			IntConverter::optArg(1, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[0]->ToObject();
		return (
			Size::Converter::optProp(&size, "size", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(Mat::PyrDown) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PyrDown", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PyrDownAsync) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PyrDownAsync", PyrWorker, worker);
}

NAN_METHOD(Mat::PyrUp) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::PyrUp", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PyrUpAsync) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::PyrUpAsync", PyrWorker, worker);
}

struct Mat::BuildPyramidWorker : public SimpleWorker {
public:
	cv::Mat mat;

	BuildPyramidWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int maxlevel;
	int borderType = cv::BORDER_DEFAULT;

	std::vector<cv::Mat> dst;

	const char* execute() {
		cv::buildPyramid(mat, dst, maxlevel, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Mat, cv::Mat>::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &maxlevel, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::optArg(1, &borderType, info);
	}
};

NAN_METHOD(Mat::BuildPyramid) {
	BuildPyramidWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::BuildPyramid", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::BuildPyramidAsync) {
	BuildPyramidWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BuildPyramidAsync", BuildPyramidWorker, worker);
}

struct Mat::HoughLinesWorker {
public:
	cv::Mat mat;

	HoughLinesWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double rho;
	double theta;
	int threshold;
	double srn = 0;
	double stn = 0;
	double min_theta = 0;
	double max_theta = CV_PI;

	std::vector<cv::Vec2f> lines;

	const char* execute() {
		cv::HoughLines(mat, lines, rho, theta, threshold, srn, stn, min_theta, max_theta);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec2, cv::Vec2d, cv::Vec2f>::wrap(lines);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &rho, info) ||
			DoubleConverter::arg(1, &theta, info) ||
			IntConverter::arg(2, &threshold, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &srn, info) ||
			DoubleConverter::optArg(4, &stn, info) ||
			DoubleConverter::optArg(5, &min_theta, info) ||
			DoubleConverter::optArg(6, &max_theta, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&srn, "srn", opts) ||
			DoubleConverter::optProp(&stn, "stn", opts) ||
			DoubleConverter::optProp(&min_theta, "min_theta", opts) ||
			DoubleConverter::optProp(&max_theta, "max_theta", opts)
		);
	}
};

NAN_METHOD(Mat::HoughLines) {
	HoughLinesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughLines", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::HoughLinesAsync) {
	HoughLinesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughLinesAsync", HoughLinesWorker, worker);
}

struct Mat::HoughLinesPWorker : public HoughLinesWorker {
public:
	HoughLinesPWorker(cv::Mat mat) : HoughLinesWorker(mat) {
	}

	double minLineLength = 0;
	double maxLineGap = 0;

	std::vector<cv::Vec4f> linesP;

	const char* execute() {
		cv::HoughLinesP(mat, linesP, rho, theta, threshold, minLineLength, maxLineGap);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec4, cv::Vec4d, cv::Vec4f>::wrap(linesP);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &minLineLength, info) ||
			DoubleConverter::optArg(4, &maxLineGap, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&minLineLength, "minLineLength", opts) ||
			DoubleConverter::optProp(&maxLineGap, "maxLineGap", opts)
		);
	}
};

NAN_METHOD(Mat::HoughLinesP) {
	HoughLinesPWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughLinesP", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::HoughLinesPAsync) {
	HoughLinesPWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughLinesPAsync", HoughLinesPWorker, worker);
}

/* end imgproc */

struct Mat::HoughCirclesWorker {
public:
	cv::Mat mat;

	HoughCirclesWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int method;
	double dp;
	double minDist;
	double param1 = 100;
	double param2 = 100;
	int minRadius = 0;
	int maxRadius = 0;

	std::vector<cv::Vec3f> circles;

	const char* execute() {
		cv::HoughCircles(mat, circles, method, dp, minDist, param1, param2, minRadius, maxRadius);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec3, cv::Vec3d, cv::Vec3f>::wrap(circles);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &method, info) ||
			DoubleConverter::arg(1, &dp, info) ||
			DoubleConverter::arg(2, &minDist, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &param1, info) ||
			DoubleConverter::optArg(4, &param2, info) ||
			IntConverter::optArg(5, &minRadius, info) ||
			IntConverter::optArg(6, &maxRadius, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&param1, "param1", opts) ||
			DoubleConverter::optProp(&param2, "param2", opts) ||
			IntConverter::optProp(&minRadius, "minRadius", opts) ||
			IntConverter::optProp(&maxRadius, "maxRadius", opts)
		);
	}
};

NAN_METHOD(Mat::HoughCircles) {
	HoughCirclesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughCircles", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::HoughCirclesAsync) {
	HoughCirclesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughCirclesAsync", HoughCirclesWorker, worker);
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

void Mat::setNativeProps(cv::Mat mat) {
	this->mat = mat;
};