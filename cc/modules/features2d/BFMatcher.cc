#include "BFMatcher.h"
#include "BFMatcherBindings.h"

Nan::Persistent<v8::FunctionTemplate> BFMatcher::constructor;

NAN_MODULE_INIT(BFMatcher::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BFMatcher::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);

   ctor->SetClassName(Nan::New("BFMatcher").ToLocalChecked());
//  ctor->SetClassName(FF_NEW_STRING("BFMatcher"));


	Nan::SetAccessor(instanceTemplate, Nan::New("normType").ToLocalChecked(), BFMatcher::GetNormType);
  Nan::SetAccessor(instanceTemplate, Nan::New("crossCheck").ToLocalChecked(), BFMatcher::GetCrossCheck);

//    Nan::SetPrototypeMethod(ctor, "create", create);


    target->Set(Nan::New("BFMatcher").ToLocalChecked(), ctor->GetFunction());
//  target->Set(FF_NEW_STRING("BFMatcher"), ctor->GetFunction());

};

NAN_METHOD(BFMatcher::New) {
	FF_METHOD_CONTEXT("BFMatcher::New");
	BFMatcher* self = new BFMatcher();

    // optional args
    bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
    FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, self->normType, "normType", cv::NORM_L2);
		FF_GET_BOOL_IFDEF(optArgs, self->crossCheck, "crossCheck", false);

	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, self->normType, self->normType);
		FF_ARG_BOOL_IFDEF(1, self->crossCheck, self->crossCheck);
	}

	self->Wrap(info.Holder());
	self->bfmatcher = cv::BFMatcher(
		self->normType,
		self->crossCheck
	);

  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(BFMatcher::match) {
  FF::SyncBinding(
      std::make_shared<BFMatcherBindings::MatchWorker>(FF_UNWRAP(info.This(), BFMatcher)->bfmatcher),
    "BFMatcher::match",
    info
  );
}

NAN_METHOD(BFMatcher::matchAsync) {
  FF::AsyncBinding(
      std::make_shared<BFMatcherBindings::MatchWorker>(FF_UNWRAP(info.This(), BFMatcher)->bfmatcher),
      "FeatureDetector::matchAsync",
      info
  );
}

