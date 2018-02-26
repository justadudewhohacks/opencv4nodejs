#include "Vec.h"

Nan::Persistent<v8::FunctionTemplate> Vec2::constructor;
Nan::Persistent<v8::FunctionTemplate> Vec3::constructor;
Nan::Persistent<v8::FunctionTemplate> Vec4::constructor;

NAN_MODULE_INIT(Vec::Init) {
	v8::Local<v8::FunctionTemplate> vec2Ctor = Nan::New<v8::FunctionTemplate>(Vec2::New);
	Vec2::constructor.Reset(vec2Ctor);
	vec2Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec2Ctor->SetClassName(Nan::New("Vec2").ToLocalChecked());
	Nan::SetAccessor(vec2Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec2::GetX);
	Nan::SetAccessor(vec2Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec2::GetY);
	Nan::SetPrototypeMethod(vec2Ctor, "at", Vec2::At);
	Nan::SetPrototypeMethod(vec2Ctor, "norm", Vec2::Norm);
	Vec2::Init(vec2Ctor);

	v8::Local<v8::FunctionTemplate> vec3Ctor = Nan::New<v8::FunctionTemplate>(Vec3::New);
	Vec3::constructor.Reset(vec3Ctor);
	vec3Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec3Ctor->SetClassName(Nan::New("Vec3").ToLocalChecked());
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec3::GetX);
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec3::GetY);
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vec3::GetZ);
	Nan::SetPrototypeMethod(vec3Ctor, "at", Vec3::At);
	Nan::SetPrototypeMethod(vec3Ctor, "cross", Vec3::Cross);
	Nan::SetPrototypeMethod(vec3Ctor, "norm", Vec3::Norm);
	Vec3::Init(vec3Ctor);

	v8::Local<v8::FunctionTemplate> vec4Ctor = Nan::New<v8::FunctionTemplate>(Vec4::New);
	Vec4::constructor.Reset(vec4Ctor);
	vec4Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec4Ctor->SetClassName(Nan::New("Vec4").ToLocalChecked());
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("w").ToLocalChecked(), Vec4::GetW);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec4::GetX);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec4::GetY);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vec4::GetZ);
	Nan::SetPrototypeMethod(vec4Ctor, "at", Vec4::At);
	Nan::SetPrototypeMethod(vec4Ctor, "norm", Vec4::Norm);
	Vec4::Init(vec4Ctor);

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Vec::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Vec").ToLocalChecked());
  target->Set(Nan::New("Vec").ToLocalChecked(), ctor->GetFunction());
  target->Set(Nan::New("Vec2").ToLocalChecked(), ctor->GetFunction());
  target->Set(Nan::New("Vec3").ToLocalChecked(), ctor->GetFunction());
  target->Set(Nan::New("Vec4").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Vec::New) {
	if (info.Length() < 2) {
		return Nan::ThrowError("Vec::New - expected arguments (w), x, y, (z)");
	}
	v8::Local<v8::Object> jsVec;
	if (info.Length() == 4) {
		v8::Local<v8::Function> ct = Nan::New(Vec4::constructor)->GetFunction();
		jsVec = Nan::NewInstance(ct).ToLocalChecked();
		Nan::ObjectWrap::Unwrap<Vec4>(jsVec)->vec = cv::Vec4d(
			info[0]->NumberValue(), 
			info[1]->NumberValue(), 
			info[2]->NumberValue(), 
			info[3]->NumberValue()
		);
	} else {
		double x = info[0]->NumberValue();
		double y = info[1]->NumberValue();
		if (info.Length() == 3) {
			double z = info[2]->NumberValue();
			jsVec = Nan::NewInstance(Nan::New(Vec3::constructor)->GetFunction()).ToLocalChecked();
			Nan::ObjectWrap::Unwrap<Vec3>(jsVec)->vec = cv::Vec3d(x, y, z);
		}
		else {
			v8::Local<v8::Function> ct = Nan::New(Vec2::constructor)->GetFunction();
			jsVec = Nan::NewInstance(ct).ToLocalChecked();
			Nan::ObjectWrap::Unwrap<Vec2>(jsVec)->vec = cv::Vec2d(x, y);
		}
	}
  info.GetReturnValue().Set(jsVec);
}