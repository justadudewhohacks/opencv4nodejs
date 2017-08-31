#include "core.h"
#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Moments.h"

NAN_MODULE_INIT(Core::Init) {
  Mat::Init(target);
	Point::Init(target);
	Vec::Init(target);
	Size::Init(target);
	Rect::Init(target);
	RotatedRect::Init(target);
	Moments::Init(target);

	Nan::SetMethod(target, "partition", Partition);
};

struct Predicate {
	v8::Local<v8::Function> cb;

	Predicate(v8::Local<v8::Function> _cb) {
		cb = _cb;
	}

	bool operator()(const cv::Point2d& a, const cv::Point2d& b) {
		v8::Local<v8::Value> cbArgs[2];
		cbArgs[0] = FF_NEW(Point2::constructor);
		cbArgs[1] = FF_NEW(Point2::constructor);
		FF_UNWRAP_PT2_AND_GET(cbArgs[0]->ToObject()) = a;
		FF_UNWRAP_PT2_AND_GET(cbArgs[1]->ToObject()) = b;
		return cb->Call(Nan::GetCurrentContext()->Global(), 2, cbArgs)->BooleanValue();
	}
};

NAN_METHOD(Core::Partition) {
	if (!info[0]->IsArray()) {
		return Nan::ThrowError("Partition - expected arg0 to be an array");
	}
	if (!info[1]->IsFunction()) {
		return Nan::ThrowError("Partition - expected arg1 to be a function");
	}
	v8::Local<v8::Array> jsPts = FF_CAST_ARRAY(info[0]);
	v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(info[1]);

	std::vector<cv::Point2d> pts;
	Point::unpackJSPoint2Array(pts, jsPts);

	std::vector<int> labels;
	int numLabels = cv::partition(pts, labels, Predicate(cb));

	v8::Local<v8::Object> ret = Nan::New<v8::Object>();
	Nan::Set(ret, FF_V8STRING("labels"), FF::stdVecToJSArray<int>(labels));
	Nan::Set(ret, FF_V8STRING("numLabels"), Nan::New(numLabels));
	info.GetReturnValue().Set(ret);
}