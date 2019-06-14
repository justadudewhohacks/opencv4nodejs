#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KeyPoint.h"

Nan::Persistent<v8::FunctionTemplate> KeyPoint::constructor;

NAN_MODULE_INIT(KeyPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KeyPoint::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
	instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("KeyPoint").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("localId").ToLocalChecked(), localId_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("pt").ToLocalChecked(), pt_getter, pt_setter);
  Nan::SetAccessor(instanceTemplate, Nan::New("angle").ToLocalChecked(), angle_getter, angle_setter);
  Nan::SetAccessor(instanceTemplate, Nan::New("class_id").ToLocalChecked(), class_id_getter, class_id_setter);
  Nan::SetAccessor(instanceTemplate, Nan::New("response").ToLocalChecked(), response_getter, response_setter);
  Nan::SetAccessor(instanceTemplate, Nan::New("size").ToLocalChecked(), size_getter, size_setter);
  Nan::SetAccessor(instanceTemplate, Nan::New("octave").ToLocalChecked(), octave_getter, octave_setter);

  Nan::Set(target,Nan::New("KeyPoint").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(KeyPoint::New) {
	FF::TryCatch tryCatch("KeyPoint::New");
	FF_ASSERT_CONSTRUCT_CALL();
	KeyPoint* self = new KeyPoint();

	if (info.Length() > 0) {
		cv::Point2d pt;
		double size, angle, response;
		int octave, classId;
		if (
			Point2::Converter::arg(0, &pt, info) ||
			FF::DoubleConverter::arg(1, &size, info) ||
			FF::DoubleConverter::arg(2, &angle, info) ||
			FF::DoubleConverter::arg(3, &response, info) ||
			FF::IntConverter::arg(4, &octave, info) ||
			FF::IntConverter::arg(5, &classId, info)
		) {
			return tryCatch.reThrow();
		}
		self->self = cv::KeyPoint(pt, size, angle, response, octave, classId);
	}

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

#endif
