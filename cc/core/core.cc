#include "core.h"
#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "TermCriteria.h"

NAN_MODULE_INIT(Core::Init) {
  Mat::Init(target);
	Point::Init(target);
	Vec::Init(target);
	Size::Init(target);
	Rect::Init(target);
	RotatedRect::Init(target);
	TermCriteria::Init(target);

	Nan::SetMethod(target, "partition", Partition);
	Nan::SetMethod(target, "kmeans", Kmeans);
};

struct Predicate {
	v8::Local<v8::Function> cb;

	Predicate(v8::Local<v8::Function> _cb) {
		cb = _cb;
	}

	bool operator()(const cv::Point2d& a, const cv::Point2d& b) {
		v8::Local<v8::Value> cbArgs[2];
		cbArgs[0] = FF_NEW_INSTANCE(Point2::constructor);
		cbArgs[1] = FF_NEW_INSTANCE(Point2::constructor);
		FF_UNWRAP_PT2_AND_GET(cbArgs[0]->ToObject()) = a;
		FF_UNWRAP_PT2_AND_GET(cbArgs[1]->ToObject()) = b;
		return cb->Call(Nan::GetCurrentContext()->Global(), 2, cbArgs)->BooleanValue();
	}
};

NAN_METHOD(Core::Partition) {
	if (!info[0]->IsArray()) {
		return Nan::ThrowError("Partition - expected arg 0 to be an array");
	}
	if (!info[1]->IsFunction()) {
		return Nan::ThrowError("Partition - expected arg 1 to be a function");
	}
	v8::Local<v8::Array> jsPts = FF_CAST_ARRAY(info[0]);
	v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(info[1]);

	std::vector<cv::Point2d> pts;
	Point::unpackJSPoint2Array(pts, jsPts);

	std::vector<int> labels;
	int numLabels = cv::partition(pts, labels, Predicate(cb));

	v8::Local<v8::Object> ret = Nan::New<v8::Object>();
	Nan::Set(ret, FF_NEW_STRING("labels"), FF::stdVecToJSArray<int>(labels));
	Nan::Set(ret, FF_NEW_STRING("numLabels"), Nan::New(numLabels));
	info.GetReturnValue().Set(ret);
}


NAN_METHOD(Core::Kmeans) {
	FF_METHOD_CONTEXT("Core::Kmeans");

	FF_ARG_ARRAY(0, FF_ARR jsData);
	std::vector<cv::Point2f> data;
	Point::unpackJSPoint2Array<float>(data, jsData);

	FF_ARG_INT(1, int k);
	FF_ARG_INSTANCE(2, cv::TermCriteria termCriteria, TermCriteria::constructor, FF_UNWRAP_TERMCRITERA_AND_GET);
	FF_ARG_INT(3, int attempts);
	FF_ARG_INT(4, int flags);

	std::vector<int> labels;
	cv::Mat centersMat;
	cv::kmeans(data, k, labels, termCriteria, attempts, flags, centersMat);

	FF_OBJ ret = Nan::New<v8::Object>();
	FF_PACK_ARRAY(jsLabels, labels);
	Nan::Set(ret, FF_NEW_STRING("labels"), jsLabels);
	
	std::vector<cv::Point2f> centers;
	for (int i = 0; i < centersMat.rows; i++) {
		centers.push_back(cv::Point2f(centersMat.at<float>(i, 0), centersMat.at<float>(i, 1)));
	}
	Nan::Set(ret, FF_NEW_STRING("centers"), Point::packJSPoint2Array<float>(centers));
	info.GetReturnValue().Set(ret);
}