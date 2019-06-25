#include "Vec.h"

Nan::Persistent<v8::FunctionTemplate> Vec2::constructor;
Nan::Persistent<v8::FunctionTemplate> Vec3::constructor;
Nan::Persistent<v8::FunctionTemplate> Vec4::constructor;
Nan::Persistent<v8::FunctionTemplate> Vec6::constructor;

NAN_MODULE_INIT(Vec::Init) {
	v8::Local<v8::FunctionTemplate> vec2Ctor = Nan::New<v8::FunctionTemplate>(Vec2::New);
	Vec2::constructor.Reset(vec2Ctor);
	vec2Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec2Ctor->SetClassName(Nan::New("Vec2").ToLocalChecked());
	Nan::SetAccessor(vec2Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec2::x_getter);
	Nan::SetAccessor(vec2Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec2::y_getter);
	Nan::SetPrototypeMethod(vec2Ctor, "at", Vec2::At);
	Nan::SetPrototypeMethod(vec2Ctor, "norm", Vec2::Norm);
	Vec2::Init(vec2Ctor);

	v8::Local<v8::FunctionTemplate> vec3Ctor = Nan::New<v8::FunctionTemplate>(Vec3::New);
	Vec3::constructor.Reset(vec3Ctor);
	vec3Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec3Ctor->SetClassName(Nan::New("Vec3").ToLocalChecked());
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec3::x_getter);
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec3::y_getter);
	Nan::SetAccessor(vec3Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vec3::z_getter);
	Nan::SetPrototypeMethod(vec3Ctor, "at", Vec3::At);
	Nan::SetPrototypeMethod(vec3Ctor, "cross", Vec3::Cross);
	Nan::SetPrototypeMethod(vec3Ctor, "norm", Vec3::Norm);
	Vec3::Init(vec3Ctor);

	v8::Local<v8::FunctionTemplate> vec4Ctor = Nan::New<v8::FunctionTemplate>(Vec4::New);
	Vec4::constructor.Reset(vec4Ctor);
	vec4Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec4Ctor->SetClassName(Nan::New("Vec4").ToLocalChecked());
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("w").ToLocalChecked(), Vec4::w_getter);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec4::x_getter);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec4::y_getter);
	Nan::SetAccessor(vec4Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vec4::z_getter);
	Nan::SetPrototypeMethod(vec4Ctor, "at", Vec4::At);
	Nan::SetPrototypeMethod(vec4Ctor, "norm", Vec4::Norm);
	Vec4::Init(vec4Ctor);

	v8::Local<v8::FunctionTemplate> vec6Ctor = Nan::New<v8::FunctionTemplate>(Vec6::New);
	Vec6::constructor.Reset(vec6Ctor);
	vec6Ctor->InstanceTemplate()->SetInternalFieldCount(1);
	vec6Ctor->SetClassName(Nan::New("Vec6").ToLocalChecked());
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("u").ToLocalChecked(), Vec6::u_getter);
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("v").ToLocalChecked(), Vec6::v_getter);
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("w").ToLocalChecked(), Vec6::w_getter);
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vec6::x_getter);
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vec6::y_getter);
	Nan::SetAccessor(vec6Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vec6::z_getter);
	Nan::SetPrototypeMethod(vec6Ctor, "at", Vec6::At);
	Nan::SetPrototypeMethod(vec6Ctor, "norm", Vec6::Norm);
	Vec6::Init(vec6Ctor);

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Vec::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Vec").ToLocalChecked());
  Nan::Set(target,Nan::New("Vec").ToLocalChecked(), FF::getFunction(ctor));
  Nan::Set(target,Nan::New("Vec2").ToLocalChecked(), FF::getFunction(ctor));
  Nan::Set(target,Nan::New("Vec3").ToLocalChecked(), FF::getFunction(ctor));
  Nan::Set(target,Nan::New("Vec4").ToLocalChecked(), FF::getFunction(ctor));
  Nan::Set(target,Nan::New("Vec6").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Vec::New) {
	FF::TryCatch tryCatch("Vec::New");
	FF_ASSERT_CONSTRUCT_CALL();
	if (info.Length() < 2 || info.Length() > 6 || info.Length() == 5) {
		return tryCatch.throwError("Vec::New - expected arguments (u, v), (w), x, y, (z)");
	}
	v8::Local<v8::Object> jsVec;

	switch(info.Length()) {
		case 2:
			jsVec = FF::newInstance(Nan::New(Vec2::constructor));
		  Nan::ObjectWrap::Unwrap<Vec2>(jsVec)->self = cv::Vec2d(
		  	info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value()
		  );
			break;
		case 3:
		  jsVec = FF::newInstance(Nan::New(Vec3::constructor));
		  Nan::ObjectWrap::Unwrap<Vec3>(jsVec)->self = cv::Vec3d(
		  	info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value()
		  );
			break;
		case 4:
		  jsVec = FF::newInstance(Nan::New(Vec4::constructor));
		  Nan::ObjectWrap::Unwrap<Vec4>(jsVec)->self = cv::Vec4d(
		  	info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[3]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value()
		  );
			break;
		case 6:
		  jsVec = FF::newInstance(Nan::New(Vec6::constructor));
		  Nan::ObjectWrap::Unwrap<Vec6>(jsVec)->self = cv::Vec6d(
		  	info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[3]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[4]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),
		  	info[5]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value()
		  );
			break;
	}
  info.GetReturnValue().Set(jsVec);
}
