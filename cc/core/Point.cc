#include "Point.h"

Nan::Persistent<v8::FunctionTemplate> Point2::constructor;
Nan::Persistent<v8::FunctionTemplate> Point3::constructor;

NAN_MODULE_INIT(Point::Init) {
	v8::Local<v8::FunctionTemplate> pt2Ctor = Nan::New<v8::FunctionTemplate>(Point2::New);
	Point2::constructor.Reset(pt2Ctor);
	pt2Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	pt2Ctor->SetClassName(Nan::New("Point2").ToLocalChecked());
	Nan::SetAccessor(pt2Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Point2::GetX);
	Nan::SetAccessor(pt2Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Point2::GetY);
	Nan::SetPrototypeMethod(pt2Ctor, "norm", Point2::Norm);
	Nan::SetPrototypeMethod(pt2Ctor, "at", Point2::At);
	Point2::Init(pt2Ctor);

	v8::Local<v8::FunctionTemplate> pt3Ctor = Nan::New<v8::FunctionTemplate>(Point3::New);
	Point3::constructor.Reset(pt3Ctor);
	pt3Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	pt3Ctor->SetClassName(Nan::New("Point3").ToLocalChecked());
	Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Point3::GetX);
	Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Point3::GetY);
	Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Point3::GetZ);
	Nan::SetPrototypeMethod(pt3Ctor, "norm", Point3::Norm);
	Nan::SetPrototypeMethod(pt3Ctor, "at", Point3::At);
	Point3::Init(pt3Ctor);

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Point::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Point").ToLocalChecked());
  target->Set(Nan::New("Point").ToLocalChecked(), ctor->GetFunction());
  target->Set(Nan::New("Point2").ToLocalChecked(), ctor->GetFunction());
  target->Set(Nan::New("Point3").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Point::New) {
	if (info.Length() < 2) {
		return Nan::ThrowError("Point::New - expected arguments x, y, (z)");
	}
	double x = info[0]->NumberValue();
	double y = info[1]->NumberValue();
	v8::Local<v8::Object> jsPoint;
	if (info.Length() == 3) {
		double z = info[2]->NumberValue();
		jsPoint = Nan::NewInstance(Nan::New(Point3::constructor)->GetFunction()).ToLocalChecked();
		Nan::ObjectWrap::Unwrap<Point3>(jsPoint)->pt = cv::Point3d(x, y, z);
	}
	else {
		v8::Local<v8::Function> ct = Nan::New(Point2::constructor)->GetFunction();
		jsPoint = Nan::NewInstance(ct).ToLocalChecked();
		Nan::ObjectWrap::Unwrap<Point2>(jsPoint)->pt = cv::Point2d(x, y);
	}
  info.GetReturnValue().Set(jsPoint);
}